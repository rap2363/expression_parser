#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "DirectedAcyclicGraph.h"

std::string getVariable(const std::string& line)
{
    std::string variableName = line.substr(0, line.find("="));

    // Remove spaces in variable name (if there are any)
    variableName.erase(remove_if(variableName.begin(), variableName.end(), isspace), variableName.end());
    return variableName;
}

std::string populateFromExpression(const std::string& line, std::vector<std::string>& dependencies, double& value)
{
    std::string expression = line.substr(line.find("=")+1, line.length());
    // Remove spaces (if any)
    expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());
    std::string variableOrNumber;
    while (expression.find("+", 0) != std::string::npos || expression.length() > 0)
    {
        size_t operatorPosition = expression.find("+", 0);
        variableOrNumber = expression.substr(0, operatorPosition);
        if (operatorPosition == std::string::npos)
        {
            expression = "";
        }
        else
        {
            expression.erase(0, operatorPosition + 1);
        }
        try
        {
            value += std::stod(variableOrNumber);
        }
        catch (const std::invalid_argument& ia)
        {
            dependencies.push_back(variableOrNumber);
        }
    }
}

int main(int argc, char *argv[])
{
    std::unordered_map<std::string, DAGNode*> variableMap; // Map of DAGNodes
    std::unordered_map<std::string, std::vector<std::string> > dependencyMap; // Map from node to vector of dependencies
    if (argc != 2)
    {
        std::cout << "Please supply an input file as an argument (e.g. './expression_parser sample_file.txt')" << std::endl;
    }
    else
    {
        std::string input_file = argv[1];
        std::ifstream ifs(input_file);
        if (!ifs.is_open()) {
            std::cout << "Could not open file..." << std::endl;
            return 1;
        }
        std::vector<std::string> tokens;
        std::string line;
        std::string name;
        double value;
        while (std::getline(ifs,line))
        {
            name = getVariable(line);
            value = 0;
            std::vector<std::string> dependencies;
            populateFromExpression(line, dependencies, value);
            DAGNode node(name, value);
            variableMap.insert(std::pair<std::string, DAGNode*>(name, new DAGNode(name, value)));
            dependencyMap.insert(std::pair<std::string, std::vector<std::string> >(name, dependencies));
        }

        for (auto kv : dependencyMap)
        {
            for (auto iter : kv.second)
            {
                variableMap.at(kv.first)->addDependency(variableMap.at(iter));
            }
        }

        for (auto kv : variableMap)
        {
            std::cout << kv.first << ": ";
            kv.second->evaluate();
            std::cout << kv.second->getValue() << std::endl;
        }
    }
}