#pragma once

#include "Block.h"
#include "transaction.h"
#include <vector>


class Blockchain
{
    // important things
    std::vector<Block> blocks;
    int difficulty;

    // helpfull things
    
    int n_transact;
    int current_block_id;
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
            
            // new block ready and loaded
            n_transact = 0;
            current_block_id++;
            blocks.push_back(Block(current_block_id,old_hash));
        }

        blocks[current_block_id].data[n_transact] = t;
        n_transact++;

        // update indexes
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
            terminal_log("trying a new nonce");
            blocks[current_block_id].nonce++; // i have no issue with this being trash values
        }
        terminal_log("Found Valid Nonce");
        return blocks[current_block_id].hash_self();
    }
};