#include <fstream>

using namespace std;

enum class NivelSeveridad{ DEBUG, INFO, WARNING, ERROR, CRITICAL, SECURITY};  // enum class evita colisiones con otros nombres

#define LOG_ERROR(msg) logMessage(NivelSeveridad::ERROR, msg, __FILE__, __LINE__)   // recupera el archivo y línea donde se produce el error

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

void logMessage(NivelSeveridad nivel, string mensaje){           // de acuerdo al nivel de severidad recupera su mensaje y lo escribe en el archivo
    ofstream logFile("log.txt", ios::app); 

    logFile << "[" << severidad_a_string(nivel) << "] " << mensaje << endl;

    logFile.close();
}

void logMessage(NivelSeveridad nivel, string mensaje_de_error, string archivo, int linea_de_codigo){     //  imprime el archivo y linea del error con el mensaje 
    ofstream logFile("log.txt", ios::app);
    logFile << "[" << severidad_a_string(nivel) << "] " << mensaje_de_error
            << " (Archivo: " << archivo << ", Línea: " << linea_de_codigo << ")" << endl;
    logFile.close();
}

void logMessage(NivelSeveridad nivel, string mensaje_de_acceso, string nombre_de_usuario){    // registra el acceso del usuario      
    ofstream logFile("log.txt", ios::app);
    logFile << "[" << severidad_a_string(nivel) << "] " << mensaje_de_acceso << " " << nombre_de_usuario << endl;

    logFile.close();
};

int main(){
    logMessage(NivelSeveridad::DEBUG, "Iniciando el programa");           // prueba la función con una llamada de cada nivel del severidad
    logMessage(NivelSeveridad::INFO, "Iniciado correctamente");
    logMessage(NivelSeveridad::WARNING, "Archivo no encontrado");
    logMessage(NivelSeveridad::ERROR, "Error al abrir el archivo");
    logMessage(NivelSeveridad::CRITICAL, "Falla en el sistema");

    LOG_ERROR("Ocurrió un error inesperado");           // prueba la función con el archivo y linea del error

    logMessage(NivelSeveridad::SECURITY, "Access Granted,", "Lucía");        // prueba la función que registra el acceso

    try {                       
        int* ptr = nullptr;         // defino que no apunte a ninguna dirección de memoria válida
        if (ptr == nullptr) {    // como es un nullptr lanza la excepción runtime_error
            throw runtime_error("Acceso a puntero nulo");
        }
        return 0;

    } catch (const exception& e) {     // captura la excepción 
        LOG_ERROR(e.what());            // devuelve el mensaje de la excepción
        return 1;
    }

    return 0;
}