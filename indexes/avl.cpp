#ifndef AVLTree_H
#define AVLTree_H
#include<iostream>
#include<cstring>
#include <sstream>

using namespace std;

template <typename TK, typename TV>
struct NodeAVL{
    std::pair<TK,TV> pair;
    //TK data;

    int height;
    NodeAVL* left;
    NodeAVL* right;

    //Default constructor
    NodeAVL() {}
    //Constructor con 3 parametros (Data,L,R)
    NodeAVL(std::pair<TK,TV> value, NodeAVL *left, NodeAVL *right) : pair(value), left(left), right(right), height(0) {}
    //Constructor con 4 parametros (Data,L,R,Height)
    NodeAVL(std::pair<TK,TV> value, int height, NodeAVL *left, NodeAVL *right) : pair(value), height(height), left(left), right(right) {}

    void killSelf(){
        if(this->left != nullptr){
            this->left->killSelf();
        }
        if(this->right != nullptr){
            this->right->killSelf();
        }
        delete this;
    }
};

template<typename TK, typename TV>
class AVLTree{
private:
    NodeAVL<TK,TV>* root;
public:
    AVLTree(): root(nullptr) {}

    //Muestra los elementos en orden aplicando el algoritmo de (InOrder)
    void DisplayInOrderAVLTree(){
        return DisplayInOrderAVLTree(root);
    };

    bool find(TK value, TV trans){
        return find(root, value);
    }

    string getPreOrder(){
        return getPreOrder(root);
    }

    TK minValue(){
        return minValue(root);
    }
    TK maxValue(){
        return maxValue(root);
    }
    bool isBalanced(){
        return isBalanced(root);
    }
    int size(){
        return size(root);
    }

    void remove(TK value, TV trans){
        remove(root, value);
        recorreYbalancea(root);
    }

    void recorreYbalancea(){
        return recorreYbalancea(root);
    }

    //Obtiene la altura de manera recursiva del nodo en cuestion
    int height(){
        return height(root);
    }

    //Muestra el arbolito bien bonito con un algoritmo Pretty
    void printBT(){
        return printBST("",root,false);
    }

    //Inserta un elemento en el arbolito (Recorre desde la raiz)
    void insert(TK value, TV trans){
        return insert(root, value, trans);
    }

    //Actualiza la altura del nodo en cuestion
    void UpdateHeight(NodeAVL<TK,TV>* &node){
        node->height = max(height(node->left), height(node->right)) + 1;
        //La altura del nodo se obtiene de la maxima altura entre del hijo izquierdo (Lesser) y el hijo derecho (Greater)
    }

    //Aplica rotacion hacia la izquierda del nodo que desees (Utilizando P, Q, T como referencia de los nodos hijo y nieto)
    //Se da cuando existe un Balance_Factor con signo (-) (Lesser) Rotation
    void LeftRotation(NodeAVL<TK,TV>* &node){
        NodeAVL<TK,TV> *p = node; //p es Nodo actual
        NodeAVL<TK,TV> *q = p->right; //q es el hijo derecho de p (->)(Greater node child)
        NodeAVL<TK,TV> *t = q->left; //t es el hijo izquierdo de q (<-)(Lesser node grandchild)
        q->left = p; //El hijo izquierdo de q se vuelve p (<-) (The lesser child of q is now p)
        p->right = t; //El hijo derecho de p se vuelve t (->) (The greater child of p is now t)
        node = q;
        UpdateHeight(node);
    }

    //Aplica rotacion hacia la derecha del nodo que desees (Utilizando P, Q, T como referencia de los nodos hijo y nieto)
    //Se da cuando existe un Balance_Factor con signo (+) (Greater) Rotation
    void RightRotation(NodeAVL<TK,TV>* &node){
        NodeAVL<TK,TV> *p = node; //p es Nodo actual
        NodeAVL<TK,TV> *q = p->left; //q es el hijo izquierda de p (<-)(Lesser node child)
        NodeAVL<TK,TV> *t = q->right; //t es el hijo derecho de q (->)(Greater node grandchild)
        q->right = p; //El hijo derecho de q se vuelve p (->) (The greater child of q is now p)
        p->left = t; //El hijo izquierdo de p se vuelve t (<-) (The lesser child of p is now t)
        node = q;
        UpdateHeight(node);
    }

    //Retorna el factor de balanceo del nodo que desees (Resta de ambas alturas de los hijos)
    int Balance_Factor(NodeAVL<TK,TV>* node){
        return (height(node->left)- height(node->right));
        /*
            Si sale + (Esta desbalanceado hacía la izquierda) (<-) (Lesser desbalance)
            Si sale - (Esta desbalanceado hacía la derecha) (->) (Greater desbalance)
            Si sale 0 (Esta balanceado) (No desbalance)
        */
    }

    //Balancea cada nodo que esta desbalanceado, ya sea aplicando rotacion simple o rotacion doble
    void Letsbalance(NodeAVL<TK,TV>* &node){
        int nodebalancefactor = Balance_Factor(node);
        if(nodebalancefactor >= 2) { // ¿Esta desbalanceado hacia la izquierda (<-)? ¿Node Lesser desbalance?
            if(Balance_Factor(node->left) <= -1) { //¿Su hijo esta desbalanceado hacia la derecha (->)? ¿Child Greater desbalance?
                LeftRotation(node->left); //Rotacion del hijo hacia la izquierda (<-) (Child Lesser rotation)
            }
            RightRotation(node); //Rotacion del nodo actual hacia la derecha (->) (Node Greater rotation)
        }
        if(nodebalancefactor <= -2) { //¿Esta desbalanceado hacia la derecha (->)? ¿Node Greater desbalance?
            if(Balance_Factor(node->right) >= 1){ // ¿Su hijo esta desbalanceado hacia la izquierda (<-)? ¿Child Lesser desbalance?
                RightRotation(node->right); //Rotacion del hijo hacia la derecha (->) (Child Greater rotation)
            }
            LeftRotation(node); //Rotacion del nodo actual hacia la izquierda (<-) (Node Lesser rotation)
        }
    }

    ~AVLTree(){
        if(root != nullptr){
            root->killSelf();
        }
    }

private:
    void recorreYbalancea(NodeAVL<TK,TV>* &root){
        if(root != nullptr){
            UpdateHeight(root);
            Letsbalance(root);
            recorreYbalancea(root->left);
            recorreYbalancea(root->right);
        }
    }

    int height(NodeAVL<TK,TV>* node){
        if(node != nullptr) {
            int hl = height(node->left); //Obtiene la altura del subarbol izquierdo (<-) (Lesser)
            int hr = height(node->right); //Obtiene la altura del subarbol derecho (->) (Greater)
            return max(hl, hr) + 1;
        }else{
            return -1; //Si no existe el nodo tiene altura -1
        }
    }

    void remove(NodeAVL<TK,TV>* &node, TK value){
        if(node == nullptr){
            return;
        }else{
            if (value < node->pair.first) {
                remove(node->left, value);
            } else if (value > node->pair.first) {
                remove(node->right, value);
            }else {
                //Caso 1 => Tiene 0 hijos
                if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    node = nullptr;
                }
                    //Caso 2 => Tiene 1 hijos (Izq-Der)
                else if (node->left != nullptr && node->right == nullptr) {
                    NodeAVL<TK,TV>* temp = node->left;
                    delete node;
                    node = temp;

                } else if (node->left == nullptr && node->right != nullptr) {
                    NodeAVL<TK,TV> *temp = node->right;
                    delete node;
                    node = temp;

                }
                    //Caso 3 => Tiene 2 hijos
                else {
                    TK temp = maxValue(node->left);
                    node->pair.first = temp;
                    remove(node->left, temp);
                }
            }
        }
    }

    bool isBalanced(NodeAVL<TK,TV>* node){
        if (node == nullptr) {
            return true;
        }

        int hl = height(node->left);
        int hr = height(node->right);

        return abs(hl-hr)<=1 && isBalanced(node->left) && isBalanced(node->right);
    }

    int size(NodeAVL<TK,TV>* node){
        if(node == nullptr){
            return 0;
        }else{
            return 1 + size(node->left) + size(node->right);
        }
    }

    TK minValue(NodeAVL<TK,TV>* node){
        if(node == nullptr){
            cout<<"The tree is empty"<<endl;
            throw("Empty tree");
        }else{
            if(node->left != nullptr){
                return minValue(node->left);
            }else{
                return node->data;
            }
        }
    }
    TK maxValue(NodeAVL<TK,TV>* node){
        if(node == nullptr){
            cout<<"The tree is empty"<<endl;
            throw("Empty tree");
        }else{
            if(node->right != nullptr){
                return maxValue(node->right);
            }else{
                return node->pair.first;
            }
        }
    }


    string getPreOrder(NodeAVL<TK,TV>* node) {
        stringstream disp;
        if (node != nullptr) {
            disp << node->data << " ";
            disp << getPreOrder(node->left);
            disp << getPreOrder(node->right);
        }
        return disp.str();

    }


    bool find(NodeAVL<TK,TV>*node, TK value){
        if(node == nullptr){
            return false;
        }else if(value < node->data){
            return find(node->left, value);
        }else if(value > node->data){
            return find(node->right, value);
        }else {
            return true;
        }
    }

    void DisplayInOrderAVLTree(NodeAVL<TK,TV>*node){
        if(node == nullptr){
            return;
        }
        displayorder(node->left);
        cout<<node->data<<" ";
        displayorder(node->right);
    }

    void printBST(const std::string& prefix, const NodeAVL<TK,TV>* node, bool isLeft)
    {
        if (node != nullptr)
        {
            cout << prefix;
            cout << (isLeft ? "|--" : "L--");
            // print the value of the node
            cout << node->pair.first << "," << node->pair.second << endl;
            // enter the next tree level - left and right branch
            printBST(prefix + (isLeft ? "|   " : "    "), node->right, true);
            printBST(prefix + (isLeft ? "|   " : "    "), node->left, false);
        }
    }

    void insert(NodeAVL<TK,TV>*& node, TK key, TV value){
        if(node == nullptr) {
            node = new NodeAVL<TK,TV>();
            node->pair.first = key;
            node->pair.second = value;
            node->left = nullptr;
            node->right = nullptr;
            node->height = height(node);
        }else if(key < node->pair.first){
            insert(node->left, key, value);
        }else if(key > node->pair.first){
            insert(node->right, key, value);
        }else{
            return;
        }
        UpdateHeight(node);
        Letsbalance(node);
    }
};

#endif
