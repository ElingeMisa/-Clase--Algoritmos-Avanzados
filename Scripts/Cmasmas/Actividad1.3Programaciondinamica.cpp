#include <iostream>
#include <vector>


using namespace std;

// Función que implementa la programación dinámica para resolver el problema de recolección de monedas
// Complejidad: O(n cuadrada)
int memoization(vector<vector<int>>& grid, vector<vector<int>>& dp, int i, int j) {
    if (i < 0 || j < 0) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    dp[i][j] = max(memoization(grid, dp, i-1, j), memoization(grid, dp, i, j-1)) + grid[i][j];
    return dp[i][j];
}


int main() {

// casos de prueba
    vector<vector<int>> grid = {
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1}
    };
    
    vector<vector<int>> dp = {
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1}
    };

    int maxcoins = memoization(grid, dp, grid.size()-1, grid[0].size()-1);

    cout << "La cantidad máxima de monedas que se pueden recolectar es: " << maxcoins << endl;

    return 0;
}
