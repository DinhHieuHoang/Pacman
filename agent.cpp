#include "agent.h"

using namespace std;

void Map::init(int nrow, int ncolumn, vector<int> inputMatrix[]){
    Map::point = 0;

    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncolumn; j++){
            if(inputMatrix[i][j] == PACMAN_INT){
                Map::pacmanPosition = make_pair(i, j);
            }
            if(inputMatrix[i][j] == MONSTER_INT){
                Map::monsterPositions[make_pair(i, j)] = true;
            }
            if(inputMatrix[i][j] == FOOD_INT){
                Map::foodPositions[make_pair(i,j)] = true;
            }
        }
    }
}

void Map::chooseRandomMap(){
    /// choose map randomly from the file "training.txt"
}
