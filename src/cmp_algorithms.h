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

struct T {
    time_t ts;
    unsigned fraction;
};

struct Data {
    std::vector< std::pair<std::string, std::pair<T, double>>> csv_data;
    std::string date; // 1
    std::string last_price; // 3
    unsigned int data_size;

    //sorting functions
    Data * insertionSort(const Arguments *);
};

class CSVReader {
    std::string filename;
    std::string deliminator;
    std::string headers;
    std::string output;

public:
    CSVReader(std::string file = "../log_inf.csv", std::string out = "sorted.csv", std::string delim = ",") : filename(file), deliminator(delim), output(out)
    {}
    Data * getData(Data *, const Arguments *);
    void createOutput(Data *);
};

#endif