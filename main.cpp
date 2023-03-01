#include <iostream>
#define terminal_log(stuff) std::cout << stuff << std::endl;

#include "./structures/blockchain.h"
#include <string>

int main(void) {
    Blockchain b;

    b.push(Transaction("alberto","ana",0));
    b.push(Transaction("bodrio","bobuina",1));
    b.push(Transaction("carnivoro","cecilia",2));
    b.push(Transaction("delfino","diametro",3));
    b.push(Transaction("ernesto","estupido",4));
    b.push(Transaction("fanta","floro",5));
    b.push(Transaction("gordo","goloso",6));
    b.push(Transaction("helicopter","humano",7));
    b.push(Transaction("iman","iguana",8));
    b.push(Transaction("julian","juliaca",9));

    b.push(Transaction("kilo","koala",10));
    b.push(Transaction("zoologico","sigmoide",0));
    b.push(Transaction("xavier","wuwuwuwuwu",1));
    b.push(Transaction("chuta","chuta",2));
    b.push(Transaction("v","erga",3));
    b.push(Transaction("benedictoXVI","ethereum",40000));
    b.push(Transaction("no","drogas",5));
    b.push(Transaction("martin","nether",6));
    b.push(Transaction("ludwig","beethoven",7));
    b.push(Transaction("marvin","abisrror",8));

    b.push(Transaction("utec","erga",9));
    b.push(Transaction("iman","abisrror",10));
    b.push(Transaction("gordo","chuta",0));
    b.push(Transaction("ernesto","sigmoide",1000));
    b.push(Transaction("juliaca","matraca",2));
    b.push(Transaction("delfino","nether",3));
    b.push(Transaction("ana","koala",4000));
    b.push(Transaction("martin","nether",6));
    b.push(Transaction("zoologico","sigmoide",0));
    b.push(Transaction("xavier","wuwuwuwuwu",1));
    b.push(Transaction("ludwig","beethoven",7));

    b.push(Transaction("gordo","chuta",0));
    b.push(Transaction("fanta","floro",5));
    b.push(Transaction("gordo","goloso",6));
    b.push(Transaction("carnivoro","cecilia",2));
    b.push(Transaction("delfino","diametro",3));
    b.push(Transaction("ernesto","estupido",4));
    b.push(Transaction("alberto","ana",0));
    b.push(Transaction("bodrio","bobuina",1));
    b.push(Transaction("carnivoro","cecilia",2));

    b.display_hash_index(); 

    b.search_from("bodrio");
    b.search_to("chuta");
}