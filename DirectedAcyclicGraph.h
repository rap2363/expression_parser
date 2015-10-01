#ifndef DIRECTEDACYCLICGRAPH_H
#define DIRECTEDACYCLICGRAPH_H

#include <vector>
#include <string>

class DAGNode
{
public:
    DAGNode(std::string name);
    DAGNode(std::string name, double value);
    void addDependency(DAGNode* node);
    void evaluate();
    double getValue() const { return mValue; }
    bool isEvaluated() const { return mEvaluated; }

private:
    double mValue; // Initial value of the node which will be added to by other dependencies
    std::string mName; // Unique name for this node in the DAG
    std::vector<DAGNode*> mDependencies;
    bool mEvaluated;
};

#endif DIRECTEDACYCLICGRAPH_H