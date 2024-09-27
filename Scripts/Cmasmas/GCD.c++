//-------------------
#include <iostream>
#include <string>
//-------------------

using namespace std;

int iterativo (long a , long b ) { 
    
    return 0;
}

long recursivo (long a, long b) { 

    if (b == 0) { 
        return a;
    } else { 

        //cout<<'\n'<<a<<"\t"<<b<<"\t|\t"<<(a%b);

        return recursivo(b , (a%b)); 

    }

}
int main(){
    cout<<"Este es el algoritmo de auclides"<<endl;

    cout<<"Buscando comun divsor 55 y 34 \n";
    //cout<<"Buscando comun divsor 55 y 34 \na\tb\t\ta%b";

    long ans = recursivo(55,34); 

    cout<<"\nEl maximo comun divisor es : "<< ans;
}


