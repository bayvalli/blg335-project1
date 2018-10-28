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
        cout << "CSV File has been read." << endl;
        data.insertionSort(&arguments);
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
    for(int i = 0; i < args->size && getline(file, line); i++, d->data_size++)
    {
        string input, s;
        
        input = line;

        istringstream ss(input);
        std::getline(ss, d->timestamp, ','); //First column is timestamp
        std::getline(ss, s, ','); //Second column does not matter, will never use..
        std::getline(ss, d->last_price, ','); //First column is timestamp

        pair<string, double> f_pair;
        f_pair.first = d->timestamp;
        f_pair.second = stof(d->last_price); 
        
        d->csv_data.push_back(make_pair(line, f_pair)); //Pair that sorting algorithms will use 

        ss.clear();

        ////////////////////////////////////////////////////////////////////////////////////
        cout << d->csv_data[i].first << endl;
        cout << "-----------------------------" << endl;
        cout << "Timestamp:" << d->csv_data[i].second.first << "\tLast Price:" << d->csv_data[i].second.second << endl;
        cout << "-----------------------------" << endl;
        ////////////////////////////////////////////////////////////////////////////////////
    }

    return d;
}

Data * Data::insertionSort(const Arguments * args){
    if(args->feature == "p"){ //insertion sort with respect to last price
        double key;
        for(int i = 1, j; i < data_size; i++){
            key = csv_data[i].second.second;
            j = i-1;

            while(j >= 0 && csv_data[j].second.second > key){
                swap(csv_data[j+1], csv_data[j]);
                j = j-1;
            }
            key = csv_data[j+1].second.second;
        }
    }
    else {

    }

    cout << endl << endl << "/////////////////////////////////////////////////////////////////////////" << endl;
    for(int i=0; i<data_size;i++){
        ////////////////////////////////////////////////////////////////////////////////////
        cout << csv_data[i].first << endl;
        cout << "-----------------------------" << endl;
        cout << "Timestamp:" << csv_data[i].second.first << "\tLast Price:" << csv_data[i].second.second << endl;
        cout << "-----------------------------" << endl;
        ////////////////////////////////////////////////////////////////////////////////////
    }
    return this;
}
