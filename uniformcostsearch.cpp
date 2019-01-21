#include "uniformcostsearch.h"

UniformCostSearch::UniformCostSearch(Map _map, Index _origin, Index _destination)
    : SearchProblem(_map, _origin, _destination)
{
}

bool UniformCostSearch::findPath(){
    std::priority_queue<WeightedNode*, std::vector<WeightedNode*> ,Cmp> q;
    std::stack<WeightedNode*> trashCollector;
    std::vector<std::vector<bool>> closed = std::vector<std::vector<bool>>();
    closed.resize(map.size());
    for(int i = 0; i < map.size(); ++i)
        closed[i] = std::vector<bool>(map[i].size(), false);
    while(!q.empty())
        q.pop();
    q.push(new WeightedNode(origin, nullptr, 0));
    while(!q.empty()){
        WeightedNode* currNode = q.top();
        trashCollector.push(currNode);
        Index currPosition = currNode->currPos;
        q.pop();
        if (closed[currPosition.first][currPosition.second])
            continue;
        closed[currPosition.first][currPosition.second] = true;
        if(currPosition == destination){
            path.clear();
            while(currNode->prevNode != nullptr){
                path.push_back(currNode->currPos);
                currNode = (WeightedNode*)(currNode->prevNode);
            }
            while(!trashCollector.empty()){
                WeightedNode* temp = trashCollector.top();
                trashCollector.pop();
                delete temp;
            }
            return true;
        }
        for(int i = 0; i < expandNum; ++i){
            Index nextPosition = std::make_pair<int, int>(currPosition.first + moveDirection[i].first,
                                                  currPosition.second + moveDirection[i].second);
            if(isValid(nextPosition) && visited[nextPosition.first][nextPosition.second] == false){
                q.push(new WeightedNode(nextPosition, currNode, currNode->weight + map[nextPosition.first][nextPosition.second]));
                visited[nextPosition.first][nextPosition.second] = true;
            }
        }
    }
    while(!trashCollector.empty()){
        WeightedNode* temp = trashCollector.top();
        trashCollector.pop();
        delete temp;
    }
    return false;
}
