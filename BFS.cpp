#include "BFS.h"

using namespace std;

vector<int> searchPathBFS(pair<int, int> source, pair<int, int> destination, int nrow, int ncolumn, vector<int> inputMatrix[], int ourHero){
    int parent[nrow][ncolumn];
    bool isVisited[nrow][ncolumn];
    bool inFrontier[nrow][ncolumn];

    memset(parent, -1, sizeof(parent));
    memset(isVisited, false, sizeof(isVisited));
    memset(inFrontier, false, sizeof(inFrontier));

    queue<pair<int, int>> bfsQueue;
    bfsQueue.push(source);
    inFrontier[source.first][source.second] = true;

    pair<int, int> currentPosition;
    vector<int> moves;

    while(!bfsQueue.empty()){
        currentPosition = bfsQueue.front();
        bfsQueue.pop();

        isVisited[currentPosition.first][currentPosition.second]=true;
        for(size_t i=0; i<sizeof(MOVES); ++i){
            pair<int, int> nextPosition = make_pair(currentPosition.first + MOVES[i].first, currentPosition.second + MOVES[i].second);
            if(nextPosition.first<0 || nextPosition.first>=nrow){
                continue;
            }
            if(nextPosition.second < 0 || nextPosition.second>=ncolumn){
                continue;
            }
            if(inputMatrix[nextPosition.first][nextPosition.second] == WALL_INT){
                continue;
            }
            if(ourHero == PACMAN_INT && inputMatrix[nextPosition.first][nextPosition.second] == MONSTER_INT){
                continue;
            }
            if(!(isVisited[nextPosition.first][nextPosition.second]||inFrontier[nextPosition.first][nextPosition.second])){
                if(destination.first == nextPosition.first && destination.second){
                    moves.push_back(i);
                    while(currentPosition.first!=source.first || currentPosition.second!=source.second){
                        moves.push_back(parent[currentPosition.first][currentPosition.second]^2);
                        currentPosition = make_pair(currentPosition.first + MOVES[parent[currentPosition.first][currentPosition.second]].first, currentPosition.second + MOVES[parent[currentPosition.first][currentPosition.second]].second);
                    }
                    reverse(moves.begin(), moves.end());
                    return moves;
                }
                inFrontier[nextPosition.first][nextPosition.second]=true;
                bfsQueue.push(nextPosition);
                parent[nextPosition.first][nextPosition.second]=i^2;
            }
        }
    }
    return moves;
}
