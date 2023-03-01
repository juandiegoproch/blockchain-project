#pragma once

#include "block.h"
#include "transaction.h"
#include <vector>
#include "../indexes/hash.h"
#include "../indexes/trie.h"
#include "../indexes/avl.h"
#include "../indexes/heap.h"


class Blockchain
{
    // important things
    std::vector<Block*> blocks;
    int difficulty;

    // helpfull things
    
    int n_transact;
    int current_block_id;

    // indexes
    HashTable<string, Transaction*> m_hash_from;
    HashTable<string, Transaction*> m_hash_to;

    Patricia<string, Transaction*> m_trie_from;
    Patricia<string, Transaction*> m_trie_to;

    vector<pair<string, Transaction*> > m_vec_from;
    vector<pair<string, Transaction*> > m_vec_to; 

    AVLTree<int, Transaction*> m_avl_amount;
    AVLTree<int, Transaction*> m_avl_moment;

    MaxHeap<int,Transaction*> m_mxheap_ammount;
    MaxHeap<int,Transaction*> m_mxheap_moment;

    MinHeap<int,Transaction*> m_miheap_ammount;
    MinHeap<int,Transaction*> m_miheap_moment;

public:
    Blockchain()
    {
        uint512_t zero;
        zero = 0;
        difficulty = 4;
        current_block_id = 0;
        n_transact = 0;

        Block* firstblock = new Block(current_block_id,zero);
        blocks.push_back(firstblock);
    }

    void push(const Transaction& t) // inserts a new transaction into the last Block in the Blocks vector
    {
        if (n_transact >= BLOCK_TRANSACTION_AMMOUNT)
        {
            // push the block to the blocks vector
            uint512_t old_hash = performPOW();
            blocks[current_block_id]->display();
            Block* newblock = new Block(current_block_id,old_hash);
            blocks.push_back(newblock);

            // new block ready and loaded
            n_transact = 0;
            current_block_id++;
        }

        blocks[current_block_id]->data[n_transact] = t;
        n_transact++;
        // update indexes

        m_hash_from.insert(blocks[current_block_id]->data[n_transact-1].from, addressof(blocks[current_block_id]->data[n_transact-1]));
        m_hash_to.insert(blocks[current_block_id]->data[n_transact-1].to, addressof(blocks[current_block_id]->data[n_transact-1]));

        m_trie_from.insert(blocks[current_block_id]->data[n_transact-1].from, addressof(blocks[current_block_id]->data[n_transact-1]));
        m_trie_to.insert(blocks[current_block_id]->data[n_transact-1].to, addressof(blocks[current_block_id]->data[n_transact-1]));

        m_vec_from.push_back(make_pair(blocks[current_block_id]->data[n_transact-1].from, addressof(blocks[current_block_id]->data[n_transact-1])));
        m_vec_to.push_back(make_pair(blocks[current_block_id]->data[n_transact-1].to, addressof(blocks[current_block_id]->data[n_transact-1])));

        m_avl_amount.insert(blocks[current_block_id]->data[n_transact-1].ammount, addressof(blocks[current_block_id]->data[n_transact-1]));
        m_avl_moment.insert(blocks[current_block_id]->data[n_transact-1].moment, addressof(blocks[current_block_id]->data[n_transact-1]));

        m_mxheap_ammount.insert(blocks[current_block_id]->data[n_transact-1].ammount, addressof(blocks[current_block_id]->data[n_transact-1]));
        m_miheap_ammount.insert(blocks[current_block_id]->data[n_transact-1].ammount, addressof(blocks[current_block_id]->data[n_transact-1]));

        m_mxheap_moment.insert(blocks[current_block_id]->data[n_transact-1].moment, addressof(blocks[current_block_id]->data[n_transact-1]));
        m_miheap_moment.insert(blocks[current_block_id]->data[n_transact-1].moment, addressof(blocks[current_block_id]->data[n_transact-1]));
    
    }

    void display_tree_index(){
        std::cout << "\nm_tree_amount\n";
        m_avl_amount.printBT();
    }

    void display_trie_index(){
        std::cout << "\nm_trie_from\n";
        m_trie_from.display();
        std::cout << "\nm_trie_to\n";
        m_trie_to.display();
    }

    void display_hash_index(){
        std::cout << "\nm_hash_from\n";
        m_hash_from.display();
        std::cout << "\nm_hash_to\n";
        m_hash_to.display();
    }

    void search_from(string searchable){

        std::cout << "\nsearch: " << searchable << "\n";
        std::vector<Transaction*> vec = m_hash_from.search(searchable);
        vec = m_hash_from.search(searchable);
        for(auto ptr = vec.begin(); ptr != vec.end(); ptr++){
            std::cout << to_string(*ptr) << std::endl; // por algun motivo, este puntero apunta a un sitio fuera de donde toca: (alrededor del data[10] del Blocks[4])
        }
        std::cout << "\n\n";
    }

    void search_to(string searchable){
        std::cout << "\nsearch: " << searchable << "\n";
        std::vector<Transaction*> vec = m_hash_to.search(searchable);
        vec = m_hash_to.search(searchable);
        for(auto ptr = vec.begin(); ptr != vec.end(); ptr++){
            std::cout << to_string(*ptr) << std::endl;
        }
        std::cout << "\n\n";
    }

    void begins_with_from(string searchable){
        std::cout << "begins with: " << searchable << "\n";
        std::vector<Transaction*> vec = m_trie_from.containsSearch(searchable);
        for(auto ptr = vec.begin(); ptr != vec.end(); ptr++){
            std::cout << to_string(*ptr) << std::endl;
        }             
        std::cout << "\n\n";
    }

    void begins_with_to(string searchable){
        std::cout << "begins with: " << searchable << "\n";
        std::vector<Transaction*> vec = m_trie_to.containsSearch(searchable);
        for(auto ptr = vec.begin(); ptr != vec.end(); ptr++){
            std::cout << to_string(*ptr) << std::endl;
        }             
        std::cout << "\n\n";
    }

    void contains_from(string searchable){
        std::cout << "contains: " << searchable << "\n\n";
        for(auto ptr = m_vec_from.begin(); ptr != m_vec_from.end(); ptr++){
            if(boyermoore((*ptr).first, searchable)){
                cout << to_string((*ptr).second) << std::endl;
            }
        }
        std::cout << "\n\n";
    }

    void contains_to(string searchable){
        std::cout << "contains: " << searchable << "\n\n";
        for(auto ptr = m_vec_to.begin(); ptr != m_vec_to.end(); ptr++){
            if(boyermoore((*ptr).first, searchable)){
                cout << to_string((*ptr).second) << std::endl;
            }
        }
        std::cout << "\n\n";
    }

    void maxvalue_ammount()
    {
        std::cout << "Max value transaction for ammount: " << std::endl;
        std::cout << to_string(m_mxheap_ammount.top()) << std::endl;
        std::cout << "\n\n";
    }

    void minvalue_ammount()
    {
        std::cout << "Min value transaction for ammount: " << std::endl;
        std::cout << to_string(m_miheap_ammount.top()) << std::endl;
        std::cout << "\n\n";
    }

    void maxvalue_moment()
    {
        std::cout << "Max value transaction for moment: " << std::endl;
        std::cout << to_string(m_mxheap_moment.top()) << std::endl;
        std::cout << "\n\n";
    }

    void minvalue_moment()
    {
        std::cout << "Min value transaction for ammount: " << std::endl;
        std::cout << to_string(m_miheap_moment.top()) << std::endl;
        std::cout << "\n\n";
    }

    void search_range_ammount(int start, int stop)
    {
        //m_avl_amount.printBT();
        std::cout << "Range " << start << ":" << stop << std::endl;
        for (auto ptr:m_avl_amount.find_range(start,stop))
        {
            cout << to_string(ptr.second) << std::endl;
        }
        std::cout << "\n" << std::endl;
    }

    void search_range_moment(int start, int stop)
    {
        m_avl_moment.printBT();
        std::cout << "Range " << start << ":" << stop << std::endl;
        for (auto ptr:m_avl_moment.find_range(start,stop))
        {
            cout << to_string(ptr.second) << std::endl;
        }
        std::cout << "\n" << std::endl;
    }

    ~Blockchain()
    {
        for (auto i:blocks)
            delete i;
    }
private:
    bool blockIsValid()
    {
        uint512_t hash_ = blocks[current_block_id]->hash_self();
        to_string(hash_);
        std::string block_to_insert_hash = to_string(hash_);
        // skip 0x
        for (int i = 2; i<difficulty; i++)
        {
            if (block_to_insert_hash[i] != '0') return false;
        }
        return true;
    }

    uint512_t performPOW()
    {
        while (!blockIsValid())
        {
            blocks[current_block_id]->nonce++; // i have no issue with this being trash values
        }
        //std::cout << "Hash validated with a Nonce of: " << blocks[current_block_id].nonce << std::endl; // if found, cout nonce
        return blocks[current_block_id]->hash_self();
    }
};