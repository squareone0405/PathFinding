#include "dwastarsearch.h"

DWAStarSearch::DWAStarSearch(Map _map, Index _origin, Index _destination)
    : SearchProblem(_map, _origin, _destination)
{
}

bool DWAStarSearch::findPath(){
    std::priority_queue<Node4AStar*, std::vector<Node4AStar*> ,CmpAStar> q;
    std::stack<Node4AStar*> trashCollector;
    std::vector<std::vector<bool>> closed = std::vector<std::vector<bool>>();
    closed.resize(map.size());
    for(int i = 0; i < map.size(); ++i)
        closed[i] = std::vector<bool>(map[i].size(), false);
    while(!q.empty())
        q.pop();
    float N = getHuristic(origin, destination) * 3.0;
    float epsilon = 0.5;
    float weight = 0.0;
    q.push(new Node4AStar(origin, nullptr, getHuristic(origin, destination) * (1.0+epsilon), 0));
    while(!q.empty()){
        Node4AStar* currNode = q.top();
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
                currNode = (Node4AStar*)(currNode->prevNode);
            }
            while(!trashCollector.empty()){
                Node4AStar* temp = trashCollector.top();
                trashCollector.pop();
                delete temp;
            }
            return true;
        }
        for(int i = 0; i < expandNum; ++i){
            Index nextPosition = std::make_pair<int, int>(currPosition.first + moveDirection[i].first,
                                                  currPosition.second + moveDirection[i].second);
            if(isValid(nextPosition) && closed[nextPosition.first][nextPosition.second] == false){
                weight = 0;
                if((currNode->g) <= N)
                    weight = epsilon * (1.0 - (currNode->g)/N);
                //qDebug("%f",(1.0 +  epsilon * (1.0 - (currNode->g)/N)));
                q.push(new Node4AStar(nextPosition, currNode,
                                      getHuristic(nextPosition, destination) * (1.0 + weight),
                                      currNode->g + map[nextPosition.first][nextPosition.second]));
                visited[nextPosition.first][nextPosition.second] = true;
            }
        }
    }
    while(!trashCollector.empty()){
        Node4AStar* temp = trashCollector.top();
        trashCollector.pop();
        delete temp;
    }
    return false;
}
