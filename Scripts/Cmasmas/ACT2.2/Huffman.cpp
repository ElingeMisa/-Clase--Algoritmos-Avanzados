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

    map<char, string> codes;
    map<char, bool> visited;
    
    vector<Node> nodes;

    huffman_tree tree;

public:

    all_huffman() {
        pool = 0;
        
        for(int i = 0; i < 300; i++) {visited[i] = false;}

    }

    void fill_nodes_text(string text){
        // vaciamos el vector de nodos
        nodes.clear();

        map<char, int> freq_map;
        for (char ch : text) {
            if (freq_map.find(ch) == freq_map.end()) {
                freq_map[ch] = 1;
            } else {
                freq_map[ch]++;
            }
            pool++;
        }

        for (auto &pair : freq_map) {
            nodes.push_back(Node(true, pair.first, pair.second, nullptr, nullptr));
        }

        for(int i = 0; i < nodes.size(); i++)   {nodes[i].prob = (((float)nodes[i].freq) / ((float)pool));}


    }

    void fill_nodes_file(string filename){
        // vaciamos el vector de nodos
        nodes.clear();

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo: " << filename << endl;
            return;
        }

        map<char, int> freq_map;
        char ch;
        while (file.get(ch)) {
            if (freq_map.find(ch) == freq_map.end()) {
                freq_map[ch] = 1;
            } else {
                freq_map[ch]++;
            }
            pool++;
        }

        file.close();

        for (auto &pair : freq_map) {
            nodes.push_back(Node(true, pair.first, pair.second, nullptr, nullptr));
        }

        for(int i = 0; i < nodes.size(); i++)   {nodes[i].prob = (((float)nodes[i].freq) / ((float)pool));}

    }

    void merge_nodes() {
        // Cambiar la función de comparación para ordenar por frecuencia
        auto compare = [](Node* left, Node* right) { return left->freq > right->freq; };
        priority_queue<Node*, vector<Node*>, decltype(compare)> pq(compare);

        // Crear nodos dinámicos y almacenarlos en la cola de prioridad
        for (auto& node : nodes) {
            pq.push(new Node(node.isLeaf, node.ch, node.freq, nullptr, nullptr));
        }

        while (pq.size() > 1) {
            // Extraemos los dos nodos con menor frecuencia
            Node* left = pq.top();
            pq.pop();
            Node* right = pq.top();
            pq.pop();

            // Asegurarse de que el nodo con mayor frecuencia quede a la derecha
            if (left->freq > right->freq) {
                swap(left, right);  // Intercambiamos para que el nodo con mayor frecuencia quede a la derecha
            }

            // Crear el nodo padre y asignar los hijos
            Node* parent = new Node(false, '#', left->freq + right->freq, left, right);
            parent->prob = left->prob + right->prob;  // La probabilidad se sigue sumando igual que antes
            pq.push(parent);
        }

        tree.root = pq.top();

        // Limpiar y liberar la memoria de los nodos
        nodes.clear();
        nodes.push_back(*tree.root);
        
        fill_codes();
    }

    void fill_codes() {
        fill_codes_aux(tree.root, "");
    }
    
    void fill_codes_aux(Node* node, string code) {
        if (node->isLeaf) {
            codes[node->ch] = code;
            node->code = code;
            return;
        }
        if (node->left != nullptr) {
            fill_codes_aux(node->left, code + "0");
        }
        if (node->right != nullptr) {
            fill_codes_aux(node->right, code + "1");
        }
        
    }

    void print_tree(){

        if (nodes.size() == 0) {
            cout << "No hay nodos en el arbol" << endl;
            return;
        }else{
            if(nodes[0].left != nullptr)   {print_tree_aux(nodes[0].left);}
            if(nodes[0].right != nullptr)  {print_tree_aux(nodes[0].right);}
        }
            
    }

    void print_tree_aux(Node* node){
        if(node->isLeaf){
            cout << "\tCaracter: [" << node->ch << "] Frecuencia: [" << node->freq << "] Codigo: " << node->code << endl;
        }else{
            
            if(node->left != nullptr)   {print_tree_aux(node->left);}
            if(node->right != nullptr)  {print_tree_aux(node->right);}
        }
    }

    void print_characters(){
        string trash;
        float pool_prob = 0;
        cout << "Mostrando la lista de caracteres...\n\n";
        
        if(nodes.size() > 2){

            for(int i = 0; i < nodes.size(); i++){
                if (nodes[i].isLeaf) {cout<<"[" << i <<"] Caracter: [" << nodes[i].ch << "]\tFrecuencia: \t[" << nodes[i].freq << "]\tProbabilidad: [" << nodes[i].prob << "]\t Codigo: ["<<nodes[i].code <<"]\n";}
                pool_prob += nodes[i].prob;
            }
            
            cout << "Probabilidad total: " << pool_prob << endl;

        }else{
            print_tree();
        }

    }

    void encode_file(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo: " << filename << endl;
            return;
        }

        ofstream output_file(filename + "_encoded.txt");
        if (!output_file.is_open()) {
            cerr << "No se pudo abrir el archivo de salida: file_salida" << endl;
            return;
        }

        char ch;
        while (file.get(ch)) {
            if (codes.find(ch) != codes.end()) {
                output_file << codes[ch] << " ";
                if (ch == '\n') {output_file << endl;}
            } else {
                cerr << "Caracter no encontrado en el mapa de códigos: " << ch << endl;
            }
        }

        file.close();
        output_file.close();
    }
    
    bool decode_file(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo: " << filename << endl;
            return false;
        }

        string output_filename = filename.substr(0, filename.find_last_of('.')) + "_decoded.txt";
        ofstream output_file(output_filename);
        if (!output_file.is_open()) {
            cerr << "No se pudo abrir el archivo de salida: " << output_filename << endl;
            return false;
        }

        string code;
        bool mini_flag = false;
        while (file >> code) {
            for (auto &pair : codes) {
                if (pair.second == code) {
                    output_file << pair.first;
                    mini_flag = true;
                    break;
                }
            }
            if (!mini_flag) {
                cerr << "Código no encontrado en el mapa de códigos: " << code << endl;
            }
            mini_flag = false;
        }

        file.close();
        output_file.close();
    }
    
    void encode_text(string text) {
        
        
        for (char ch : text) {
            if (codes.find(ch) != codes.end()) {
                cout << codes[ch] << " ";
            } else {
                cerr << "Caracter no encontrado en el mapa de códigos: " << ch << endl;
            }
        }
        cout << endl;
        
        
    }

    void decode_text(string text) {
        string code;
        bool mini_flag = false;
        for (int i = 0; i < text.size(); i++) {
            if (text[i] == ' ') {
                for (auto &pair : codes) {
                    if (pair.second == code) {
                        cout << pair.first;
                        mini_flag = true;
                        break;
                    }
                }
                if (!mini_flag) {
                    cerr << "Código no encontrado en el mapa de códigos: " << code << endl;
                }
                code = "";
                mini_flag = false;
            } else {
                code += text[i];
            }
        }
        cout << endl;
    }
};

int main() {
    all_huffman mi_huffman;

    string filenae;
    
    int option;
    bool visited[256];
    bool flag;

    do {
        cout <<"Seleccione una opcion: \n\n  [1]\tCodificar un archivo\n  [2]\tDecodificar un archivo\n  [3]\tMostrar una lista de los caracteres, con sus ocurrencias, probabilidades y códigos\n  [4]\tCodificar un texto\n  [5]\tDecodificar un texto\n  [6]\tMostrar el arbol\n  [7]\tSalir\n\n";
        cin >> option;

        string user_text; // Declare user_text before the switch statement
        string trash = "";

        // Swqitch case para las opciones
        switch (option) {
            case 1:

                cout << "Ingrese el nombre del archivo a codificar: ";
                cin >> filenae;

                cout << "\n\tCodificando archivo...\n";

                cout <<"\t   Llenando Nodos ...\n";
                mi_huffman.fill_nodes_file(filenae);
                cout <<"\t\t[Nodos llenados]\n";
                cout <<"\t   Mergeando nodos ...\n";
                mi_huffman.merge_nodes();
                cout <<"\t\t[Nodos mergeados]\n";
                cout <<"\t   Generando códigos ...\n";
                cout <<"\t\t[Códigos generados]\n";
                cout <<"\t   Guardando archivo ...\n";
                mi_huffman.encode_file(filenae);
                cout <<"\t\t[Archivo guardado]\n";

                //mi_huffman.merge_nodes();

                break;
            case 2:
                cout << "Ingrese el nombre del archivo a decodificar: ";
                cin >> filenae;
                cout << "\n\tDecodificando archivo...\n";
                flag = mi_huffman.decode_file(filenae);
                
                if (flag) {cout << "\t\t[Archivo decodificado correctamente]\n";}
                break;
            case 3:
                
                mi_huffman.print_tree();
                break;
            case 4:
                cout << "Ingrese el texto a codificar en una sola linea porfavor. \n";
                cin.ignore(); // Clear the input buffer
                getline(cin, user_text);
                cout << "\n\tCodificando texto...\n";
                cout <<"\t   Llenando Nodos ...\n";
                mi_huffman.fill_nodes_text(user_text);
                cout <<"\t\t[Nodos llenados]\n";
                cout <<"\t   Mergeando nodos ...\n";
                mi_huffman.merge_nodes();
                cout <<"\t\t[Nodos mergeados]\n";
                cout <<"\t   Generando códigos ...\n";
                cout <<"\t\t[Códigos generados]\n";
                cout << "Texto codificado como: \n";
                mi_huffman.encode_text(user_text);

                break;
            case 5:
                cout << "Ingrese el texto a decodificar: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, user_text);
                cout << "\n\tDecodificando texto...\n";
                mi_huffman.decode_text(user_text);
                
                
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
