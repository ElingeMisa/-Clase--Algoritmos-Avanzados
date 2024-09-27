#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Función para llenar el vector de monedas con los valores del archivo de texto
void fill(const string& filename, vector<int>& coins){
    ifstream file(filename);
    if (file.is_open()) {
        // leer la primera linea 
        string line;
        int n_coins;
        file >> n_coins;
        
        for (int i = 0; i < n_coins; i++) {
            int coin;
            file >> coin;
            coins.push_back(coin);
        }
        
        file.close();
    }
}

void mitad(vector<int>&arr, int inicio, int final, int pivote){
    int temp = arr[pivote];
    int i = inicio;
    int j = final;

    while ((i < j)){

        while((arr[i] < temp )) i ++;
        while((arr[j] > temp )) j --;

        cout << "i: " << i << " j: " << j << endl;
        cout << "arr[i]: " << arr[i] << " arr[j]: " << arr[j] << endl;

        if( arr[i] >= temp){
            arr.insert(arr.begin() + pivote, arr[i]);
            i++;
            j--;
        } else if (arr[j] <= temp){
            arr.insert(arr.begin() + pivote, arr[j]);
            j--;
            i++;
        }
    }
    
}

int main(){
    // Comenzamos leyendo el arreglo desde el archivo de texto
    vector<int> numeros;
    fill("numbers.txt", numeros);

    // Imprimimos el arreglo original
    cout << "Arreglo original:" << endl;
    for (int i = 0; i < numeros.size(); i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    // Seleccionamos el pivote como el primer elemento del arreglo
    int pivote = 5;
    mitad(numeros, 0, numeros.size() - 1, pivote);

    // Imprimimos el arreglo después de seleccionar el pivote
    cout << "Arreglo después de seleccionar el pivote:" << endl;
    for (int i = 0; i < numeros.size(); i++) {
        cout << numeros[i] << " ";
    }

    return 0;
}
