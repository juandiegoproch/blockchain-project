#include <iostream>
#define terminal_log(stuff) std::cout << stuff << std::endl;

#include "./structures/blockchain.h"
#include <string>

int main(void) {
    Blockchain b;

    b.push(Transaction("bolon","ana",0));
    b.push(Transaction("bodrio","bobuina",1));
    b.push(Transaction("carnivoro","cecilia",2));
    b.push(Transaction("delfino","diametro",3));
    b.push(Transaction("ernesto","estupido",4));
    b.push(Transaction("fanta","floro",5));
    b.push(Transaction("gordo","goloso",6));
    b.push(Transaction("helicopter","humano",7));
    b.push(Transaction("iman","iguana",8)); 
    b.push(Transaction("julian","juliaca",9));

    b.push(Transaction("xandor","koala",10));
    b.push(Transaction("zoologico","sigmoide",0));
    b.push(Transaction("xavier","wuwuwuwuwu",1));
    b.push(Transaction("chuta","chuta",2));
    b.push(Transaction("marcos","erga",3));
    b.push(Transaction("benedictoXVI","ethereum",4));
    b.push(Transaction("marle","drogas",5));
    b.push(Transaction("martin","nether",6));
    b.push(Transaction("ludwig","beethoven",7));
    b.push(Transaction("marvin","abisrror",8));

    b.push(Transaction("imantado","erga",9));
    b.push(Transaction("iman","abisrror",10));
    b.push(Transaction("gordo","chuta",0));
    b.push(Transaction("ernesto","sigmoide",1));
    b.push(Transaction("delfines","matraca",2));
    b.push(Transaction("delfino","nether",3));
    b.push(Transaction("xander","koala",4));
    b.push(Transaction("martin","nether",6));
    b.push(Transaction("zoologico","sigmoide",0));
    b.push(Transaction("xavier","wuwuwuwuwu",1));
    b.push(Transaction("ludwig","beethoven",7));

    b.push(Transaction("gordo","chuta",0));
    b.push(Transaction("gordosososo","floro",5));
    b.push(Transaction("gordillo","goloso",6));
    b.push(Transaction("carnivoro","cecilia",2));
    b.push(Transaction("delfino","diametro",3));
    b.push(Transaction("ernesto","estupido",4));
    b.push(Transaction("gordisimo","ana",0));
    b.push(Transaction("boludo","bobuina",1));
    b.push(Transaction("carne","cecilia",2));

    b.display_hash_index(); 

    b.search_from("delfino");
    b.search_to("koala");
}