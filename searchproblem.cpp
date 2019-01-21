#include "searchproblem.h"

SearchProblem::SearchProblem(Map _map, Index _origin, Index _destination)
{
    map = _map;
    origin = _origin;
    destination = _destination;
    height = map.size();
    width = map[0].size();
    visited.resize(height);
    for(int i = 0; i < height; ++i){
        visited[i] = std::vector<bool>(width, false);
    }
}

std::vector<std::vector<bool>> SearchProblem::getVisited(){
    return visited;
}

std::vector<Index> SearchProblem::getPath(){
    return path;
}

bool SearchProblem::isValid(Index pos){
    return (pos.first>=0&&pos.first<height
            &&pos.second>=0&&pos.second<width
            &&map[pos.first][pos.second]!=0);
}
