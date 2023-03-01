#pragma once
#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>

#include "helpers.cpp"

using namespace std;

#define ALPHABET_SIZE 26

template <typename TV, typename TK>
class Patricia{
public:
    class NodeArray{
    public:
        pair<TV,TK> prefix;
        list<NodeArray*>* children;
        bool end;

        NodeArray(){
            prefix.first = "";
            children = new list<NodeArray*>[ALPHABET_SIZE];
            end = false;
        }
        NodeArray(TV word, TK trans){
            prefix.first = word;
            prefix.second = trans;
            children = new list<NodeArray*>[ALPHABET_SIZE];
            end = false;
        }
    };

private:
    NodeArray* root;
public:
    Patricia(){
        root = new NodeArray();
        root->end = false;
    }

    void insert(TV word, TK trans){
        insert(root, word, trans);
    }

    void insert(NodeArray* node, TV word, TK trans){
        //cout << "Inserting Substring: " << word << endl;
        NodeArray* temp = node;
        if(temp->children->empty())
        { 
            // If is empty just push.
            NodeArray* _node = new NodeArray(word, trans);
            _node->end = true;
            // find appropiate position to insert not done because empty
            temp->children->push_back(_node);
            return;
        } 
        else 
        {
            for(auto ptr = temp->children->begin(); ptr != temp->children->end(); ptr++){
                if(boyermoore(word, (*ptr)->prefix.first)){
                    //cout << "BOYER MOORE" << endl;
                    insert((*ptr), word.substr(int((*ptr)->prefix.first.size()), word.size()), trans);
                    return;
                }
                // Previous boyer-moore was to see if there was a prefix for the word to insert.
                // Now we check if the word to insert is prefix for some already inserted word.
                if(boyermoore((*ptr)->prefix.first, word)){
                    // cout << "need to split: " << (*ptr)->prefix << " cuz of " << word << endl;
                    string new_pre = (*ptr)->prefix.first.substr(int(word.size()), int((*ptr)->prefix.first.size())); 
                    // new_pre = new splitted prefix
                    NodeArray* new_node = new NodeArray(word, trans); // Instantiate new Node
                    (*ptr)->prefix.first = new_pre;                  // Change preffix for the new splitted pre.
                    new_node->children->push_back(*ptr);      // Push old node into the new Node
                    temp->children->push_back(new_node);      // Push the new Node
                    temp->children->remove(*ptr);              // Remove old node

                    // i cant be bothered to insert these things ordered, so.... well
                    new_node->children->sort(
                    [](NodeArray* x,NodeArray* y)
                    {
                        return (x->prefix.first < y->prefix.first);
                    }
                    );
                    temp->children->sort(
                    [](NodeArray* x,NodeArray* y)
                    {
                        return (x->prefix.first < y->prefix.first);
                    }
                    );
                    return;
                } 
            }

            NodeArray* _node = new NodeArray(word, trans);
            _node->end = true;
            // find appropiate position
            // insert ordered
            temp->children->push_back(_node);

            temp->children->sort(
            [](NodeArray* x,NodeArray* y)
            {
                return (x->prefix.first < y->prefix.first);
            }
            );

            temp->end = true;
            //cout << "inserting at root: " << word << endl;
            return;
        }
    }

    string toString(string sep = "") {
        string buff = "";
        words(root, "", "", buff, sep);
        return buff.substr(1,(int)buff.size());
    }

    void remove(string key)
    {
        // stack things up
        string word = key;
        NodeArray* node = root;

        stack<NodeArray*> st;

        while (word != "" && node != nullptr)
        {
            for (auto i: *(node->children))
            {
                if (isPrefix(i->prefix.first,word))
                {
                    st.push(i);
                    node = i;

                    // reduce the word
                    word = word.substr(i->prefix.first.size());

                    break;
                }
            }
        }
        // now i have a traceback
        // allways remove the end qualifier
        st.top()->end = false;
        // now, delete all elements from stack until a branch is found, an end == true element is found or is root.
        // cases where other words may require the thingy
            // just 1 remaining       only 0 or 1 children means no subtries an end means another word prefixes the one being deleted
        while((st.top() != root) && (st.top()->children->size() < 2) && !st.top()->end)
        {
            NodeArray* temp = st.top(); // keep this to eventually delete it
            delete st.top();
            st.pop();
            st.top()->children->remove(temp);
        }
    }


    bool search(string word) {
        bool found = searchRec(root, word);
        //cout << "Searching: " << word << ": ";
        //if(found) cout << "true\n";
        //else cout << "false\n";        
        return found;
    }
    
    void display()
    {
        displayRec(root, "root");
        cout << endl;
    }

private:

    bool isPrefix(string prf,string wrd)
    {
        if (prf.size() > wrd.size()) return false; // prefixes cant be bigger than the word itself

        // check that all letters are equal
        for (int i = 0; i<prf.size(); i++)
        {
            if (prf[i] != wrd[i]) return false;
        }

        return true;
    }

    bool numChilds(NodeArray* node){
        int c = 0;
        NodeArray* temp = node;
        for(auto ptr = temp->children->begin(); ptr != temp->children->end(); ptr++){
            c++;
        }
        return c;
    }


    int bucket_size(NodeArray* node){
        int elements = 0;
        for(auto ptr = node->children->begin(); ptr != node->children->end(); ptr++){
            elements++;
        }
        return elements;
    }

    // Print hash buckets
    void displayFull(NodeArray* node){
        int b_size = bucket_size(node);
        for(auto ptr = node->children->begin(); ptr != node->children->end(); ptr++){
            if(b_size <= 1){ 
                cout << "[ " << (*ptr)->prefix.first << "-" << (*ptr)->prefix.second << " ]";
            } else {
                cout << "[ " << (*ptr)->prefix.first << "-" << (*ptr)->prefix.second << " ] - ";
            }
            b_size--;
        }
    }

    // Go recursively through the trie.
    void displayRec(NodeArray* node, string prefix){
        if(node->children->empty()) return;
        cout << endl << "child of " << prefix << " : ";
        displayFull(node);
        for(auto ptr = node->children->begin(); ptr != node->children->end(); ptr++){
            displayRec((*ptr), (*ptr)->prefix.first);
        }
    }

    void words(NodeArray* node, string val, string stack,string& buffer,string sep = " ", bool final = false){
        stack += val;
        if (node->end)
            buffer += stack + sep;
        for(auto ptr = node->children->begin(); ptr != node->children->end(); ptr++){
            bool _end = false; if((*ptr)->end) _end = true;
            words((*ptr), (*ptr)->prefix.first, stack,buffer, sep, _end);
        }
    }

    bool searchRec(NodeArray* node, string wrd){
        if(wrd == "") return true;
        //cout << " > " << wrd << endl;
        for(auto ptr = node->children->begin(); ptr != node->children->end(); ptr++){
            if(boyermoore(wrd, (*ptr)->prefix.first)){
                //cout << "boyer: " << wrd << " " << (*ptr)->prefix << endl;
                return searchRec((*ptr), wrd.substr(int((*ptr)->prefix.first.size()), wrd.size()));
                break;
            }
        }
        return false;
    }

    ~Patricia(){    }
};
