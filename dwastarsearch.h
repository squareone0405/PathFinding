#ifndef DWASTARSEARCH_H
#define DWASTARSEARCH_H

#include "config.h"
#include "searchproblem.h"

class DWAStarSearch : public SearchProblem
{
public:
    DWAStarSearch(Map _map, Index _origin, Index _destination);
public:
    bool findPath();
};

#endif // DWASTARSEARCH_H
