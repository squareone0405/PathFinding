#ifndef UNIFORMCOSTSEARCH_H
#define UNIFORMCOSTSEARCH_H

#include "config.h"
#include "searchproblem.h"

class UniformCostSearch : public SearchProblem
{
public:
    UniformCostSearch(Map _map, Index _origin, Index _destination);
public:
    bool findPath();
};

#endif // UNIFORMCOSTSEARCH_H
