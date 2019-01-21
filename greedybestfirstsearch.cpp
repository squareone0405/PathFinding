#include "greedybestfirstsearch.h"

GreedyBestFirstSearch::GreedyBestFirstSearch(Map _map, Index _origin, Index _destination)
    : SearchProblem(_map, _origin, _destination)
{
}

bool GreedyBestFirstSearch::findPath(){
    std::priority_queue<WeightedNode*, std::vector<WeightedNode*> ,Cmp> q;
    std::stack<WeightedNode*> trashCollector;
    while(!q.empty())
        q.pop();
    q.push(new WeightedNode(origin, nullptr, getHuristic(origin, destination)));
    while(!q.empty()){
        WeightedNode* currNode = q.top();
        trashCollector.push(currNode);
        Index currPosition = currNode->currPos;
        q.pop();
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
                q.push(new WeightedNode(nextPosition, currNode, getHuristic(nextPosition, destination)));
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
