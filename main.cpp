#include <iostream>
#include <string>
using namespace std;
//programa que visa implementar uma árvore de busca digital (Trie)
// Posição de um nó depende da comparação entre os bits que compõe as chaves
#include "Trie.cpp"

void preenche_trie( Trie *a) {
    a->insere("10000");
    a->insere("01100");
    a->insere("01111");
    a->insere("01101 ");
    a->insere("00100 ");
    a->insere("10110");
    a->insere("00110");
    a->insere("10101");
    a->insere("11000");
    a->insere("01010");
    a->insere("01001");
    a->insere("00001");
    a->insere("10011");
    a->insere("10111");
    a->insere("10001");
    a->insere("10100");
    a->insere("01011");
    a->insere("00010");
    a->insere("01110");
    a->insere("11010");
    a->insere("00101");
    a->insere("11001");
    a->insere("10010");
    a->insere("00011");
    a->insere("01000");
    a->insere("00111");
}

void delete_trie(Trie *a) {
    a->remove("00001");
    a->remove("00101");
    a->remove("01001");
    a->remove("01111");
    a->remove("10101");
    a->remove("01011");
    a->remove("11000");
    a->remove("10111");
    a->remove("11010");


}

int main(){
    Trie a{};

    preenche_trie(&a);
    cout  << "Altura is : " << a.altura() << endl << "Trie plotada:" << endl;
    a.print();

    cout << endl <<"Trie depois das remocoes:" << endl << endl << endl;

    delete_trie(&a);

    a.print();

    cout << " \n \n \n Nova altura: " << a.altura();

    return 0;
}
