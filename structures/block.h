#pragma once

#include <iostream>
#define terminal_log(stuff) std::cout << stuff << std::endl;

#include "../hashlibrary/hashpp.h"
#include "transaction.h"
#include "../integer_extension/uint512.h"
#include <string>

#define BLOCK_TRANSACTION_AMMOUNT 10

struct Block
{
    int block_id;
    unsigned long long int nonce;
    uint512_t prev;
    Transaction data[BLOCK_TRANSACTION_AMMOUNT];
public:

    Block(int id, uint512_t prevhash)
    {
        nonce = 0;
        block_id = id;
        prev = prevhash;
    }

    uint512_t hash_self()
    // hashes itself and returns the hash
    {
        // first make it into a string
        std::string stringified;
        stringified += std::to_string(block_id) + std::to_string(nonce) + to_string(prev);

        for (int i = 0; i<BLOCK_TRANSACTION_AMMOUNT; i++)
        {
            stringified += to_string(data[i]);
        }

        uint512_t real_hash;
        hashpp::hash hsh_obj = hashpp::get::getHash(hashpp::ALGORITHMS::SHA2_512,stringified);
        real_hash = getui512fromstr(hsh_obj.getString());
        
        return real_hash;
    }

    void display(){
        std::cout << "------------------- BLOCK ~ " << nonce << " -------------------" << std::endl;
        for(int i = 0; i < BLOCK_TRANSACTION_AMMOUNT; i++){
            std::cout << "[" << i << "]\t";
            std::cout << to_string(data[i]) << "\n";
        }
    }
};
