#include "Astar.h"

using namespace std;

vector<int> searchPath(pair<int, int> source, pair<int, int> destination, int nrow, int ncolumn, vector<int> inputMatrix[], int ourHero){
    if(source.first<0 || source.second<0 || destination.first<0 || destination.second<0){
        return vector<int>();
    }
    PriorityQueue priorityQueue(nrow, ncolumn);
    priorityQueue.insertNewElement(source.first, source.second, ManhattanDistance(source, destination), 0);
    while(!priorityQueue.empty()){
        MinQueueElement tmp = priorityQueue.front();
        if(tmp.coord.first == destination.first && tmp.coord.second == destination.second){
            return priorityQueue.traceBack(destination.first, destination.second, source.first, source.second);
        }
        priorityQueue.pop();
        for(int i=0; i<sizeof(MOVES); i++){
            int x_next = tmp.coord.first + MOVES[i].first;
            int y_next = tmp.coord.second + MOVES[i].second;

            if(x_next<0 || y_next<0 || x_next>nrow || y_next>ncolumn){
                continue;
            }

            if(priorityQueue.hasVisited(x_next, y_next)){
                continue;
            }

            if(inputMatrix[x_next][y_next] == WALL_INT){
                continue;
            }

            if(ourHero == PACMAN_INT && inputMatrix[x_next][y_next] == MONSTER_INT){
                continue;
            }

            priorityQueue.move(tmp.coord.first, tmp.coord.second, destination.first, destination.second, i);
        }
    }
    return vector<int>();
}
