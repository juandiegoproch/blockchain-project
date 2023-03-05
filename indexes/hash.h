#pragma once

#include <iostream>
#include <string>
#include <forward_list>
#include <vector>
using namespace std;

template <typename TK, typename TV>
class HashTable{
private:
    struct Entry{
        TK key;
        TV value;
        size_t hashval;

        bool operator==(HashTable table){
            return this->key == table.key && this->value == table.value ? true : false;
        }
    };
public:
    class Iterator{
        
    public:
        Iterator(){}
    };

private:
    forward_list<Entry>* lists;
    int maxSize;
    int currentSize;
    double maxFillFactor;
    int resize_increase;
    int max_col;
public:
    HashTable(){
        maxSize = 5; // how long is the table
        lists = new forward_list<Entry>[maxSize];
        maxFillFactor = 0.8;
        resize_increase = 2; 
        max_col = 3;
        currentSize = 0; // current ammount of elements in the table
    }

    // O(k) complexity, im doing push front so O(1) rlly.
    void set(const TK key, const TV value){
        Entry en;
        en.key = key;
        en.value = value;
        en.hashval = hashFun(key);

        int pos = en.hashval % maxSize;
        while(bucket_size(pos) >= max_col){
            pos++;
        }
        forward_list<Entry> & whichList = lists[pos];
        //cout << "Inserting " << value << " in position << " << pos << " hashval: " << en.hashval << endl;

        whichList.push_front(en);
        currentSize++;

        if(double(currentSize)/double(maxSize) >= maxFillFactor)
            resize();
    }

    void insert(const TK key, const TV value)
    {
        set(key,value);
    }

    // O(k) complexity? yes.
    void remove(TK key){
        int index = hashFun(key) % maxSize;
        forward_list<Entry> &whichList = lists[index];
        auto prev = whichList.before_begin();
        for(auto ptr = whichList.begin(); ptr != whichList.end(); ptr++){
            if((*ptr).key == key){
                whichList.erase_after(prev);
                break;
            }
            prev = ptr;
        }
    }

    vector<TV> search(TK key){
        vector<TV> vec = {};
        int index = hashFun(key) % maxSize;
        forward_list<Entry> whichList = lists[index];
        if(whichList.empty()) return vec;
        for(auto ptr = whichList.begin(); ptr != whichList.end(); ptr++){
            if((*ptr).key == key) {
                vec.push_back((*ptr).value);
            }
        }
        return vec;
    }

    // O(k) complexity? yes.
    TV get(TK key){
        int index = hashFun(key) % maxSize;
        forward_list<Entry> whichList = lists[index];
        cout << "searching in list: " << index << " = ";
        for(auto ptr = whichList.begin(); ptr != whichList.end(); ptr++){
            if((*ptr).key == key){
                return (*ptr).value;
            }
        }
        throw ("Element not found");
    }

    void display(){
        for(int i = 0; i < maxSize; i++){
            if(!lists[i].empty()){
                cout << "[" << i << "]" << " -> ";
                forward_list<Entry> whichList = lists[i];
                int b_size = bucket_size(i);
                for(auto ptr = whichList.begin(); ptr != whichList.end(); ptr++){
                    if(b_size <= 1)
                        cout << "[ " << (*ptr).key << " : " << (*ptr).value << " ]";
                    else
                        cout << "[ " << (*ptr).key << " : " << (*ptr).value << " ]=-=";
                    b_size--;
                }
                cout << "\n";
            }

        }   
    }

    // O(n)
    int bucket_size(int index){
        forward_list<Entry> whichList = lists[index];
        int elements = 0;
        for(auto ptr = whichList.begin(); ptr != whichList.end(); ptr++){
            elements++;
        }
        return elements;
    }

private:

    size_t hashFun(const string &key){
        std::hash<TK> ptr_hash;
        return ptr_hash(key);
    }

    int next(int pos){
        if(pos == maxSize-1)
            return 0;
        return ++pos;
    }

    int prev(int pos){
        if(pos == 0)
            return maxSize-1;
        return --pos;
    }

    void insertEntry(const Entry& toinsert)
    {
        int pos = toinsert.hashval % maxSize;
        lists[pos].push_front(toinsert);
        currentSize++;
    }

    // O(N) + O(k) ? yes
    void resize()
    {
        // save everything
        forward_list<Entry>* oldtable = lists;
        int oldmaxSize;
        int oldcurrentSize;

        // reset stuff to have a clean state
        maxSize = oldmaxSize * resize_increase;
        currentSize = 0;

        // increase the size of the table
        lists = new forward_list<Entry>[maxSize];

        // copy everything back up
        for (int i = 0; i<oldmaxSize;i++)
        {
            while (!lists[i].empty())
            {
                insertEntry(lists[i].front());
                lists[i].pop_front();
            }
        }
    }
};

/*
int main(){
    HashTable<string, Trans*> hash;

    Trans* t = new Trans;
    t->name = "marisola";
    t->kk = "gaa";
    t->amount = 1000;

    Trans* t2 = new Trans;
    t2->name = "enrique";
    t2->kk = "marisola";
    t2->amount = 100;
    
    hash.set(t->name, t);
    hash.set(t2->name, t2);
    hash.display();

    return 0;
}*/