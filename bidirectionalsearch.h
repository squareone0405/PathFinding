#ifndef BIDIRECTIONALSEARCH_H
#define BIDIRECTIONALSEARCH_H

#include "config.h"
#include "searchproblem.h"

class BidirectionalSearch : public SearchProblem
{
public:
    BidirectionalSearch(Map _map, Index _origin, Index _destination);
public:
    bool findPath();
};

#endif // BIDIRECTIONALSEARCH_H
