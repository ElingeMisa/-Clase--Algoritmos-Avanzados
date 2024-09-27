#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Función para llenar el vector desde un archivo
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

// Función para ordenar el vector usando Bubble Sort
void bubble_sort(std::vector<char>& vec) {
    size_t n = vec.size();
    bool swapped;

    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break; 
        }
    }
}

// Función para generar todos los subconjuntos en orden lexicográfico
void generate_subsets_helper(const std::vector<char>& cadena, std::string current, int index, std::vector<std::string>& subsets) {
    // Agregar el subconjunto actual a la lista de subconjuntos
    if (!current.empty()) {
        subsets.push_back(current);
    }

    // Generar todos los subconjuntos a partir del índice actual
    for (int i = index; i < cadena.size(); ++i) {
        // Incluir el carácter actual en el subconjunto
        generate_subsets_helper(cadena, current + cadena[i], i + 1, subsets);
    }
}

void generate_subsets(const std::vector<char>& cadena, std::vector<std::string>& subsets) {
    // Iniciar la recursión con una cadena vacía y el índice 0
    generate_subsets_helper(cadena, "", 0, subsets);

    // Dado que el vector cadena está ordenado y estamos generando subconjuntos a partir de índices crecientes,
    // los subconjuntos generados ya estarán en orden lexicográfico.
}

int main() {
    // Se toma la cadena para generar los subsets
    std::vector<char> cadena;
    std::vector<std::string> subsets;

    std::string filename = "subset.txt";

    fill(cadena, filename);

    // Ordenar la cadena usando Bubble Sort
    bubble_sort(cadena);

    generate_subsets(cadena, subsets);

    // Imprimir los subconjuntos generados en orden lexicográfico
    for (const std::string& subset : subsets) {
        std::cout << subset << std::endl;
    }

    return 0;
}
