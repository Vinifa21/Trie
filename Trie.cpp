// Árvore digital (cada nível é referente a um dígito do key)
// altura depende da quantidade de digitos da chave/
// filho a esq = 0 dir = 1
// sobre o INSERE: uma chave será inserida na primeira posição livre, (válida para seus bits)
// valido pois todas as subarvores no nivel k, possui k-1 bits iniciais identicos
//delete: um nó folha pode ser colocado em qualquer posição do caminho que leve até ele

struct Node{
    Node* p; // aponta para o pai
    Node* left; // representa que próx digito é 0
    Node* right; // representa que próx digito é 1
    string key;

};

class Trie{
public:
    Node* root;

    Trie(){
      root = nullptr;
      };
    ~Trie() {
        delete root;
    }

    Node * verifica_filho(Node* current, char c) {
        // retorna o próx filho que irei acessar, de acordo com c
        if( c == '0') {
            return  current->left;
        }
        else {
           return current->right;
        }
    }

    bool busca(string key) {
        Node* current = this->root; // nó atual (começa na root)
        int n_digitos = key.length();

        for(int i = 0; i < n_digitos; i++) { // for percorre todos os digitos da key a ser encontrada
            char c = key[i]; // digito atual
            Node* proximo_filho = verifica_filho(current, c);

            if(current->key != key) { // entra aqui caso current nao for a key correta
                current = proximo_filho;
            }
            else { // caso ache o nó na trie
                return true; }
            if( current == nullptr) { // caso nó não esteja na trie
                return false; }
        }


    }

    bool insere(string key) {

        // se nó a ser inserido for a raiz
        if(this->root == nullptr) {
            this->root = new Node();
            this->root->key = key;
            this->root->left = nullptr;
            this->root->right = nullptr;
            this->root->p = nullptr;
            return true;
        }

        Node* current = this->root;
        int n_digitos = key.length();
        Node* proximo_filho;

        for(int i = 0; i < n_digitos; i++) {
            char c = key[i];
            proximo_filho = verifica_filho(current, c);

            if(current->key == key) {
                cout << "Node ja existente na Trie";
                return false;
            }
            if(proximo_filho == nullptr) {
                proximo_filho = new Node;
                if(c == '0') {
                    current->left = proximo_filho;
                }
                else {
                    current->right = proximo_filho;
                }

                break; // achei o endereço da chave (está em proximo_filho)
            }
            current = proximo_filho; // desço na árvore
        }
        // preencho o novo node
        proximo_filho->p = current;
        proximo_filho->key = key;
        proximo_filho->left = nullptr;
        proximo_filho->right = nullptr;
        return true;
    }

    int alturaTrie(Node* current) {
        if(current == nullptr) {// caso base da recursão
            return 0;
        }
        else {
            return 1 + max(alturaTrie(current->left), alturaTrie(current->right));
        }
    }

    int altura() {
        return alturaTrie(this->root);
    }

    void printTrie(Node* node, string prefix = "", bool isLeft = true) {
        if (node == nullptr) return;

        // Primeiro imprime o filho da direita (1) para aparecer no topo
        printTrie(node->right, prefix + (isLeft ? "   " : "    "), false);

        // Imprime o nó atual
        cout << prefix;
        cout << (isLeft ? " " : " ");
        cout << (node->key.empty() ? "(vazio)" : node->key) << endl;

        // Depois imprime o filho da esquerda (0)
        printTrie(node->left, prefix + (isLeft ? "    " : "   "), true);
    }

    void print() {
        printTrie(this->root);
    }

    bool remove(string key) {
        Node* current = this->root;
        int n_digitos = key.length();
        Node* alvo = nullptr;

        // for percorre todos os digitos da key a ser encontrada
        for (int i = 0; i < n_digitos && current != nullptr; i++) {
            if (current->key == key) {
                alvo = current;
                break;
            }
            char c = key[i]; // digito atual
            current = verifica_filho(current, c);
        }

        if (alvo == nullptr || alvo->key != key) return false; // caso nó não esteja na trie

        if (alvo->left == nullptr && alvo->right == nullptr) {
            // se node é folha
            Node* pai = alvo->p;
            if (pai != nullptr) {
                if (pai->left == alvo) pai->left = nullptr;
                else if (pai->right == alvo) pai->right = nullptr;
            } else {
                this->root = nullptr; // era a raiz
            }
            delete alvo; // apago o nó
            return true;
        } else {
            Node* aux = alvo;
            char c = 'L';
            // enquanto ainda tiver nós a serem percorridos (até chegar na folha)
            while (aux->left != nullptr || aux->right != nullptr) {
                if (aux->left != nullptr) {
                    aux = aux->left;
                    c = '0';
                } else {
                    aux = aux->right;
                    c = '1';
                }
            }
            // aux é a folha mais profunda que pertence ao caminho do nó que será deletado
            alvo->key = aux->key; // chave no endeço de alvo recebe a chave da folha

            if (c == '0')
                aux->p->left = nullptr;
            else if (c == '1')
                aux->p->right = nullptr;

            delete aux; // deleto aux (folha), s key agr está no endereço de alvo (cuja key foi deletada)
            return true;
        }

    }

};
