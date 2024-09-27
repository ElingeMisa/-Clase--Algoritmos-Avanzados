#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Variables globales

    vector< vector<int> > mapa;
    string path;

// función para llenar la matriz de monedas desde un archivo de texto
void llenarMatriz()
{
    ifstream archivo("mapa.txt"); // Abre el archivo con el nombre "matriz.txt"
    int n;
    archivo >> n; 
    mapa.resize(n, vector<int>(n)); 

    for (int i = 0; i < n; i++) {   for (int j = 0; j < n; j++) {archivo >> mapa[i][j];}    }
    archivo.close(); 
}

// Función que implementa algoritmos greedy para resolver el problema de recolección de monedas
// Complejidad: O(n) donde n es el tamaño de la matriz
int greedy(int current_coins, string path, int i, int j)
{
    // si la posición actual es válida
    if (i == mapa.size() - 1 && j == mapa.size() - 1) return current_coins + mapa[i][j];
   
    int right = 0, down = 0;

    for(int i2 = i; i2 < mapa.size()-1;i2++){
        right += mapa[i2][j];
    }
    for (int j2 = j; j2 < mapa.size()-1; j2++){
        down += mapa[i][j2];
    }

    if (right > down) {
        path = path +  " [Derecha" + " (" + to_string(mapa[i+1][j]) + ")]";
        return greedy(current_coins + mapa[i][j], path, i + 1, j);
    } else  if (right < down) {
        path = path +  " [Abajo" + " " + to_string(mapa[i][j+1]) + "]";
        return greedy(current_coins + mapa[i][j], path, i, j + 1);
    } else {
        int right_coins = greedy(current_coins + mapa[i][j], path + "R", i + 1, j);
        int down_coins = greedy(current_coins + mapa[i][j], path + "D", i, j + 1);
        return max(right_coins, down_coins);
    }

}

int main()
{
    llenarMatriz();

    cout << "Buscando la ruta con más monedas..." << endl;
    // Mostrar el mapa
    for (int i = 0; i < mapa.size(); i++)
    {
        for (int j = 0; j < mapa[i].size(); j++) cout << mapa[i][j] << " ";
        cout << '\n';
    }

    string mini_path = "[Inicio " + to_string(mapa[0][0]) + "]";

    cout << "La cantidad máxima de monedas que se pueden recolectar es: " << greedy(mapa[0][0], mini_path, 0, 0) << "siguiendo el camino "<< '\n' << mini_path << endl;

    return 0;
}
