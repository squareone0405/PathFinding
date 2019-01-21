#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "config.h"
#include "searchproblem.h"

class BreadthFirstSearch : public SearchProblem
{
public:
    BreadthFirstSearch(Map _map, Index _origin, Index _destination);
public:
    bool findPath();
};

#endif // BREADTHFIRSTSEARCH_H
