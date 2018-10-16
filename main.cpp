#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class Arguments
{
    string algorithm;  //algorithm type
    string feature;    //sorting criteria
    unsigned int size; // number of lines of the document
};

void displayUsage()
{
    cerr << "You have entered wrong number of argument! \nUsage: ./cmpSortingAlgo -algo algorithmType -feature criterion -size N" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    opterr = 0; //For prevent printing error messages to stderr when user enters an unknown argument
    const option long_options[] = {
        {"algo", required_argument, 0, 0},
        {"feature", required_argument, 0, 0},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};
    
    Arguments arguments;
    
    int opt;
    while (opt = getopt_long_only(argc, argv, "h", long_options, nullptr) != -1){
        switch(opt){
            case "algo": 
        }
    }

        return 0;
}