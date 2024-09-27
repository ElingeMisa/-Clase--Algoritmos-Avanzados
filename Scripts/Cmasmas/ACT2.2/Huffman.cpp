#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class Node {
public:
    
    bool isLeaf;
    char ch;
    int freq;
    float prob;
    
    string code;
    
    Node *left, *right;
    
    Node(bool isleaf,char ch, int freq, Node *left, Node *right) :isLeaf(isleaf), ch(ch), freq(freq), left(left), right(right) {}
    
    bool operator>(const Node &node) const {return freq > node.freq;}

};

class huffman_tree {
public:
    Node *root;
};

class all_huffman {
private:

    long long pool;

    bool visited[300];
    
    
    vector<Node*> nodes;

    huffman_tree tree;

public:

    all_huffman() {
        pool = 0;
        nodes.push_back(new Node(false, '#', 0, nullptr, nullptr));
        nodes[nodes.size()-1]->prob = 3;

        for(int i = 0; i < 300; i++) {visited[i] = false;}


    }

    void fill_nodes_file(string filename){
        
        ifstream file(filename);
            string line;
            // leer el archivo linea por linea
            while (getline(file, line)) {

                pool+=line.size();
                    //cout << line << endl;
                for(int ch = 0; ch<line.size(); ch++){
                    char this_char = line[ch];
                        //cout<<line[ch]<<"]";
                    if (visited[line[ch]] == false) {
                            //cout << "[Caracter: " << ch << "] ";
                        visited[line[ch]] = true;
                        Node* node = new Node(true, line[ch], 1, nullptr, nullptr);
                        nodes.push_back(node);
                            //cout << " Nodo: " << nodes_dir[ch]->ch << " Frecuencia: " << nodes_dir[ch]->freq <<" ]"<< endl;
                    } else if (visited[line[ch]] == true) {
                        for(int i = 0; i < nodes.size(); i++){
                            if(nodes[i]->ch == ch){
                                nodes[i]->freq++;
                                break;
                            }
                        }

                    }
                }
            }

        file.close();

        for(int i = 0; i < nodes.size(); i++)   {nodes[i]->prob = (((float)nodes[i]->freq) / ((float)pool));}

        /*
            for(int i = 0; i < nodes.size(); i++){
                cout << "Nodo: " << nodes[i].ch << " Frecuencia: " << nodes[i].freq << endl;
            }
        */

    }

    void merge_nodes(){

        
        
    }

    void print_tree(){print_tree_aux(nodes[0], "*");}

    void print_tree_aux(Node *node, string code){
        if(node->isLeaf){
            cout << "\tCaracter: [" << node->ch << "] Frecuencia: [" << node->freq << "] Codigo: " << code << endl;
        }else{

            if(node->left != nullptr)   {print_tree_aux(node->left, code + "0");}
            if(node->right != nullptr)  {print_tree_aux(node->right, code + "1");}
        }
    }

    void print_characters(){
        string trash;
        cout << "Mostrando la lista de caracteres...\n\t[presione enter para continuar]";
        cin>>trash;
        for(int i = 0; i < nodes.size(); i++){
            if (nodes[i]->isLeaf) {cout << "\t\tCaracter: [" << nodes[i]->ch << "]\tFrecuencia: [" << nodes[i]->freq << "]\tProbabilidad: [" << nodes[i]->prob << "]\n" << endl;}
        }
    }
};

int main() {
    all_huffman mi_huffman;

    string filenae;
    int option;
    bool visited[256];

    do {
        cout <<"Seleccione una opcion: \n\n  [1]\tCodificar un archivo\n  [2]\tDecodificar un archivo\n  [3]\tMostrar una lista de los caracteres, con sus ocurrencias, probabilidades y códigos\n  [4]\tCodificar un texto\n  [5]\tDecodificar un texto\n  [6]\tMostrar el arbol\n  [7]\tSalir\n\n";
        cin >> option;

        string user_text; // Declare user_text before the switch statement

        // Swqitch case para las opciones
        switch (option) {
            case 1:

                cout << "Ingrese el nombre del archivo a codificar: ";
                cin >> filenae;

                cout << "\n\tCodificando archivo...\n";

                mi_huffman.fill_nodes_file(filenae);
                cout <<"\t\t[Nodos llenados]\n";

                mi_huffman.merge_nodes();

                break;
            case 2:
                cout << "Ingrese el nombre del archivo a decodificar: ";
                cin >> filenae;

                //mi_huffman.decode_file();
                break;
            case 3:
                
                mi_huffman.print_characters();
                break;
            case 4:
                cout << "Ingrese el texto a codificar: ";
                cin >> user_text;
                break;
            case 5:
                cout << "Ingrese el texto a decodificar: ";
                cin >> user_text;
                break;
            case 6:
                cout << "Mostrando el arbol...\n";
                mi_huffman.print_tree();
                break;
            case 7:
                cout << "Saliendo...";
                break;
            default:
                cout << "Opcion no valida";
                break;
        }
        /////////////////////////////////////

    } while (option != 7);

}