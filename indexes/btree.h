#ifndef BTree_H
#define BTree_H
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <cmath>
#include <vector>
#include <queue>
#include <functional>
#include "node.h"

using namespace std;

template <typename TK>
class BTree {
  private:
	Node<TK>* root;
	int M;  // grado u orden del arbol
	int n; // total de elementos en el arbol 
	std::function<bool(const TK &, const TK &)> less;
    std::function<bool(const TK &, const TK &)> greater;
    std::function<bool(const TK &, const TK &)> equal; 

	TK minKey(Node<TK>* node) {
    	Node<TK>* temp = node;
    	while(!temp->leaf){
    		temp = temp->children[0];
    	}
    	return temp->keys[0];
  	}

  	TK maxKey(Node<TK>* node) {
		Node<TK>* temp = node;
		while(!temp->leaf){
		temp = temp->children[temp->count];
		}
		return temp->keys[temp->count-1];
	}

	void join_izquierdo(Node<TK>* &izquierdo, TK union_value, Node<TK>* &derecho) {
		izquierdo->keys[izquierdo->count] = union_value;
		izquierdo->count++;

		for (int i =  0; i < derecho->count; i++) {
			izquierdo->keys[izquierdo->count + i] = derecho->keys[i];
			izquierdo->count++;
		}

		if (!derecho->leaf) {
			for (int i = 0; i < derecho->count + 1; i++) {
				izquierdo->children[izquierdo->count + i] = derecho->children[i];
			}
		}
		derecho = nullptr;
	}

	void misplace(Node<TK>* &node, TK key){
    	int i = 0;
      	while (node->keys[i] != key) {
        	i++;
      	}

      	while (i < node->count - 1) {
        	node->keys[i] = node->keys[i+1];
        	i++;
      	}
      	node->keys[i] = (int) NULL;
      	node->count--;
    }

	void remove(Node<TK> *&node, TK key)
	{
		// hallar la posicion de la llave
		int i = 0;
		while (i < node->count && greater(key, node->keys[i]))
			i++;

		if (node->leaf)
		{
			// caso 0
			if (i < node->count && equal(node->keys[i], key))
			{
				misplace(node, key);
			}
		}
		else
		{
			int pos = i;
			// caso 3
			if (i < node->count && equal(node->keys[i], key))
			{
				TK sucesor = minKey(node->children[i + 1]);
				node->keys[i] = sucesor;
				remove(node->children[i + 1], sucesor);
				pos = i + 1;
			}
			else
			{
				remove(node->children[pos], key);
			}
			if (node->children[pos]->count < (M - 1) / 2)
			{
				if (!(pos > 0 && node->children[pos - 1]->count > (M - 1) / 2) && (pos < M - 2 && node->children[pos + 1]->count > (M - 1) / 2))
				{
					node->children[pos]->keys[node->children[pos]->count] = node->keys[pos];
					node->children[pos]->count++;

					TK temp = node->keys[pos];
					node->keys[pos] = node->children[pos + 1]->keys[0];

					misplace(node->children[pos + 1], node->children[pos + 1]->keys[0]);
				}
				else
				{
					// caso 2: join con cualquiera
					// TODO
					int temp = pos;
					if (temp == 0)
					{
						temp++; // si no tiene nodo izquierdo que una el siguiente con su izquierdo
					}
					TK unionKey = node->keys[temp - 1];
					join_izquierdo(node->children[temp - 1], unionKey, node->children[temp]);
					misplace(node, node->keys[temp - 1]);
				}
			}
		}
		if (this->root->count == 0 && this->root->leaf != true)
		{
			this->root = this->root->children[0];
		}
	}

	bool search(Node<TK>* node, TK key){
		int cont = 0;
		while (cont < node->count && greater(key, node->keys[cont])){
		cont++;
		}

		if (equal(node->keys[cont], key)){
		return true;
		}

		if (node->leaf == true){
		return false;
		}

		return search(node->children[cont], key);
	}

	string toString(Node<TK>* node, const string& sep){
		string result = "";
		int i;
		for (i=0; i < node->count; i++){
			if (node->leaf != true)
				result += toString(node->children[i], sep);
			result += std::to_string(node->keys[i]) + sep;
		}
		if (node->leaf != true)
		result += toString(node->children[i], sep);
		return result;
	}

	public:
	BTree(int _M) : root(nullptr), M(_M), n(0) {}
	BTree(int _M,
		std::function<bool(const TK &, const TK &)> _less,
    	std::function<bool(const TK &, const TK &)> _greater,
		std::function<bool(const TK &, const TK &)> _equal):
		root(nullptr), M(_M), n(0) {
			this->less = _less;
    		this->greater = _greater;
    		this->equal = _equal;
		}

	bool search(TK key);//indica si se encuentra o no un elemento ||||  (terminado)
	void insert(TK key); //inserta un elemento |||| (terminado)
	void remove(TK key);//elimina un elemento |||| (falta)
	int height();//altura del arbol. Considerar altura 0 para arbol vacio |||| (terminado)
	string toString(const string& sep);  // recorrido inorder |||| (terminado)
	void display_pretty() {
		this->display_pretty(this->root);
	}

	TK minKey();  // minimo valor de la llave en el arbol |||| (terminado)
	TK maxKey();  // maximo valor de la llave en el arbol |||| (terminado)
	void clear(); // eliminar todos lo elementos del arbol |||| (terminado)
	int size();   // retorna el total de elementos insertados |||| (terminado)
	~BTree(){    // liberar memoria |||| (terminado)
		root->killSelf();
		n = 0;
	}
};

template <typename TK>
bool BTree<TK>::search(TK key) {
  return search(root, key);
}

template<typename TK>
void BTree<TK>::insert(TK key){
  n++;
  if(root==nullptr){
    root=new Node<TK>(M, true, less, greater, equal);
    root->keys[0]=key;
    root->count=1;
    }
  else{
    root= root->insert(key,root,root);
  }
}

template <typename TK>
void BTree<TK>::remove(TK key) {
	if (this->search(key)){
		n--;
		this->remove(this->root, key);
	}
	return;
}

template <typename TK>
int BTree<TK>::height() {
  int count = 0;
  if (root == nullptr){
	return count;
  }
  Node<TK>* temp = this->root;

  while(temp->leaf != true){
    count++;
    temp = temp->children[0];
  }
  return count;
}

template <typename TK>
string BTree<TK>::toString(const string& sep) {
  string result = toString(root, sep);
  return result.substr(0,result.size() - sep.size());
} 

template <typename TK>
TK BTree<TK>::minKey() {
  return this->minKey(this->root);
}

template <typename TK>
TK BTree<TK>::maxKey() {
  return this->maxKey(this->root);
}

template <typename TK>
void BTree<TK>::clear() {
  root->killSelf();
  root = nullptr;
  n = 0;
}

template <typename TK>
int BTree<TK>::size() {
  return n;
}

#endif
