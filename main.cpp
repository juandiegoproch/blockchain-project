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
    b.push(Transaction("k","k",10));

    b.push(Transaction("z","sdf9",0));
    b.push(Transaction("x","wiu",1));
    b.push(Transaction("c","sdfiu",2));
    b.push(Transaction("v","ergo",3));
    b.push(Transaction("b","eth",4));
    b.push(Transaction("n","dsgsd",5));
    b.push(Transaction("m","eth",6));
    b.push(Transaction("l","tthe",7));
    b.push(Transaction("k","wge",8));
    b.push(Transaction("j","asgfas",9));
    b.push(Transaction("h","zzzxz",10));

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
    b.push(Transaction("k","k",10));

    b.push(Transaction("z","sdf9",0));
    b.push(Transaction("x","wiu",1));
    b.push(Transaction("c","sdfiu",2));
    b.push(Transaction("v","ergo",3));
    b.push(Transaction("b","eth",4));
    b.push(Transaction("n","dsgsd",5));
    b.push(Transaction("m","eth",6));
    b.push(Transaction("l","tthe",7));
    b.push(Transaction("k","wge",8));
    b.push(Transaction("j","asgfas",9));
    b.push(Transaction("h","zzzxz",10));

}