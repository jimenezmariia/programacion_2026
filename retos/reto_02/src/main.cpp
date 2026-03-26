#include <curl/curl.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

std::string trim(const std::string& value) {
    const std::string whitespace = " \t\r\n";
    const size_t start = value.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    const size_t end = value.find_last_not_of(whitespace);
    return value.substr(start, end - start + 1);
}

void load_dotenv(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        const std::string clean = trim(line);
        if (clean.empty() || clean[0] == '#') continue;

        size_t sep = clean.find('=');
        if (sep == std::string::npos || sep == 0) continue;

        std::string key = trim(clean.substr(0, sep));
        std::string val = trim(clean.substr(sep + 1));

        if (val.size() >= 2 && ((val.front() == '"' && val.back() == '"') || (val.front() == '\'' && val.back() == '\''))) {
            val = val.substr(1, val.size() - 2);
        }

        if (!key.empty() && (!std::getenv(key.c_str()) || std::string(std::getenv(key.c_str())).empty())) {
            _putenv_s(key.c_str(), val.c_str());
        }
    }
}

size_t write_cb(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total = size * nmemb;
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), total);
    return total;
}

std::string escape_json(const std::string& input) {
    std::string escaped;
    for (const char ch : input) {
        switch (ch) {
            case '"':  escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default:   escaped += ch; break;
        }
    }
    return escaped;
}

std::string unescape_json(const std::string& input) {
    std::string out;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '\\' && i + 1 < input.size()) {
            switch (input[++i]) {
                case '"':  out += '"'; break;
                case '\\': out += '\\'; break;
                case 'n':  out += '\n'; break;
                case 't':  out += '\t'; break;
                default:   out += input[i]; break;
            }
        } else out += input[i];
    }
    return out;
}

std::string get_content(const std::string& json) {
    const std::regex re("\"content\"\\s*:\\s*\"((?:\\\\.|[^\\\"])*)\"");
    std::smatch m;
    return (std::regex_search(json, m, re) && m.size() > 1) ? unescape_json(m[1].str()) : "";
}

struct Config {
    std::string model = "llama-3.1-8b-instant";
    std::string prompt;
};

Config parse_args(int argc, char* argv[]) {
    Config conf;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--model" && i + 1 < argc) conf.model = argv[++i];
        else if (arg == "--prompt" && i + 1 < argc) conf.prompt = argv[++i];
    }
    return conf;
}

std::string do_request(const std::string& key, const std::string& url, const std::string& model, const std::string& prompt) {
    CURL* curl = curl_easy_init();
    if (!curl) throw std::runtime_error("CURL error");

    std::string body, full_url = url + "/v1/chat/completions";
    std::string payload = "{\"model\":\"" + escape_json(model) + "\",\"messages\":[{\"role\":\"user\",\"content\":\"" + escape_json(prompt) + "\"}]}";

    struct curl_slist* headers = curl_slist_append(nullptr, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + key).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

    CURLcode res = curl_easy_perform(curl);
    long code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
    
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK || code < 200 || code >= 300) 
        throw std::runtime_error("Error HTTP " + std::to_string(code) + ": " + body);

    return body;
}

} // namespace

int main(int argc, char* argv[]) {
    try {
        Config conf = parse_args(argc, argv);
        load_dotenv(".env");

        const char* key = std::getenv("OPENAI_API_KEY");
        const char* url = std::getenv("OPENAI_BASE_URL");

        if (!key) {
            std::cerr << "Error: No hay API Key en .env\n";
            return 1;
        }

        if (conf.prompt.empty()) {
            std::cout << "Pregunta: ";
            std::getline(std::cin, conf.prompt);
        }
        if (conf.prompt.empty()) return 0;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        std::string json = do_request(key, url ? url : "https://api.groq.com/openai", conf.model, conf.prompt);
        curl_global_cleanup();

        std::string resp = get_content(json);
        if (!resp.empty()) std::cout << "\n[Respuesta]:\n" << resp << "\n";
        else std::cout << "\n[JSON]:\n" << json << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
