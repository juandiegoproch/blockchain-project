#include <iostream>
#define terminal_log(stuff) std::cout << stuff << std::endl;

#include "./structures/blockchain.h"
#include <string>
#include "userui.h"

void testSearch(Blockchain& b){
    // --=-=-=-=-= DONE
    cout << "\n\t\t----- TEST SEARCH -----\n\n";

    b.push(Transaction("bolon","ana",0));
    b.push(Transaction("bodrio","bobuina",1));
    b.push(Transaction("carnivoro","cecilia",2));
    b.push(Transaction("delfino","diametro",3));
    b.push(Transaction("ernesto","estupido",4));
    b.push(Transaction("fanta","floro",5));
    b.push(Transaction("gordo","goloso",6));
    b.push(Transaction("helicopter","humano",7));
    b.push(Transaction("iman","iguana",8)); 
    b.push(Transaction("delfin","juliaca",9));

    b.push(Transaction("imantado","jerga",9));
    b.push(Transaction("iman","abisrror",10));
    b.push(Transaction("gordo","chuta",0));
    b.push(Transaction("ernesto","sigmoide",1));
    b.push(Transaction("delfino","matraca",2));
    b.push(Transaction("delfino","nether",3));
    b.push(Transaction("xander","koala",4));
    b.push(Transaction("martin","nether",6));
    b.push(Transaction("zoologico","sigmoide",0));
    b.push(Transaction("xavier","wuwuwuwuwu",1));
    b.push(Transaction("ludwig","beethoven",7));
    //b.display_hash_index(); 

    b.search_from("delfino");
    b.search_to("koala");
}

void testBeginsWith(Blockchain& b){
    // =-=-=-=-=- DONE
    cout << "\n\t\t----- TEST BEGIN -----\n\n";
    b.push(Transaction("ban", "ouija", 5));
    b.push(Transaction("banana", "vaca", 5));
    b.push(Transaction("ana", "vacaciones", 5));
    b.push(Transaction("wob", "vacas", 5));
    b.push(Transaction("wobo", "trenzo", 5));

    b.push(Transaction("wobowubzy", "trenzotas", 5));
    b.push(Transaction("banco", "oui", 5));
    b.push(Transaction("turtwig", "grotle", 5));
    b.push(Transaction("turtiga", "grotezco", 5));
    b.push(Transaction("banconeta", "hola", 5));

    //b.display_trie_index();

    b.begins_with_from("ba");
}

void testContains(Blockchain& b){
    // -=-=-=-=-=-=-=- DONE
    cout << "\n\t\t----- TEST CONTAINS -----\n\n";
    b.push(Transaction("ban", "olivos", 5));
    b.push(Transaction("banana", "vaca", 5));
    b.push(Transaction("ana", "vacaciones", 5));
    b.push(Transaction("wob", "vacas", 5));
    b.push(Transaction("wobo", "trenzo", 5));

    b.push(Transaction("wobowubzy", "trenzotas", 5));
    b.push(Transaction("banco", "oui", 5));
    b.push(Transaction("turtwig", "grotle", 5));
    b.push(Transaction("turtiga", "grotezco", 5));
    b.push(Transaction("banconeta", "hola", 5));      

    b.contains_from("wob");

    b.contains_to("v");
}

void testAVL(Blockchain& b){
    cout << "\n\t\t----- TEST AVL -----\n\n";
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

    b.display_tree_index();

}


int main(void) {
    Blockchain b;
    testSearch(b);
    //testBeginsWith(b);
    //testAVL(b);
    //testContains(b);

    userUI(b);

    return 0;
}