#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H

#include "config.h"
#include "searchproblem.h"

class AStarSearch : public SearchProblem
{
public:
    AStarSearch(Map _map, Index _origin, Index _destination);
public:
    bool findPath();
};

#endif // ASTARSEARCH_H
