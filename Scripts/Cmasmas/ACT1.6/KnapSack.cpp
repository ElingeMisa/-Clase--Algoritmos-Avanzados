#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Variables globales
    int W;  
    int n;  

    vector<int> values; 
    vector<int> weights;  

// Función para llenar los valores y pesos desde un archivo de texto
void llenar() {
    ifstream archivo("mochila.txt");

    archivo >> n >> W;  // Leer número de objetos y capacidad de la mochila

    values.resize(n);
    weights.resize(n);

    for (int i = 0; i < n; i++) {
        archivo >> values[i] >> weights[i];
    }
    archivo.close();
}

// Función comparadora para ordenar los objetos por su ratio valor/peso
bool compare(int a, int b) {
    double ratioA = (double)values[a] / weights[a];
    double ratioB = (double)values[b] / weights[b];
    return ratioA > ratioB;
}

// Función greedy para el problema de la mochila 0/1
// Complejidad: O(n)
int knapsackGreedy(int W, int n, vector<int>& values, vector<int>& weights) {
    vector<int> indices(n);
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    // Ordenar los objetos por el ratio valor/peso en orden descendente
    sort(indices.begin(), indices.end(), compare);

    int currentWeight = 0;
    int totalValue = 0;

    for (int i = 0; i < n; i++) {
        int index = indices[i];
        if (currentWeight + weights[index] <= W) {
            currentWeight += weights[index];
            totalValue += values[index];
        } else {
            // Si no cabe no lo tomamos 
            break;
        }
    }

    return totalValue;
}

int main() {
    llenar();
    cout << "Valores y pesos de los objetos: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "\tObjeto [" << i + 1 << "]: vale " << values[i] << " y pesa " << weights[i] << endl;
    }

    cout << "Valor máximo en la mochila usando enfoque greedy: " << knapsackGreedy(W, n, values, weights) << endl;

    return 0;
}
