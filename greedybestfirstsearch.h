#ifndef GREEDYBESTFIRSTSEARCH_H
#define GREEDYBESTFIRSTSEARCH_H

#include "config.h"
#include "searchproblem.h"

class GreedyBestFirstSearch : public SearchProblem
{
public:
    GreedyBestFirstSearch(Map _map, Index _origin, Index _destination);
public:
    bool findPath();
};

#endif // GREEDYBESTFIRSTSEARCH_H
