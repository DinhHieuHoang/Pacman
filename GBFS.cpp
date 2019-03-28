#include "GBFS.h"

int GBFS(pair<int, int> src, int row, int col, vector<int> inputMaxtrix[], vector<pair<int, int>> monsterPos, int monsNo){
    int score, tmpX, tmpY;

    pair<int, int> foodPos = nearestFood(src, row, col, inputMaxtrix);
    pair<int, int> nextPos;
    int retMove = -1, retScore = -1000000000;

    for (int i = 0; i < sizeof(MOVES); ++i){
        tmpX = src.first + MOVES[i].first;
        tmpY = src.second + MOVES[i].second;
        nextPos = make_pair(tmpX, tmpY);
        if (tmpX < 0 || tmpY < 0 || inputMaxtrix[tmpX][tmpY] == WALL_INT){
            continue;
        } else {
            // Calculate the score for the next moves
            score = ManhattanDistance(nextPos, foodPos);
            for (int i = 0; i < monsNo; ++i){
                score -= ManhattanDistance(nextPos, monsterPos[i]);
            }

            // If the score is better , record the move for return
            if (score > retScore){
                retScore = score;
                retMove = i;
            }
        }
    }

    return retMove;
}

pair<int, int> nearestFood(pair<int, int> src, int row, int col, vector<int> inputMaxtrix[]){
    pair<int, int> ret = make_pair(-1, -1);
    pair<int, int> tmp;
    int dist = 1000000000;

    for (int i = 0; i < col; ++i){
        for (int j = 0; j < row; ++j){
            tmp = make_pair(i, j);
            if (inputMaxtrix[i][j] == FOOD_INT && ManhattanDistance(tmp, src) < dist){
                dist = ManhattanDistance(tmp, src);
                ret = tmp;
            }   
        }
    }

    return ret;
}
