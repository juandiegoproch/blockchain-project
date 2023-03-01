//
// Created by dchul on 2/02/2023.
//


#include <iostream>
#include "heap.h"
#include <cstring>
using namespace std;

struct Trans{
    string name;
    string apellido;
    int amount;
};

int main()
{
    Trans* t = new Trans;
    Trans* t2 = new Trans;
    Heap<int,Trans*>* heap = new Heap<int, Trans*>();
    Trans* transpointer;

    //heapp->top();
    heap->push(8,t);
    heap->push(9,t2);
    heap->push(10,t);
    heap->push(11,t2);

    heap->pop();
    transpointer = heap->top(); //18f0
    std::cout<<transpointer<<std::endl;

    heap->pop();
    transpointer = heap->top(); //1960
    std::cout<<transpointer<<std::endl;


    /*
    heapp->push(55);
    cout<<heapp->top()<<endl;//55
    heapp->pop();
    heapp->pop();
    cout<<heapp->top()<<endl;//49
    */

}
