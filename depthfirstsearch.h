#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "config.h"
#include "searchproblem.h"

class DepthFirstSearch : public SearchProblem
{
public:
    DepthFirstSearch(Map _map, Index _origin, Index _destination);
public:
    bool findPath();
};

#endif // DEPTHFIRSTSEARCH_H
