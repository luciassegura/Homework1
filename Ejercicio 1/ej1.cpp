#include <iostream>
#include <vector>

using namespace std;

// Crea y devuelve una matriz cuadrada rellenándola con números consecutivos empezando por el 1.
vector<vector<int>> crear_matriz(int tamaño){
    vector<vector<int>> matriz(tamaño, vector<int>(tamaño));  // se inicializa con 'tamaño' y cada fila es un vector de 'tamaño columnas'

    int num = 1;
    for(int i = 0; i < tamaño; i++){
        for(int j = 0; j < tamaño; j++){
            matriz[i][j] = num;
            num += 1;
        }
    }

    return matriz;

}

// Imprime el contenido de la matriz indicando los ínidices corresponidientes
void imprimir_matriz(const vector<vector<int>> matriz, int tamaño){
    for (int i = tamaño * tamaño - 1; i >= 0; i--) {            // trata a la matriz como un arreglo y lo recorre al revés
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