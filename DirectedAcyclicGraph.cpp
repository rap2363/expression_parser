#include "DirectedAcyclicGraph.h"

DAGNode::DAGNode(std::string name)
    : mName(name), mValue(0), mEvaluated(false)
{
}

DAGNode::DAGNode(std::string name, double value)
    : mName(name), mValue(value), mEvaluated(false)
{
}

void DAGNode::addDependency(DAGNode* node)
{
    mDependencies.push_back(node);
}

void DAGNode::evaluate()
{
    if (isEvaluated())
    {
        return;
    }

    for (auto iter = mDependencies.begin(); iter != mDependencies.end(); ++iter)
    {
        if (!(*iter)->isEvaluated()) // If dependency needs to be evaluated, do so before adding its value
        {
            (*iter)->evaluate();
        }
        mValue += (*iter)->getValue();
    }
    mEvaluated = true;
}