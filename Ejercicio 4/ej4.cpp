#include <iostream>
#include <chrono>
using namespace std;

// A

bool comparar_texto(string texto1, string texto2){
    if(texto1.length() != texto2.length()){             // si las longitudes no son iguales, no es el mismo texto
        return false;
    }

    if(texto1.empty() && texto2.empty()){               // si no hay texto, son iguales
        return true;
    }

    if(texto1[0] == texto2[0]){                          // compara caracter por caracter
        return comparar_texto(texto1.substr(1), texto2.substr(1));
    }

    return false;
}

// Para resolverlo elegí usar string porque el tiempo de ejecución es más rápido que usando char. 
// Con string tarda entre 50 y 100 nanosegundos mientras que con char, más de 2000 en algunas ejecuciones.

// C

consteval bool comparar_texto2(const char* texto1, const char* texto2){         // con consteval se fuerza a que la comparación de los textos sea en la compilación
    if (*texto1 != *texto2){
        return false;
    }

    if (*texto1 == '\0' && *texto2 == '\0'){  
        return true;
    }

    return comparar_texto2(texto1 + 1, texto2 + 1); 
}

int main() {
    string a = "con un texto de al menos 64 caracteres estoy probando la funcionalidad de mi función recursiva";
    string b = "con un texto de al menos 64 caracteres estoy probando la funcionalidad de mi función recursiva";

    auto startTime = chrono::high_resolution_clock::now();
    auto endTime = chrono::high_resolution_clock::now();

    auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

    if(comparar_texto(a, b)){
        cout << "Los textos son iguales. A comparar_texto le tomó " << elapsedTime.count() << " nanosegundos." << endl;
    }
    else {
        cout << "Los textos no son iguales. A comparar_texto le tomó " << elapsedTime.count() << " nanosegundos." << endl;
    }

    constexpr bool resultado = comparar_texto2("con un texto de al menos 64 caracteres estoy probando la funcionalidad de mi función recursiva",  "con un texto de al menos 64 caracteres estoy probando la funcionalidad de mi función");


    auto startTime2 = chrono::high_resolution_clock::now();
    auto endTime2 = chrono::high_resolution_clock::now();

    auto elapsedTime2 = chrono::duration_cast<chrono::nanoseconds>(endTime2 - startTime2);

    if constexpr(resultado) {  // evaluado en compilación
        cout << "Los textos son iguales (evaluado en compilación). A comparar_texto2 le tomó " << elapsedTime2.count() << " nanosegundos." << endl;
    } 
    else {
        cout << "Los textos no son iguales (evaluado en compilación). A comparar_texto2 le tomó " << elapsedTime2.count() << " nanosegundos." << endl;
    }

    return 0;
}

// Cuando la comparación de los textos se realiza en tiempo de compilación el tiempo que tarda es menor. Lo ejecuté varias veces
// y en la mayoría de ellas comparar_texto2 tarda la mitad del tiempo que comparar_texto (aunque algunas pocas veces tardan lo mismo)
// Al principio dije que preferí usar string antes que char porque tardaba menos pero, si se fuerza al programa a que la comparación 
// sea en la compilación, es preferible usar char.