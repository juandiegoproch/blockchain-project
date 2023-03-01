#include <string>
#include <stdexcept>
#include <iostream>
#include "structures/blockchain.h"

std::string getWordFromCin()
{
    std::string word = "";
    std::cin >> word;
    return word;
}


void userUI(Blockchain& b)
{
    // User Prompt
    std::string user_help_string =
    R"V0G0N(
    Blockchain Application Commands:

        ----------------------------------------------------------
        
        Available commands:


        new_transaction <from> <to> <ammount:str>
            Add a new transaction to the blockchain.

        search <to/from> <what:str>
            Search for equality in fields to/from.

        range_search <to/from> <start:int> <end:int>
            Searches for all transactions within the range <start, end> on specified attribute.
        
        starts_with <from, to> <prefix:str>
            Searches for all transactions starting with prefix.

        contained <from, to> <argument:str>
            Searches for all transactions containing argument.

        maxvalue <ammount/moment>
            Returns the maximum value transaction for the specified attribute.

        maxvalue <ammount/moment>
            Returns the minimum value transaction for the specified attribute.

        quit
            Quits the application

        help
            Shows this message.

    )V0G0N";
    std::cout << "                       BLOCKCHAIN MANAGER COMMANDLINE               TYPE: USER-QUERY \n \n --------------------------------------------------------------------------------------- \n 2/28/2023 " << std::endl;
    std::cout << user_help_string << std::endl << ">> ";

    // get command type
    std::string nextword;

    while ((nextword = getWordFromCin()) != "quit")
    {
        if (nextword == "new_transaction")
        {
            std::string sender, recipient, ammt_s;
            int ammt_i;

            std::cin >> sender;
            std::cin >> recipient;

            std::cin >> ammt_s;

            try
            {
                for (int i = 0; i<ammt_s.length();i++)
                {
                    if ( ammt_s[i] - '0' >= 10) throw std::invalid_argument(" Invalid characters in string");
                }

                ammt_i = atoi(ammt_s.c_str());

                std::cout << "Starting transaction..." << std::endl;

                b.push(Transaction(sender,recipient,ammt_i));
                std::cout << "Transaction finished" << std::endl;
            }
            catch (std::invalid_argument a)
            {   
                std::cout << "The transaction could not be processed: ";
                std::cout << "\'" << ammt_s << "\' is not a valid ammout." << std::endl;
            }
        }
        else if (nextword == "search")
        {
            std::string who, argument;

            std::cin >> who;
            std::cin >> argument;

            if (who == "to")
            {
                std::cout << "searching over \'to\' for " << argument << ". "<< std::endl;
                b.search_to(argument);
            }
            else if (who == "from")
            {
                std::cout << "searching over \'from\' for " << argument << ". " << std::endl;
                b.search_from(argument);
            }
            else
            {
                std::cout << "Invalid search attribute \"" << who << "\". Valid ones are \'to\' and \'from\'.";
            }
        }
        else if (nextword == "range_search")
        {
            std::string who,start_s, end_s;
            int start_i, end_i;
            std::cin >> who;

            std::cin >> start_s;
            std::cin >> end_s;

            bool bad = false;

            // validate start
            try
            {
                for (int i = 0; i<start_s.length();i++)
                {
                    if ( start_s[i] - '0' >= 10) throw std::invalid_argument(" Invalid characters in string");
                }

                start_i = atoi(start_s.c_str());
            }
            catch(std::invalid_argument a)
            {
                bad = true;
                std::cout << "Invalid start" << std::endl;
            }

            // validate end
            if (!bad)
            {
                try
                {
                    for (int i = 0; i<end_s.length();i++)
                    {
                        if ( end_s[i] - '0' >= 10) throw std::invalid_argument(" Invalid characters in string");
                    }

                    end_i = atoi(end_s.c_str());
                }
                catch(std::invalid_argument a)
                {
                    bad = true;
                    std::cout << "Invalid end" << std::endl;
                }
            }


            if ( end_i < start_i && !bad)
            {
                bad = true;
                std::cout << "Invalid Range" << std::endl;
            }
            
            if (!bad)
            {
                if (who == "moment")
                {
                    std::cout << "searching range over \'moment\'. " << std::endl;
                    std::cout << " (Overwrite this!) Please implement at" << __FILE__ << " line:" << __LINE__ << std::endl;
                }
                else if (who == "ammount")
                {
                    std::cout << "searching range over \'ammount\'. " << std::endl;
                    std::cout << " (Overwrite this!) Please implement at" << __FILE__ << " line:" << __LINE__ << std::endl;
                }
                else
                {
                    std::cout << "Invalid attribute \"" << who <<"\"" << std::endl;
                }
            }
        }
        else if (nextword == "starts_with")
        {
            std::string who, prefix;

            std::cin >> who;
            std::cin >> prefix;

            if (who == "from")
            {
                std::cout << "searching strats with over \'from\'. " << std::endl;
                b.begins_with_from(prefix);
            }
            else if (who == "to")
            {
                std::cout << "searching strats with over \'to\'. " << std::endl;
                b.begins_with_to(prefix);
            }
            else
            {
                std::cout << "Invalid attribute" << std::endl;
            }
        }
        else if (nextword == "contained")
        {
            std::string argument;

            std::cin >> argument;

            std::cout << "searching contains " << argument << std::endl;
            std::cout << " (Overwrite this!) Please implement at" << __FILE__ << " line:" << __LINE__ << std::endl;

        }
        else if (nextword == "maxvalue")
        {
            std::string who;

            std::cin >> who;

            if (who == "ammount")
            {
                std::cout << "max value over \'ammount\'. " << std::endl;
                std::cout << " (Overwrite this!) Please implement at" << __FILE__ << " line:" << __LINE__ << std::endl;
            }
            else if (who == "moment")
            {
                std::cout << "max value over \'moment\'. " << std::endl;
                std::cout << " (Overwrite this!) Please implement at" << __FILE__ << " line:" << __LINE__ << std::endl;
            }
            else
            {
                std::cout << "Invalid attribute" << std::endl;
            }
        }
        else if (nextword == "minvalue")
        {
            std::string who;

            std::cin >> who;

            if (who == "ammount")
            {
                std::cout << "min value over \'ammount\'. " << std::endl;
                std::cout << " (Overwrite this!) Please implement at" << __FILE__ << " line:" << __LINE__ << std::endl;
            }
            else if (who == "moment")
            {
                std::cout << "min value over \'moment\'. " << std::endl;
                std::cout << " (Overwrite this!) Please implement at" << __FILE__ << " line:" << __LINE__ << std::endl;
            }
            else
            {
                std::cout << "Invalid attribute" << std::endl;
            }
        }
        else if (nextword == "help")
        {
            std::cout << user_help_string <<std::endl;
        }
        else
        {
            std::cout << "Invalid Command: No command named \'" << nextword << "\'" << std::endl;
        }

        // flush cin regardles of anything
        std::cin.clear();
        cin.ignore(10000,'\n');
        std::cout << ">> ";
    }


}