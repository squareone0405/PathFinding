#ifndef ITERATIVEDEEPENSEARCH_H
#define ITERATIVEDEEPENSEARCH_H

#include "config.h"
#include "searchproblem.h"

class IterativeDeepenSearch : public SearchProblem
{
public:
    IterativeDeepenSearch(Map _map, Index _origin, Index _destination);
private:
    NodeMap depthTableCurr;
    NodeMap depthTablePrev;
    Node* finalNode;
    std::stack<Node*> trashCollector;
public:
    bool findPath();
private:
    bool depthLimitedSearch(Node* node, int currDepth, int maxDepth);
};

#endif // ITERATIVEDEEPENSEARCH_H
