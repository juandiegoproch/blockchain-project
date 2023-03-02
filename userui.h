#include <string>
#include <stdexcept>
#include <iostream>
#include "structures/blockchain.h"
#include "read_csv.h"

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

        minvalue <ammount/moment>
            Returns the minimum value transaction for the specified attribute.

        read_csv <filename>
            Uploads data from the csv file into the blockchain. *

        display
            Displays all the blocks in the blockchain.

        quit
            Quits the application

        help
            Shows this message.
        
        * Data must be formatted like: <to>,<from>,<moment>,<ammount> '\n
    )V0G0N";
    std::cout << "                       BLOCKCHAIN MANAGER COMMANDLINE               TYPE: USER-QUERY \n \n --------------------------------------------------------------------------------------- \n 2/28/2023 " << std::endl;
    std::cout << user_help_string << std::endl << ">> ";

    // get command type
    std::string nextword;
    /*
        Quienes faltan?
        min/max - Hacer que existan
    */
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
                    b.search_range_moment(start_i,end_i);
                }
                else if (who == "ammount")
                {
                    std::cout << "searching range over \'ammount\'. " << std::endl;
                    b.search_range_ammount(start_i,end_i);
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
            //std::cout << "This option has known issues: Fails to match inside word if string is not sigular char"; fixed !
            std::string who,argument;

            std::cin >> who;
            std::cin >> argument;

            if (who == "to")
            {
                std::cout << "searching over to contains " << argument << std::endl;
                b.contains_to(argument);
            }
            else if (who == "from")
            {
                std::cout << "searching over from contains " << argument << std::endl;
                b.contains_from(argument);
            }
            else
            {
                std::cout << "Invalid attribute" << std::endl;
            }

        }
        else if (nextword == "maxvalue")
        {
            std::string who;

            std::cin >> who;

            if (who == "ammount")
            {
                std::cout << "max value over \'ammount\'. " << std::endl;
                b.maxvalue_ammount();
            }
            else if (who == "moment")
            {
                std::cout << "max value over \'moment\'. " << std::endl;
                b.maxvalue_moment();
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
                b.minvalue_ammount();
            }
            else if (who == "moment")
            {
                std::cout << "min value over \'moment\'. " << std::endl;
                b.minvalue_moment();
            }
            else
            {
                std::cout << "Invalid attribute" << std::endl;
            }
        }
        else if (nextword == "read_csv")
        {
            std::string filename;
            std::cin >> filename;
            std::vector<Transaction> transactsread;
            if (read_csv(filename,transactsread))
            {
                std::cout << "reading file..." << std::endl;
                
                for (Transaction i:transactsread)
                    b.push(i);

                std::cout << "file succesfully read..." << std::endl;
            }
            else{
                std::cout << "Invalid file." << std::endl;
            }


        }
        else if (nextword == "help")
        {
            std::cout << user_help_string <<std::endl;
        }
        else if(nextword == "display")
        {
            b.display_blocks();
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