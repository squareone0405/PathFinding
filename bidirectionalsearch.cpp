#include "bidirectionalsearch.h"

BidirectionalSearch::BidirectionalSearch(Map _map, Index _origin, Index _destination)
                                         : SearchProblem(_map, _origin, _destination)
{
}

bool BidirectionalSearch::findPath(){
    Index moveDirection4DiagonalFirst[8] = {std::make_pair<int, int>(-1, -1), std::make_pair<int, int>(1, -1),
                                            std::make_pair<int, int>(-1, 1), std::make_pair<int, int>(1, 1),
                                            std::make_pair<int, int>(-1, 0), std::make_pair<int, int>(0, -1),
                                            std::make_pair<int, int>(1, 0), std::make_pair<int, int>(0, 1)};
    int visitOrder = 0;
    if(expandNum == 4)
        visitOrder = 4;
    std::vector<std::vector<Node*>> visitedByOrigin;
    visitedByOrigin.resize(height);
    for(int i = 0; i < height; ++i){
        visitedByOrigin[i] = std::vector<Node*>(width, nullptr);
    }
    std::vector<std::vector<Node*>> visitedByDestination;
    visitedByDestination.resize(height);
    for(int i = 0; i < height; ++i){
        visitedByDestination[i] = std::vector<Node*>(width, nullptr);
    }
    std::queue<Node*> qOrigin;
    std::queue<Node*> qDestination;
    std::stack<Node*> trashCollector;
    while(!qOrigin.empty())
        qOrigin.pop();
    qOrigin.push(new Node(origin, nullptr));
    while(!qDestination.empty())
        qDestination.pop();
    qDestination.push(new Node(destination, nullptr));
    while(!qOrigin.empty() && !qDestination.empty()){
        Node* currNodeOrigin = qOrigin.front();
        Node* currNodeDestination = qDestination.front();
        qOrigin.pop();
        qDestination.pop();
        trashCollector.push(currNodeOrigin);
        trashCollector.push(currNodeDestination);
        Index currPositionOrigin = currNodeOrigin->currPos;
        Index currPositionDestination = currNodeDestination->currPos;
        if(visitedByDestination[currPositionOrigin.first][currPositionOrigin.second]
                || visitedByOrigin[currPositionDestination.first][currPositionDestination.second]){
            Index converge = std::make_pair<int, int>(-1, -1);
            if(visitedByDestination[currPositionOrigin.first][currPositionOrigin.second])
                converge = currPositionOrigin;
            else if(visitedByOrigin[currPositionDestination.first][currPositionDestination.second])
                converge = currPositionDestination;
            path.clear();
            path.push_back(converge);
            Node* nodeOnPathOrigin = visitedByOrigin[converge.first][converge.second];
            Node* nodeOnPathDestination = visitedByDestination[converge.first][converge.second];
            while(nodeOnPathOrigin->prevNode != nullptr){
                path.push_back(nodeOnPathOrigin->currPos);
                nodeOnPathOrigin = nodeOnPathOrigin->prevNode;
            }
            while(nodeOnPathDestination->prevNode != nullptr){
                path.push_back(nodeOnPathDestination->currPos);
                nodeOnPathDestination = nodeOnPathDestination->prevNode;
            }
            path.push_back(destination);
            while(!trashCollector.empty()){
                Node* temp = trashCollector.top();
                trashCollector.pop();
                delete temp;
            }
            return true;
        }
        for(int i = visitOrder; i < 8; ++i){
            Index nextPosition = std::make_pair<int, int>(currPositionOrigin.first + moveDirection4DiagonalFirst[i].first,
                                                  currPositionOrigin.second + moveDirection4DiagonalFirst[i].second);
            if(isValid(nextPosition) && visitedByOrigin[nextPosition.first][nextPosition.second] == nullptr){
                qOrigin.push(new Node(nextPosition, currNodeOrigin));
                visitedByOrigin[nextPosition.first][nextPosition.second] = currNodeOrigin;
                visited[nextPosition.first][nextPosition.second] = true;
            }
        }
        for(int i = visitOrder; i < 8; ++i){
            Index nextPosition = std::make_pair<int, int>(currPositionDestination.first + moveDirection4DiagonalFirst[i].first,
                                                  currPositionDestination.second + moveDirection4DiagonalFirst[i].second);
            if(isValid(nextPosition) && visitedByDestination[nextPosition.first][nextPosition.second] == nullptr){
                qDestination.push(new Node(nextPosition, currNodeDestination));
                visitedByDestination[nextPosition.first][nextPosition.second] = currNodeDestination;
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
