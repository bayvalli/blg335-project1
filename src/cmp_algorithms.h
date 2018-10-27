#ifndef CMP_ALGORITHMS
#define CMP_ALGORITHMS

#include <string>
#include <vector>
#include <utility>

struct Arguments
{
    std::string algorithm;  //algorithm type
    std::string feature;    //sorting criteria
    unsigned int size; // number of lines of the document
};

struct Data {
    std::vector< std::pair<std::string, std::vector <std::string>>> csv_data;
    std::string timestamp; // 1
    std::string last_price; // 3

    //sorting functions
};

class CSVReader {
    std::string filename;
    std::string deliminator;
    std::string headers;

public:
    CSVReader(std::string file = "../log_inf.csv", std::string delim = ",") : filename(file), deliminator(delim)
    {}
    Data * getData(Data * data, const Arguments * args);
};

#endif