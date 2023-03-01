#include <string>
#include <cstdlib>

#define ascii_size 256

bool boyermoore(std::string text, std::string pattern){
    if(text == pattern) return true;
    int table[ascii_size];
    int size = text.size();

    if(int(pattern.size()) == 1){
        for(int i = 0; i < int(text.size()); i++){
            if(text[i] == pattern[0]){
                return true;
            }
        }
    }

    for(int i = 0; i < ascii_size; i++) table[i] = -1;
    for(int i = 0; i < size; i++) table[int(text[i])] = i;
    // ---------------
    int txt_size = text.size();
    int patt_size = pattern.size();
    int pos = 0;
    //cout << "txt-patt " << txt_size - patt_size << endl;
    while(pos < (txt_size - patt_size)){
        //cout << "pos: " << pos << endl;
        int x = patt_size - 1;
        //cout << "base x: " << x << endl;
        while(x >= 0 && (int(pattern[x]) == int(text[pos + x]))){
            x--;
        }
        //cout << pattern[x] << " & " << text[pos + x] << "|| ";
        //if(pattern[x] == text[pos + x]) cout << "true" << endl;
        //else cout << "false" << endl;

        if(x >= 0){
            unsigned char ch = text[pos + x];
            pos += std::max(1, x - table[ch]);
        } else {
            if(pos == 0) return true;
            //cout << "pushing in: " << pos << " jumping to: " << pos + patt_size << " x: " << x << endl;
            pos += (pos + patt_size < txt_size-1)? patt_size : 1; 
        }
    }
    //cout << "stopped at: " << pos << endl;
    return false;
}