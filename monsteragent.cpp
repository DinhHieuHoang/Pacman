#include "monsteragent.h"

using namespace std;

void MonsterAgent::move(int i, vector<int> inputMatrix[]){
    if(i<0){
        return;
    }
    inputMatrix[currentPosition.first][currentPosition.second] = PATH_INT;
    if(Map::foodPositions.find(currentPosition)!=Map::foodPositions.end()){
        inputMatrix[currentPosition.first][currentPosition.second] = FOOD_INT;
    }
    Map::monsterPositions.erase(currentPosition);
    currentPosition.first += MOVES[i].first;
    currentPosition.second +=MOVES[i].second;
    inputMatrix[currentPosition.first][currentPosition.second] = MONSTER_INT;
    Map::monsterPositions[currentPosition]=true;
    if(currentPosition == Map::pacmanPosition){
        cout<<"Monster ate Pacman"<<endl;
    }
}

int MonsterAgent::level4_1(int nrow, int ncolumn, vector<int> inputMatrix[]){
    /// guess the aim of Pacman
    int mx = INT_MAX;
    pair<int, int> guess = make_pair(-1, -1);
    for(map<pair<int, int>,bool>::iterator i = Map::foodPositions.begin(); i!=Map::foodPositions.end(); i++){
        int tmp = searchPath(Map::pacmanPosition, i->first, nrow, ncolumn, inputMatrix, PACMAN_INT).size();
        if(mx > tmp){
            guess = i->first;
            mx = tmp;
        }
    }

    vector<int> path = searchPath(currentPosition, guess, nrow, ncolumn, inputMatrix, MONSTER_INT);
    vector<int> pacPath = searchPath(currentPosition, Map::pacmanPosition, nrow, ncolumn, inputMatrix, MONSTER_INT);
    if(pacPath.size()<=path.size()){
        if(pacPath.size()>0)
            return pacPath[0];
    }
    if(path.empty()){
        return -1;
    }
    return path[0];
}
