#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


void fill(const string& filename, vector<int>& coins) {
    ifstream file(filename);
    if (file.is_open()) {
        // leer la primera linea 
        string line;
        int n_coins;
        file >> n_coins;
        
        for (int i = 0; i < n_coins; i++)
        {
            int coin;
            file >> coin;
            coins.push_back(coin);
        }
        
        file.close();
    }
}
int bascula(int inicio, int fin, const vector<int>& pesos) {
    int suma = 0;
    for (int i = inicio; i <= fin; i++) suma += pesos[i];
    return suma;
}
// algoritmo para encontrar la moneda falsa , complejidad O(log(n))
int fake_coin(const vector<int>& pesos, int Li, int Lf, int Ri, int Rf, int pos) {

    // simulamos la bascula
    int left = bascula(Li, Lf, pesos);
    int right = bascula(Ri, Rf, pesos);

    // std::cout << "Li: " << Li << " Lf: " << Lf << " Ri: " << Ri << " Rf: " << Rf << " pos: " << pos <<"->"<<pesos[pos]<< endl;
    // std::cout << "left: " << left << " right: " << right << endl;
   
    // casos base : la posiicion es la moneda falsa
    if (left == right) return pos;

    // Se revisa en que lado de la bascula esta la moneda falsa
    if(right < left) { 
            // Si la cantidad de monedas es impar
        if((Rf - Ri)%2==0)
        {
            pos = Ri + (Rf - Ri)/2;
            
            Li = Ri;
            Lf = pos-1;
            Ri = pos+1;

            
        }
        else
        {                                            // si la cantidad de monedas es par
            
            pos = Ri + (Rf-1 - Ri)/2;
            
            Li = Ri;
            Lf = pos;
            Ri = pos+1;
            
        }
        
    } else {
            
        if((Lf - Li)%2==0){                         // Si la cantidad de monedas es impar
            pos = Li + (Lf - Li)/2;
            
            Ri = Li;
            Rf = pos-1;
            Li = pos+1;
            
        }
        else{                                      // si la cantidad de monedas es par
            pos = Li + (Lf-1 - Li)/2;
            
            Ri = Li;
            Rf = pos;
            Li = pos+1;
            
        }
       
    }

    return fake_coin(pesos, Li, Lf, Ri, Rf, pos);
}

int main() {
    /*
       Algoritmo para fake-coin.
    */ 
    vector<int> pesos;
    string filename = "coins.txt";
    fill(filename, pesos);

    // mostramos el numero de monedas
    std::cout << "Numero de monedas: " << pesos.size() << endl;
    // mostramos el peso de las monedas
    for (int i = 0; i < pesos.size(); i++) std::cout << pesos[i] << " ";
    std::cout << endl;
    // buscamos la moneda falsa (si es una cantidad impar de monedas)

    if (pesos.size() % 2 != 0) {
        int pos = fake_coin(pesos, 0, (pesos.size()-1)/2-1, (pesos.size()+1)/2, pesos.size()-1, (pesos.size()-1)/2);
        std::cout << "La moneda falsa es la numero " << pos+1 << endl;
    } else {
    
        int pos = fake_coin(pesos, 0, pesos.size()/2-1, pesos.size()/2, pesos.size()-1, pesos.size()/2);
        std::cout << "La moneda falsa es la numero " << pos+1 << endl;
    }
    // mostramos el resultado
    
}