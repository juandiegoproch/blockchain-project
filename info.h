#include <string>
#include "./indexes/btree.h"
#include "blockchain.h"
#include "list.h"
#include "transaction.h"

using namespace std;

class Information {
    //necesito mandar la info de la transaccion
    //estoy suponiendo q se manda con la estructura de la list.h
    //SinglyLinkedList<Transaction*> info;
    //vector<Block*> infom;
    BTree<Transaction*>* order_by_moment;
    BTree<Transaction*>* order_by_ammount;

    public:
    Information() {
        this->order_by_moment = new BTree<Transaction*>(15,
            [](const Transaction *first, const Transaction *second) {return first->moment < second->moment;},
            [](const Transaction *first, const Transaction *second) {return second->moment < first->moment;},
            [](const Transaction *first, const Transaction *second) {return second->moment == first->moment;}
            );

        this->order_by_ammount = new BTree<Transaction*>(15,
            [](const Transaction *first, const Transaction *second) {return first->ammount < second->ammount;},
            [](const Transaction *first, const Transaction *second) {return second->ammount < first->ammount;},
            [](const Transaction *first, const Transaction *second) {return second->ammount == first->ammount;}
            );
    };

    auto get_btree_moment(){
        return this->order_by_moment;
    }

    auto get_btree_ammount(){
        return this->order_by_ammount;
    }

    void new_transaction(Transaction* transaction) {
        //not sure how we are pushing seb
        //this->info.push_front(transaction);
        //this->infom.push(transaction)
        this->order_by_moment->insert(transaction);
        this->order_by_ammount->insert(transaction);
        }

    Transaction* recient_transaction() {
        return order_by_date->maxKey();
    }

    Transaction* biggest_transaction() {
        return order_by_amount->maxKey();
    }

};  