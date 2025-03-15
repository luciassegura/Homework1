#include <fstream>

using namespace std;

enum class NivelSeveridad{ DEBUG, INFO, WARNING, ERROR, CRITICAL, SECURITY};

#define LOG_ERROR(msg) logMessage(NivelSeveridad::ERROR, msg, __FILE__, __LINE__)       // B

string severidad_a_string(NivelSeveridad level){
    switch (level) {
        case NivelSeveridad::DEBUG: return "DEBUG";
        case NivelSeveridad::INFO: return "INFO";
        case NivelSeveridad::WARNING: return "WARNING";
        case NivelSeveridad::ERROR: return "ERROR";
        case NivelSeveridad::CRITICAL: return "CRITICAL";
        case NivelSeveridad::SECURITY: return "SECURITY";
    }
    return "UNKNOWN";
}

void logMessage(NivelSeveridad nivel, string mensaje){           
    ofstream logFile("log.txt", ios::app); 

    logFile << "[" << severidad_a_string(nivel) << "] " << mensaje << endl;

    logFile.close();
}

void logMessage(NivelSeveridad nivel, string mensaje_de_error, string archivo, int linea_de_codigo){       
    ofstream logFile("log.txt", ios::app);
    logFile << "[" << severidad_a_string(nivel) << "] " << mensaje_de_error
            << " (Archivo: " << archivo << ", Línea: " << linea_de_codigo << ")" << endl;
    logFile.close();
}

void logMessage(NivelSeveridad nivel, string mensaje_de_acceso, string nombre_de_usuario){          
    ofstream logFile("log.txt", ios::app);
    logFile << "[" << severidad_a_string(nivel) << "] " << mensaje_de_acceso << " " << nombre_de_usuario << endl;

    logFile.close();
};

int main(){
    logMessage(NivelSeveridad::DEBUG, "Iniciando el programa");           
    logMessage(NivelSeveridad::INFO, "Iniciado correctamente");
    logMessage(NivelSeveridad::WARNING, "Archivo no encontrado");
    logMessage(NivelSeveridad::ERROR, "Error al abrir el archivo");
    logMessage(NivelSeveridad::CRITICAL, "Falla en el sistema");

    LOG_ERROR("Ocurrió un error inesperado");           

    logMessage(NivelSeveridad::SECURITY, "Access Granted,", "Lucía");        

    try {                       
        int* ptr = nullptr;         
        if (ptr == nullptr) {
            throw runtime_error("Acceso a puntero nulo");
        }
        return 0;

    } catch (const exception& e) {
        LOG_ERROR(e.what());
        return 1;
    }
    return 0;
}


// Para compilar y ejecutar
// g++ -std=c++17 -Wall -Wextra -o "Ejercicio 2/ej2" "Ejercicio 2/ej2.cpp"
// cd "Ejercicio 2"
// g++ -std=c++17 -Wall -Wextra -o ej1 ej2.cpp
// ./ej2


