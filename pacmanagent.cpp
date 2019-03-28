#include <bits/stdc++.h>
#include "pacmanagent.h"
#include "constants.h"
#include "agent.h"

using namespace std;

void PriorityQueue::insertNewElement(int x, int y, int uv, int c){
    MinQueueElement newElement(x, y, uv, c);

    onQueue[x][y] = minQueue.size();
    minQueue.push_back(newElement);

    int currentPosition = minQueue.size()-1;
    int nextPosition = (currentPosition - 1) / 2;
    while (currentPosition > 0 && minQueue[currentPosition].utilityValue > minQueue[nextPosition].utilityValue)
    {
        swap(minQueue[currentPosition], minQueue[nextPosition]);
        currentPosition = nextPosition;
        nextPosition = (currentPosition-1)/2;
    }
}

MinQueueElement PriorityQueue::getCoordinate(int x, int y){
    if(onQueue[x][y]<0){
        MinQueueElement nullElement;
        return nullElement;
    }
    return minQueue[onQueue[x][y]];
}

void PriorityQueue::move(int x, int y, int fx, int fy, int imove){
    int x_next = x+MOVES[imove].first;
    int y_next = y+MOVES[imove].second;

    trace[x_next][y_next] = imove^2;
    //cout<<x_next<<" "<<y_next<<" "<<(imove^2)<<endl;
    insertNewElement(x_next, y_next, ManhattanDistance(make_pair(x,y), make_pair(fx, fy)), 1+getCoordinate(x,y).cost);
}

bool PriorityQueue::empty(){
    return minQueue.empty();
}

vector<int> PriorityQueue::traceBack(int x, int y, int s, int t){
    vector<int> moves;
    while(x!=s || y!=t){
        int imove = trace[x][y];
        if(imove<0){
            cout<<"No path found"<<endl;
            vector<int> nullVector;
            return nullVector;
        }
        moves.push_back(imove^2);
        x = x + MOVES[imove].first;
        y = y + MOVES[imove].second;
    }
    reverse(moves.begin(), moves.end());
    return moves;
}

int LearnedMatrix::getAtPosition(int i, int j){
    return lMatrix[MATRIX_MAX_LENGTH+i][MATRIX_MAX_LENGTH+j];
}

pair<int,int> PacmanAgent::findCurrentPosition(int nrow, int ncolumn, vector<int>inputMatrix[]){
    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncolumn; j++){
            if(inputMatrix[i][j] == PACMAN_INT){
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1);
}

pair<int, int> PacmanAgent::findFoodPosition(int nrow, int ncolumn, vector<int> inputMatrix[]){
    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncolumn; j++){
            if(inputMatrix[i][j] == FOOD_INT){
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1);
}

vector<int> PacmanAgent::level1_BFS(int nrow, int ncolumn, vector<int>inputMatrix[]){
    /// find current position:
    pair<int, int> pacmanPosition = findCurrentPosition(nrow, ncolumn, inputMatrix);

    /// find food's position:
    pair<int, int> foodPosition = findFoodPosition(nrow, ncolumn, inputMatrix);

    /// BFS
    int parent[nrow][ncolumn];
    bool isVisited[nrow][ncolumn];
    bool inFrontier[nrow][ncolumn];

    memset(parent, -1, sizeof(parent));
    memset(isVisited, false, sizeof(isVisited));
    memset(inFrontier, false, sizeof(inFrontier));

    queue<pair<int, int>> bfsQueue;
    bfsQueue.push(pacmanPosition);
    inFrontier[pacmanPosition.first][pacmanPosition.second] = true;

    pair<int, int> currentPosition;

    vector<int> moves;

    bool found=false;

    while(!bfsQueue.empty()){
        currentPosition = bfsQueue.front();
        bfsQueue.pop();

        isVisited[currentPosition.first][currentPosition.second] = true;
        for(size_t i=0; i<4; ++i){
            if(currentPosition.first + MOVES[i].first<0 || currentPosition.first + MOVES[i].first>=nrow){
                continue;
            }
            if(currentPosition.second + MOVES[i].second < 0 || currentPosition.second + MOVES[i].second>=ncolumn){
                continue;
            }
            if(inputMatrix[currentPosition.first + MOVES[i].first][currentPosition.second + MOVES[i].second] == WALL_INT || inputMatrix[currentPosition.first + MOVES[i].first][currentPosition.second + MOVES[i].second] == MONSTER_INT){
                continue;
            }
            if(!(isVisited[currentPosition.first + MOVES[i].first][currentPosition.second + MOVES[i].second] || inFrontier[currentPosition.first + MOVES[i].first][currentPosition.second + MOVES[i].second])){
                if(foodPosition.first == currentPosition.first + MOVES[i].first && foodPosition.second == currentPosition.second + MOVES[i].second){

                    moves.push_back(i);
                    while(currentPosition.first!=pacmanPosition.first || currentPosition.second!=pacmanPosition.second){
                        moves.push_back(parent[currentPosition.first][currentPosition.second]^2);
                        currentPosition = make_pair(currentPosition.first + MOVES[parent[currentPosition.first][currentPosition.second]].first, currentPosition.second + MOVES[parent[currentPosition.first][currentPosition.second]].second);
                    }
                    found=true;
                    break;
                }
                inFrontier[currentPosition.first + MOVES[i].first][currentPosition.second + MOVES[i].second] = true;
                bfsQueue.push(make_pair(currentPosition.first + MOVES[i].first, currentPosition.second + MOVES[i].second));
                parent[currentPosition.first + MOVES[i].first][currentPosition.second + MOVES[i].second] = i^2;
            }
        }
        if(found){
            break;
        }
    }

    vector<int> nullVector;

    ///output
    if(moves.empty()){
        return nullVector;
    }

    if(moves.size()*MOVE_COST>FOOD_SCORE){
        return nullVector;
    }

    reverse(moves.begin(), moves.end());
    return moves;
}

int ManhattanDistance(pair<int, int> a, pair<int, int> b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

MinQueueElement PriorityQueue::front(){
    return minQueue[0];
}

void PriorityQueue::pop()
{
    MinQueueElement f = front();
    onQueue[f.coord.first][f.coord.second] = -2;
    swap(minQueue[0], minQueue[minQueue.size()-1]);
    minQueue.pop_back();
    int current = 0;
    while(current*2+1<minQueue.size()){
        int tmp = current*2+1;
        if(tmp+1<minQueue.size()){
            if(minQueue[tmp].utilityValue>minQueue[tmp+1].utilityValue){
                tmp++;
            }
        }
        if(minQueue[current].utilityValue>minQueue[tmp].utilityValue){
            swap(minQueue[current], minQueue[tmp]);
        }
        else{
            break;
        }
        current = tmp;
    }
}

bool PriorityQueue::hasVisited(int x, int y){
    if(trace[x][y]==-1)
    {
        return false;
    }
    return true;
}

vector<int> PacmanAgent::level1_A_Star(int nrow, int ncolumn, vector<int>inputMatrix[]){
    pair<int, int> initialPosition = findCurrentPosition(nrow, ncolumn, inputMatrix);
    pair<int, int> foodPosition = findFoodPosition(nrow, ncolumn, inputMatrix);

    vector<int> nullVector;

    PriorityQueue priorityQueue(nrow, ncolumn);
    priorityQueue.insertNewElement(initialPosition.first, initialPosition.second, ManhattanDistance(initialPosition, foodPosition), 0);
    while(!priorityQueue.empty()){
        MinQueueElement tmp = priorityQueue.front();
        if(tmp.coord.first == foodPosition.first && tmp.coord.second == foodPosition.second){
            vector<int> tracePath = priorityQueue.traceBack(foodPosition.first, foodPosition.second, initialPosition.first, initialPosition.second);
            if(tracePath.size() * MOVE_COST >= FOOD_SCORE){
                return nullVector;
            }
            return tracePath;
        }
        priorityQueue.pop();
        for(int i=0; i<4; i++){
            int x_next = tmp.coord.first + MOVES[i].first;
            int y_next = tmp.coord.second + MOVES[i].second;

            if(x_next<0 || y_next<0 || x_next>=nrow || y_next>=ncolumn){
                continue;
            }

            if(priorityQueue.hasVisited(x_next, y_next)){
                continue;
            }

            if(inputMatrix[x_next][y_next] == WALL_INT || inputMatrix[x_next][y_next] == MONSTER_INT){
                continue;
            }

            priorityQueue.move(tmp.coord.first, tmp.coord.second, foodPosition.first, foodPosition.second, i);
        }
    }
    return nullVector;
}

vector<int> PacmanAgent::level2(int nrow, int ncolumn, vector<int> inputMatrix[]){
    return level1_A_Star(nrow, ncolumn, inputMatrix);
}

void PacmanAgent::move(int i, vector<int> inputMatrix[]){
    if(i<0){
        return;
    }

    Map::point--;
    pair<int, int> currentPosition = Map::pacmanPosition;
    inputMatrix[currentPosition.first][currentPosition.second] = PATH_INT;
    currentPosition.first += MOVES[i].first;
    currentPosition.second +=MOVES[i].second;
    inputMatrix[currentPosition.first][currentPosition.second] = PACMAN_INT;
    Map::pacmanPosition = currentPosition;

    if(Map::foodPositions.find(currentPosition)!=Map::foodPositions.end()){
        Map::point+=10;
        Map::foodPositions.erase(currentPosition);
    }
}

double PacmanAgent::calculateProbOfMov(double a, int t){
    double dependencyOnGamePoint = Map::point<0?(Map::point*0.3):0;
    return 1.0/(1.0+a*t);
}

bool PacmanAgent::random(double a){
    double sr = rand()*1.0/RAND_MAX;
    if(sr<=a){
        return true;
    }
    return false;
}

pair<double, pair<int,int>> PacmanAgent::playThisGame(int nrow, int ncolumn, vector<int> inputMatrix[], double a, bool prnt){
    freopen("moveList.txt", "a", stdout);
    int ans=0;
    int mrk = 0;
    int t=0;
    int chosenMove;
    while(Map::point >= MIN_POINT){
        if(ans<Map::point){
            ans = Map::point;
            mrk = t;
        }
        ++t;
        //cout<<t<<endl;
        chosenMove = -1;
        //if(!random(calculateProbOfMov(a, t))){
        //    return make_pair(Map::point, make_pair(ans, mrk));
        //}
        vector<int> foodMove;
        vector<int> notFoodMove;
        for(size_t i = 0; i<4; i++){
            int x_next = Map::pacmanPosition.first + MOVES[i].first;
            int y_next = Map::pacmanPosition.second + MOVES[i].second;

            if(x_next < 0 || y_next < 0 || x_next >= nrow || y_next >= ncolumn){
                continue;
            }
            //cout<<x_next<<" "<<y_next<<" "<<i<<endl;
            if(inputMatrix[x_next][y_next] == FOOD_INT){
              //      cout<<"?"<<endl;
                foodMove.push_back(i);
            }
            else if(inputMatrix[x_next][y_next] == PATH_INT){
             //   cout<<"?"<<endl;
                notFoodMove.push_back(i);
            }
        }
        if(!foodMove.empty()){
            chosenMove = rand() % foodMove.size();
            chosenMove = foodMove[chosenMove];
        }
        else if(!notFoodMove.empty()){
            if(!random(calculateProbOfMov(a, t))){
                fclose(stdout);
                return make_pair(Map::point, make_pair(ans, mrk));
            }
            chosenMove = rand() % notFoodMove.size();
            chosenMove = notFoodMove[chosenMove];
        }
        else{
            fclose(stdout);
            return make_pair(Map::point, make_pair(ans, mrk));
        }
        move(chosenMove, inputMatrix);
        if(prnt){
            cout<<chosenMove<<endl;
        }
    }
    fclose(stdout);
    return make_pair(Map::point, make_pair(ans, mrk));
}

double PacmanAgent::train(int nrow, int ncolumn, vector<int> inputMatrix[]){
    double currentUpperBound = UPPER_BOUND;
    double currentLowerBound = LOWER_BOUND;
    double oneThird, twoThird;

    double oneThirdGamePoint;
    double twoThirdGamePoint;

    pair<double, pair<int, int>> point;

    for(int cntLoop = 0; cntLoop<TERN_SEARCH_LOOP_NUM; ++cntLoop){
        oneThird = (2*currentLowerBound + currentUpperBound)/3.0;
        twoThird = (2*currentUpperBound + currentLowerBound)/3.0;

        oneThirdGamePoint = 0.0;
        twoThirdGamePoint = 0.0;

        for(int cntGame = 0; cntGame<TERN_SEARCH_A_NUM; ++cntGame){
            int chosenFile = Map::chooseRandomMap(nrow, ncolumn, inputMatrix, trainingfile);
            point = playThisGame(nrow, ncolumn, inputMatrix, oneThird, false);
            oneThirdGamePoint += point.first;
            Map::loadMap(chosenFile, nrow, ncolumn, inputMatrix, trainingfile);
            point = playThisGame(nrow, ncolumn, inputMatrix, twoThird, false);
            twoThirdGamePoint += point.first;
        }

        if(oneThirdGamePoint > twoThirdGamePoint){
            currentUpperBound = twoThird;
        }
        else{
            currentLowerBound = oneThird;
        }
    }

    level3_a = (oneThird+twoThird)/2.0;

    freopen("output.txt","w",stdout);
    for(int cntGame = 0; cntGame<TERN_SEARCH_A_NUM; ++cntGame){
        int chosenFile = Map::chooseRandomMap(nrow, ncolumn, inputMatrix, validatingfile);
        point = playThisGame(nrow, ncolumn, inputMatrix, level3_a, false);
        cout<<point.first<<" "<<point.second.first<<" "<<point.second.second<<endl;
    }
    fclose(stdout);
    return level3_a;
}

vector<int> PacmanAgent::level3(int nrow, int ncolumn, vector<int> inputMatrix[]){
    return vector<int>();
}

void PacmanAgent::endGame(){
    Map::pacmanPosition = make_pair(-1,-1);
}

int PacmanAgent::level4(int nrow, int ncolumn, vector<int> inputMatrix[]){
    return -1;
}

