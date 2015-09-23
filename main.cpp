#include <iostream>
#include <fstream>
#include <map>

#include "DirectedAcyclicGraph.h"

int main(int argc, char *argv[])
{
    std::map<char, DAGNode*> variableMap;

    if (argc != 2)
    {
        std::cout << "Please supply an input file as an argument (e.g. './expression_parser sample_file.txt')" << std::endl;
    }
    else
    {
        std::string original_file_name = argv[1];
        std::ifstream ifs(original_file_name);
        if (!ifs.is_open()) {
            std::cout << "Could not open file..." << std::endl;
            return 1;
        }
        std::cout << "Got a file" << std::endl;
    }
}