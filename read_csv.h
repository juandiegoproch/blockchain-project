#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
#include "structures/transaction.h"

using namespace std;

bool read_csv(std::string filename, vector<Transaction>& transacts)
{
    string line, word;
    ifstream file(filename);

	if(!file.is_open())
    {
        return false;
    }

    while (getline(file, line))
    {
        stringstream currline(line);
        std::string to, from, moment_s, ammount_s;

        getline(currline,to,',');
        getline(currline,from,',');
        getline(currline,moment_s,',');
        getline(currline,ammount_s,',');

        long int moment = atoi(moment_s.c_str());
        long int ammount = atoi(ammount_s.c_str());

        Transaction t;
        t.from = from;
        t.to = to;
        t.moment = moment;
        t.ammount = ammount;

        transacts.push_back(t);
		
    }

    return true;
}
