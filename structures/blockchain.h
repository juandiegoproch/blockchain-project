#pragma once

#include "block.h"
#include "transaction.h"
#include <vector>
#include "../indexes/hash.cpp"
#include "../indexes/trie.cpp"


class Blockchain
{
    // important things
    std::vector<Block> blocks;
    int difficulty;

    // helpfull things
    
    int n_transact;
    int current_block_id;

    // indexes
    HashTable<string, Transaction*> m_hash_from;
    HashTable<string, Transaction*> m_hash_to;
public:

    Blockchain()
    {
        uint512_t zero;
        zero = 0;
        difficulty = 4;
        current_block_id = 0;
        n_transact = 0;
        blocks.push_back(Block(current_block_id,zero));
    }

    void push(const Transaction& t) // inserts a new transaction into the last Block in the Blocks vector
    {
        if (n_transact >= BLOCK_TRANSACTION_AMMOUNT)
        {
            // push the block to the blocks vector
            uint512_t old_hash = performPOW();
            blocks[current_block_id].display();
            blocks.push_back(Block(current_block_id,old_hash));

            // new block ready and loaded
            n_transact = 0;
            current_block_id++;
        }

        blocks[current_block_id].data[n_transact] = t;
        n_transact++;
        // update indexes
        m_hash_from.set(blocks[current_block_id].data[n_transact-1].from, addressof(blocks[current_block_id].data[n_transact-1]));

        m_hash_to.set(blocks[current_block_id].data[n_transact-1].to, addressof(blocks[current_block_id].data[n_transact-1]));
    }

    void display_hash_index(){
        std::cout << "\nm_hash_from\n";
        m_hash_from.display();
        std::cout << "\nm_hash_to\n";
        m_hash_to.display();
    }

    void search_from(string searchable){
        std::cout << "search: " << searchable << std::endl;
        std::vector<Transaction*> vec = m_hash_from.search(searchable);
        for(auto ptr = vec.begin(); ptr != vec.end(); ptr++){
            std::cout << to_string(*ptr) << std::endl;
        }
    }

    void search_to(string searchable){
        std::cout << "search: " << searchable << std::endl;
        std::vector<Transaction*> vec = m_hash_to.search(searchable);
        for(auto ptr = vec.begin(); ptr != vec.end(); ptr++){
            std::cout << to_string(*ptr) << std::endl;
        }
    }

    

private:
    bool blockIsValid()
    {
        uint512_t hash_ = blocks[current_block_id].hash_self();
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
            blocks[current_block_id].nonce++; // i have no issue with this being trash values
        }
        //std::cout << "Hash validated with a Nonce of: " << blocks[current_block_id].nonce << std::endl; // if found, cout nonce
        return blocks[current_block_id].hash_self();
    }
};