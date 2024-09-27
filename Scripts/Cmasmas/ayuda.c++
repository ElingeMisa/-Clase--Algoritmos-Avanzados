#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Función para llenar el vector desde un archivo
// complejidad o(n)
void fill(std::vector<char>& vec, const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    char character;

    while (file >> character) { 
        vec.push_back(character); 
    }

    file.close(); 
}

// para añadir un subset a la lista de subsets , complejidad O(n) donde n es el numero de subsets
void add(std::string trash, std::vector<std::string>&arr){
    for(int x = 0; x<arr.size();x++){
     if(trash == arr[x]){return;}
    }
    arr.push_back(trash);
}

// funcion para generar todos los subsets (antes los imprmia) , complejidad O(n*2 a la n)
void printSubsets(const std::vector<char>& arr, std::vector<std::string>& subsets) {
    int n = arr.size();
    int subsetCount = 1 << n; // 2^n posibles subconjuntos

    // Iterar sobre todos los posibles subconjuntos
    for (int i = 0; i < subsetCount; ++i) {
        //std::cout << "{";
        std::string trash =" ";
        for (int j = 0; j < n; ++j) {
            // Comprobar si el j-ésimo elemento está en el subconjunto actual
            if (i & (1 << j)) {
                
                //std::cout << arr[j] << " ";

                trash+=arr[j];

            }
        }
        add(trash, subsets);
        //std::cout << "}" << std::endl;
    }
}


int main() {
    // Se toma la cadena para generar los subsets
    std::vector<char> cadena;
    std::vector<std::string> subsets;

    std::string filename = "subset.txt";

    fill(cadena, filename);

    // Ordenar la cadena usando Bubble Sort
    //bubble_sort(cadena);

    printSubsets(cadena, subsets);

    // Imprimir los subconjuntos generados en orden lexicográfico
    for (const std::string& subset : subsets) {
        std::cout << subset << std::endl;
    }

    return 0;
}
