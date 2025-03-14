#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> crear_matriz(int tamaño){
    vector<vector<int>> matriz(tamaño, vector<int>(tamaño));

    int num = 1;
    for(int i = 0; i < tamaño; i++){
        for(int j = 0; j < tamaño; j++){
            matriz[i][j] = num;
            num += 1;
        }
    }

    return matriz;

}

void imprimir_matriz(const vector<vector<int>> matriz, int tamaño){
    for (int i = tamaño * tamaño - 1; i >= 0; i--) {
        int fila = i / tamaño;
        int columna = i % tamaño;
        cout << "M[" << fila << "][" << columna << "] = " << matriz[fila][columna] << endl;
    }
}

int main(){
    int tamaño = 2;
    vector<vector<int>> matriz = crear_matriz(tamaño); 
    imprimir_matriz(matriz, tamaño); 

    return 0;
}

// Para compilar y ejecutar
// g++ -std=c++17 -Wall -Wextra -o "Ejercicio 1/ej1" "Ejercicio 1/ej1.cpp"
// cd "Ejercicio 1"
// g++ -std=c++17 -Wall -Wextra -o ej1 ej1.cpp
// ./ej1


