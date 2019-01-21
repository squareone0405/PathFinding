#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch(Map _map, Index _origin, Index _destination)
    : SearchProblem(_map, _origin, _destination)
{
}

bool DepthFirstSearch::findPath(){
    std::stack<Node*> s;
    std::stack<Node*> trashCollector;
    while(!s.empty())
        s.pop();
    s.push(new Node(origin, nullptr));
    while(!s.empty()){
        Node* currNode = s.top();
        trashCollector.push(currNode);
        Index currPosition = currNode->currPos;
        s.pop();
        if(currPosition == destination){
            path.clear();
            while(currNode->prevNode != nullptr){
                path.push_back(currNode->prevNode->currPos);
                currNode = currNode->prevNode;
            }
            while(!trashCollector.empty()){
                Node* temp = trashCollector.top();
                trashCollector.pop();
                delete temp;
            }
            return true;
        }
        for(int i = 0; i < expandNum; ++i){
            Index nextPosition = std::make_pair<int, int>(currPosition.first + moveDirection[i].first,
                                                  currPosition.second + moveDirection[i].second);
            if(isValid(nextPosition) && visited[nextPosition.first][nextPosition.second] == false){
                s.push(new Node(nextPosition, currNode));
                visited[nextPosition.first][nextPosition.second] = true;
            }
        }
    }
    while(!trashCollector.empty()){
        Node* temp = trashCollector.top();
        trashCollector.pop();
        delete temp;
    }
    return false;
}
