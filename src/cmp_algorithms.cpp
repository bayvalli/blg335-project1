#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <getopt.h> //argument parser getopt() func

#include "cmp_algorithms.h"

using namespace std;

void displayHelp(void);
void displayUsage(void);

int main(int argc, char *argv[])
{
    opterr = 0; //For prevent printing error messages to stderr when user enters an unknown argument
    const option long_options[] = {
        {"algo", required_argument, nullptr, 'a'},
        {"feature", required_argument, nullptr, 'f'},
        {"size", required_argument, nullptr, 's'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}};

    Arguments arguments; // for storing entered arguments 

    int opt; // getopt_long_only returns option's ascii code 
    int aopt_cnt = 0; // counters for handling that the user entered necessary arguments
    int fopt_cnt = 0;
    int sopt_cnt = 0;
    string arg_opt; // for option's argument
    while ((opt = getopt_long_only(argc, argv, "a:f:s:h", long_options, 0)) != -1)
    {
        switch (opt)
        {
            case 0:
                break;
            case 'a':
                arg_opt = optarg;
                if (arg_opt == "m" || arg_opt == "i"){
                    arguments.algorithm = arg_opt;
                    aopt_cnt++;
                }
                else {
                    cout << "You have passed wrong argument for algorithm!" << endl;
                    displayHelp();
                }
                break;
            case 'f':
                arg_opt = optarg;
                if (arg_opt == "t" || arg_opt == "p"){
                    arguments.feature = arg_opt;
                    fopt_cnt++;
                }
                else{
                    cout << "You have passed wrong argument for feature!" << endl;                        
                    displayUsage();
                }
                break;
            case 's':
                arg_opt = optarg;
                if(stoi(arg_opt)){
                    arguments.size = stoi(arg_opt);
                    sopt_cnt++;
                }
                break;
            case ':': /* missing option argument */
            case 'h':
                displayHelp();
                break;
            case '?': /* invalid option */
                cout << "You have entered invalid option!" << endl;    
                displayUsage();
                break;
            default:
                /* You won't actually get here. */
                break;
        }
    }
    
    if(aopt_cnt < 1 || fopt_cnt < 1 || sopt_cnt < 1)
        displayUsage();

    CSVReader csv;
    Data data;

    try {
        csv.getData(&data, &arguments);
    } catch(const char *msg){
        cerr << msg << endl;
    }


    return 0;
}

void displayUsage() //Display usage
{
    cerr << "Usage: ./cmpSortingAlgo -algo algorithmType -feature criterion -size N" << endl;
    exit(EXIT_FAILURE);
}

void displayHelp() //Display usage and help for arguments
{
    cout << "Usage: ./cmpSortingAlgo -algo algorithmType -feature criterion -size N\n\n"
            "-algo:         Algorithm type, 'i' for Insertion Sort and 'm' for Merge Sort.\n"
            "-feature:      Sorting order type, 't' for Timestamp and 'p' for last price.\n"
            "-size:         First n lines of data from 'log_inf.csv'. \n"
            "-h or --help   Display help\n";
    exit(EXIT_FAILURE);
}

// Function reads from a CSV file to taken parameter Data struct
// and takes Arguments for reading N lines of the file
Data * CSVReader::getData(Data * d, const Arguments * args){ 

    ifstream file(filename);
    if(!file.is_open())
        throw "File cannot be opened! Make sure you have log_inf.csv file.";

    getline(file, headers); // First line - headers

    string line;
    for(int i = 0; i < args->size && getline(file, line); i++)
    {
        string input, s;
        
        input = line;

        istringstream ss(input);
        std::getline(ss, d->timestamp, ','); //First column is timestamp
        std::getline(ss, s, ','); //Second column does not matter, will never use..
        std::getline(ss, d->last_price, ','); //First column is timestamp

        vector<string> f_vector;
        f_vector.push_back(d->timestamp);
        f_vector.push_back(d->last_price); 
        
        d->csv_data.push_back(make_pair(line, f_vector)); //Pair that sorting algorithms will use 

        ss.clear();

        ////////////////////////////////////////////////////////////////////////////////////
        cout << line << endl;
        cout << "-----------------------------" << endl;
        cout << "Timestamp:" << f_vector[0] << "\tLast Price:" << f_vector[1] << endl;
        cout << "-----------------------------" << endl;
        ////////////////////////////////////////////////////////////////////////////////////
    }

    return d;
}
