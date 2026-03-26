#include <curl/curl.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

// Elimina espacios en blanco al inicio y final de un string
std::string trim(const std::string& value) {
    const std::string whitespace = " \t\r\n";
    const size_t start = value.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    const size_t end = value.find_last_not_of(whitespace);
    return value.substr(start, end - start + 1);
}

// Carga las variables del archivo .env al entorno del sistema
void load_dotenv_file(const std::string& path) {
    std::ifstream dotenv_file(path);
    if (!dotenv_file.is_open()) return;

    std::string line;
    while (std::getline(dotenv_file, line)) {
        const std::string cleaned_line = trim(line);
        if (cleaned_line.empty() || cleaned_line[0] == '#') continue;

        const size_t separator = cleaned_line.find('=');
        if (separator == std::string::npos || separator == 0) continue;

        const std::string key = trim(cleaned_line.substr(0, separator));
        std::string value = trim(cleaned_line.substr(separator + 1));

        // Quitar comillas si existen
        if (value.size() >= 2 &&
            ((value.front() == '"' && value.back() == '"') ||
             (value.front() == '\'' && value.back() == '\''))) {
            value = value.substr(1, value.size() - 2);
        }

        if (key.empty()) continue;

        const char* existing_value = std::getenv(key.c_str());
        if (existing_value == nullptr || std::string(existing_value).empty()) {
            // COMPATIBILIDAD WINDOWS: Usamos _putenv_s para definir variables de entorno
            _putenv_s(key.c_str(), value.c_str());
        }
    }
}

// Callback para que CURL guarde la respuesta en un string de C++
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    const size_t total_size = size * nmemb;
    auto* output = static_cast<std::string*>(userp);
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

// Escapa caracteres especiales para formar un JSON válido
std::string escape_json(const std::string& input) {
    std::string escaped;
    escaped.reserve(input.size() + 8);
    for (const char ch : input) {
        switch (ch) {
            case '"':  escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\b': escaped += "\\b"; break;
            case '\f': escaped += "\\f"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default:   escaped += ch; break;
        }
    }
    return escaped;
}

// Des-escapa la respuesta JSON para que sea legible
std::string unescape_json_string(const std::string& input) {
    std::string output;
    output.reserve(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] != '\\') {
            output += input[i];
            continue;
        }
        if (i + 1 >= input.size()) break;
        const char next = input[++i];
        switch (next) {
            case '"':  output += '"'; break;
            case '\\': output += '\\'; break;
            case '/':  output += '/'; break;
            case 'b':  output += '\b'; break;
            case 'f':  output += '\f'; break;
            case 'n':  output += '\n'; break;
            case 'r':  output += '\r'; break;
            case 't':  output += '\t'; break;
            default:   output += next; break;
        }
    }
    return output;
}

// Extrae el campo "content" de la respuesta de OpenAI usando Regex
std::string extract_content_field(const std::string& json_response) {
    const std::regex content_regex("\"content\"\\s*:\\s*\"((?:\\\\.|[^\\\"])*)\"");
    std::smatch match;
    if (std::regex_search(json_response, match, content_regex) && match.size() > 1) {
        return unescape_json_string(match[1].str());
    }
    return "";
}

struct CliOptions {
    std::string model = "gpt-4o-mini";
    std::string prompt;
};

// Parsea los argumentos de la terminal
CliOptions parse_args(int argc, char* argv[]) {
    CliOptions options;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--model" && i + 1 < argc) {
            options.model = argv[++i];
        } else if (arg == "--prompt" && i + 1 < argc) {
            options.prompt = argv[++i];
        } else if (arg == "-h" || arg == "--help") {
            std::cout << "Uso: gpt_terminal [--model <modelo>] [--prompt <texto>]\n";
            std::exit(0);
        } else {
            throw std::runtime_error("Argumento desconocido: " + arg);
        }
    }
    return options;
}

// Realiza la petición HTTP POST a la API
std::string request_chat_completion(const std::string& api_key, const std::string& base_url, const std::string& model, const std::string& prompt) {
    CURL* curl = curl_easy_init();
    if (!curl) throw std::runtime_error("Error al inicializar CURL");

    std::string response_body;
    std::string url = base_url;
    if (!url.empty() && url.back() == '/') url.pop_back();
    url += "/v1/chat/completions";

    const std::string payload = "{\"model\":\"" + escape_json(model) + "\",\"messages\":[{\"role\":\"user\",\"content\":\"" + escape_json(prompt) + "\"}]}";

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) throw std::runtime_error(std::string("CURL falló: ") + curl_easy_strerror(res));
    if (http_code < 200 || http_code >= 300) {
        throw std::runtime_error("HTTP " + std::to_string(http_code) + ". Respuesta: " + response_body);
    }

    return response_body;
}

} // namespace final

int main(int argc, char* argv[]) {
    try {
        const CliOptions options = parse_args(argc, argv);
        
        // Cargar archivo .env
        load_dotenv_file(".env");

        const char* api_key_ptr = std::getenv("OPENAI_API_KEY");
        if (!api_key_ptr || std::string(api_key_ptr).empty()) {
            std::cerr << "Error: No se encontró la variable OPENAI_API_KEY en el entorno o en el archivo .env\n";
            return 1;
        }
        std::string api_key = api_key_ptr;

        std::string prompt = options.prompt;
        if (prompt.empty()) {
            std::cout << "Introduce tu pregunta para GPT: ";
            std::getline(std::cin, prompt);
        }
        if (prompt.empty()) return 1;

        const char* base_url_ptr = std::getenv("OPENAI_BASE_URL");
        std::string base_url = (base_url_ptr) ? base_url_ptr : "https://api.openai.com";

        curl_global_init(CURL_GLOBAL_DEFAULT);
        std::string response_json = request_chat_completion(api_key, base_url, options.model, prompt);
        curl_global_cleanup();

        std::string content = extract_content_field(response_json);
        if (!content.empty()) {
            std::cout << "\n--- Respuesta del Modelo ---\n" << content << "\n----------------------------\n";
        } else {
            std::cout << "\nRespuesta cruda (JSON):\n" << response_json << "\n";
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}