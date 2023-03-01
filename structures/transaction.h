#pragma once
#include <iostream>
#define terminal_log(stuff) std::cout << stuff << std::endl;

#include <string>
#include <cstdlib>

struct Transaction
{
public:
    std::string from;
    std::string to;
    unsigned long int moment; // Unix epoch time
    int ammount;

    Transaction(std::string from_, std::string to_, int amt)
    {
        // automatically get the time
        time_t currentime;
        time(&currentime);

        from = from_;
        to = to_;
        moment = (unsigned long int) currentime;
        ammount = amt;
    }

    Transaction()
    {
        // empty constructor so memory can be allocated
    }

};

std::string to_string(Transaction tr)
{
    std::string stringified = "";
    stringified += tr.from + "\t\t";
    stringified += tr.to + "\t\t";
    stringified += std::to_string(tr.moment) + "\t" + std::to_string(tr.ammount);
    return stringified;
}

std::string to_string(Transaction* tr)
{
    std::string stringified = "";
    stringified += tr->from + "\t\t";
    stringified += tr->to + "\t\t";
    stringified += std::to_string(tr->moment) + "\t" + std::to_string(tr->ammount);
    return stringified;
}