#ifndef SEARCHPROBLEM_H
#define SEARCHPROBLEM_H

#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include "config.h"
#include "cmath"

struct Node {
    Index currPos;
    Node* prevNode;
    Node(Index _curr, Node* _prev){
        currPos = _curr;
        prevNode = _prev;
    }
};

struct NodeEqual {
    bool operator()(const Node& lhs, const Node& rhs) const {
        return lhs.currPos == rhs.currPos;
    }
};

struct NodeHash {
    std::size_t operator()(const Node& n) const {
        size_t hashc = n.currPos.first * 1000 + n.currPos.second;
        return hashc;
    }
};

typedef std::unordered_set<Node, NodeHash, NodeEqual> NodeSet;
typedef std::unordered_map<Node, int, NodeHash, NodeEqual> NodeMap;

struct WeightedNode : public Node {
    float weight;
    WeightedNode(Index _curr, Node* _prev, float _weight) : Node(_curr, _prev){
        weight = _weight;
    }
};

struct Cmp {
    bool operator()(WeightedNode* A, WeightedNode* B){
        return A->weight > B->weight;
    }
};

struct Node4AStar : public Node {
    float h;
    int g;
    Node4AStar(Index _curr, Node* _prev, float _h, int _g) : Node(_curr, _prev){
        h = _h;
        g = _g;
    }
};

struct CmpAStar {
    bool operator()(Node4AStar* A, Node4AStar* B){
        return (A->g + A->h) > (B->g + B->h);
    }
};

class SearchProblem
{
public:
    SearchProblem() = default;
    SearchProblem(Map _map, Index _origin, Index _destination);
protected:
    Map map;
    std::vector<std::vector<bool>> visited;
    Index origin;
    Index destination;
    std::vector<Index> path;
    int width;
    int height;
    int expandNum;
    HuristicFunction hFunction;
    const Index moveDirection[8] = {std::make_pair<int, int>(-1, 0), std::make_pair<int, int>(0, -1),
                                    std::make_pair<int, int>(1, 0), std::make_pair<int, int>(0, 1),
                                    std::make_pair<int, int>(-1, -1), std::make_pair<int, int>(1, -1),
                                    std::make_pair<int, int>(-1, 1), std::make_pair<int, int>(1, 1)};
protected:
    float getHuristic(Index A, Index B){
        switch (hFunction) {
        case Manhatten:
            return abs(A.first - B.first) + abs(A.second - B.second);
            break;
        case Diagonal:
            return (abs(A.first - B.first)) > (abs(A.second - B.second)) ?
                        (abs(A.first - B.first)) : (abs(A.second - B.second));
            break;
        case Euclidean:
            return sqrt((A.first - B.first)*(A.first - B.first) + (A.second - B.second)*(A.second - B.second));
            break;
        default:
            break;
        }
        return 0.0;
    }
    bool isValid(Index pos);
public:
    virtual bool findPath() = 0;
    void setExpandNum(int num){
        this->expandNum = num;
    }
    void setHuristic(HuristicFunction hf){
        this->hFunction = hf;
    }
    std::vector<std::vector<bool>> getVisited();
    std::vector<Index> getPath();
};

#endif // SEARCHPROBLEM_H
