#include "agent.h"

using namespace std;

void Map::init(int nrow, int ncolumn, vector<int> inputMatrix[]){
    point = 0;

    foodPositions.clear();
    monsterPositions.clear();

    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncolumn; j++){
            if(inputMatrix[i][j] == PACMAN_INT){
                pacmanPosition = make_pair(i, j);
            }
            if(inputMatrix[i][j] == MONSTER_INT){
                if(monsterPositions.find(make_pair(i, j))==monsterPositions.end())
                {
                    monsterPositions[make_pair(i, j)] = 1;
                }
                else{
                    monsterPositions[make_pair(i,j)]++;
                }
            }
            if(inputMatrix[i][j] == FOOD_INT){
                Map::foodPositions[make_pair(i,j)] = true;
            }
        }
    }
}

int Map::chooseRandomMap(int &nrow, int &ncolumn, vector<int> inputMatrix[], string sss){
    /// choose map randomly from the file "training.txt"
    Map::point = 0;
    int chosenFile = rand() % numOfTrainingFile+ 1;
    stringstream ss;
    ss << chosenFile;
    string fileIndex = ss.str();

    string filename;
    if(sss == trainingfile)
        filename = trainingfile + fileIndex + txtExtension;
    else
        filename = validatingfile + fileIndex + txtExtension;
    ifstream fin(filename);
    fin>>nrow>>ncolumn;
    for(int i=0; i<nrow; i++){
        inputMatrix[i].clear();
        for(int j=0; j<ncolumn; j++){
            int inp;
            fin>>inp;
            inputMatrix[i].push_back(inp);
        }
    }
    fin.close();
    init(nrow, ncolumn, inputMatrix);
    return chosenFile;
}

void Map::loadMap(int chosenFile, int &nrow, int &ncolumn, vector<int> inputMatrix[], string sss){
    Map::point = 0;
    stringstream ss;
    ss << chosenFile;
    string fileIndex = ss.str();
    string filename;
    if(sss == trainingfile)
        filename = trainingfile + fileIndex + txtExtension;
    else
        filename = validatingfile + fileIndex + txtExtension;
    ifstream fin(filename);
    fin>>nrow>>ncolumn;
    for(int i=0; i<nrow; i++){
        inputMatrix[i].clear();
        for(int j=0; j<ncolumn; j++){
            int inp;
            fin>>inp;
            inputMatrix[i].push_back(inp);
        }
    }
    fin.close();
    init(nrow, ncolumn, inputMatrix);
}

bool Map::isFinished() {
    if(pacmanPosition.first == -1 && pacmanPosition.second == -1){
        return true;
    }
    return false;
}
