#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Mensaje {
public:
    string rol, contenido;
};

class Conversacion {
public:
    vector<Mensaje> mensajes;
    string ruta;

    Conversacion() {
        auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
        tm p;
#ifdef _WIN32
        localtime_s(&p, &t);
#else
        localtime_r(&t, &p);
#endif
        // Crear rutas simples
        string folder = "conversaciones/" + to_string(p.tm_year + 1900) + "-" + to_string(p.tm_mon + 1) + "-" + to_string(p.tm_mday);
        filesystem::create_directories(folder);
        
        ostringstream oss;
        oss << folder << "/" << put_time(&p, "%H-%M-%S") << ".json";
        ruta = oss.str();
    }

    void guardar() {
        ofstream f(ruta);
        f << "[\n";
        for (size_t i = 0; i < mensajes.size(); ++i) {
            f << "  {\"rol\": \"" << mensajes[i].rol << "\", \"contenido\": \"" << mensajes[i].contenido << "\"}";
            f << (i < mensajes.size() - 1 ? ",\n" : "\n");
        }
        f << "]";
    }
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    Conversacion chat;
    string input;

    cout << "Chatbot. Escribe 'salir' para terminar.\n";

    while (true) {
        cout << "Tu: ";
        getline(cin, input);

        if (input == "salir") break;

        chat.mensajes.push_back({"usuario", input});

        string bot_msg = input; // Por defecto repite
        if (input == "hola" || input == "Hola") bot_msg = "¡Hola! ¿En que puedo ayudarte?";
        if (input == "examen" || input == "Examen") bot_msg = "¡Exito en tu examen de mañana!";

        cout << "Bot: " << bot_msg << "\n";
        chat.mensajes.push_back({"sistema", bot_msg});
        
        chat.guardar();
    }

    return 0;
}