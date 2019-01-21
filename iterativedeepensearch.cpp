#include "iterativedeepensearch.h"

IterativeDeepenSearch::IterativeDeepenSearch(Map _map, Index _origin, Index _destination)
    : SearchProblem(_map, _origin, _destination)
{
}

bool IterativeDeepenSearch::findPath(){
    trashCollector = std::stack<Node*>();
    depthTablePrev = NodeMap();
    depthTableCurr = NodeMap();
    for (int i = 1; true; ++i){
        depthTablePrev = depthTableCurr;
        depthTableCurr.clear();
        if (depthLimitedSearch(new Node(origin, nullptr), 0, i)){
            path.clear();
            while(finalNode->prevNode != nullptr){
                path.push_back(finalNode->currPos);
                finalNode = finalNode->prevNode;
            }
            while(!trashCollector.empty()){
                Node* temp = trashCollector.top();
                trashCollector.pop();
                delete temp;
            }
            return true;
        }
        else if(depthTableCurr.size() == depthTablePrev.size())
            break;
    }
    while(!trashCollector.empty()){
        Node* temp = trashCollector.top();
        trashCollector.pop();
        delete temp;
    }
    return false;
}

bool IterativeDeepenSearch::depthLimitedSearch(Node* node, int currDepth, int maxDepth){
    if(currDepth > maxDepth)
        return false;
    Index currPosition = node->currPos;
    if(currPosition == destination){
        finalNode = node;
        return true;
    }
    depthTableCurr[Node(currPosition, nullptr)] = currDepth;
    trashCollector.push(node);
    for(int i = 0; i < expandNum; ++i){
        Index nextPosition = std::make_pair<int, int>(currPosition.first + moveDirection[i].first,
                                              currPosition.second + moveDirection[i].second);
        if(isValid(nextPosition)){
            if(depthTablePrev.find(Node(nextPosition, nullptr)) == depthTablePrev.end()
                    || depthTablePrev[Node(nextPosition, nullptr)] >= (currDepth + 1)){
                if(depthTableCurr.find(Node(nextPosition, nullptr)) == depthTableCurr.end()
                        || depthTableCurr[Node(nextPosition, nullptr)] > (currDepth + 1)){
                    visited[nextPosition.first][nextPosition.second] = true;
                    if(depthLimitedSearch(new Node(nextPosition, node), currDepth + 1, maxDepth))
                        return true;
                }
            }
        }
    }
    return false;
}
