#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Funcion para llenar el vector desde un archivi
// Complejidad O(n) donde n es el numero de elementos a permutar

void fill(std::vector<int>& vec, const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    int number;

    while (file >> number) { 
        vec.push_back(number); 
    }

    file.close(); 
}


// Función para ordenar el vector usando el algoritmo de ordenamiento por burbuja
// Complejida: O(n^2)
// retomado de la clase de algoritmos y estructuras de datos

void bubble_sort(std::vector<int> &arr)
{
    int n = arr.size();
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < n - 1; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        --n; // Reduce el rango porque el último elemento ya está ordenado
    } while (swapped);
}

// Función para generar la siguiente permutación lexicográfica
// Complejidad Temporal: O(n)

bool next_permutation(std::vector<int> &arr)
{

    int i = arr.size() - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) --i;
    if (i == -1)
    {
        return false; // Ya es la última permutación
    }

    int j = arr.size() - 1;
    // aaseguramos que este ordneado (asumiendo que sean numeros y letras <- con el ascii)
    while (arr[j] <= arr[i]) --j;
    
    std::swap(arr[i], arr[j]);

    std::reverse(arr.begin() + i + 1, arr.end());
    return true;
}

// Función para generar e imprimir todas las permutaciones en orden lexicográfico
// Complejidad Temporal: O(n^2)

void generate_permutations(std::vector<int> &arr)
{

    // empezamos ordenando
    bubble_sort(arr);

    // Imprime la primera permutación y repite si se pueden mas
    do
    {
        std::cout << '\t';
        for (int x = 0; x < arr.size(); x++)
        {
            std::cout << " " << arr[x];
        }
        std::cout<<'\n';
    } while (next_permutation(arr));
}

int main()
{

    std::vector<int> arr;
    std::string filename = "numbers.txt"; // nombre del archivo 

    fill(arr, filename);

    std::cout<<"Generando las permutaciones del arreglo: ";

    for (int num = 0;  num < arr.size(); num++) std::cout << arr[num] << " ";

    std::cout <<"\n\n";
    generate_permutations(arr);

    return 0;
}
