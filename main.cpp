#include <iostream>
#define terminal_log(stuff) std::cout << stuff << std::endl;

#include "blockchain.h"
#include <string>

int main(void)
{
    Blockchain b;

    b.push(Transaction("a","a",0));
    b.push(Transaction("b","b",1));
    b.push(Transaction("c","c",2));
    b.push(Transaction("d","d",3));
    b.push(Transaction("e","e",4));
    b.push(Transaction("f","f",5));
    b.push(Transaction("g","g",6));
    b.push(Transaction("h","h",7));
    b.push(Transaction("i","i",8));
    b.push(Transaction("j","j",9));
    b.push(Transaction("i","i",10));



}