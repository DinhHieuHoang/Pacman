#pragma once
#ifndef _PACMANAGENT_H
#define _PACMANAGENT_H

#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

class MinQueueElement{
public:
    pair<int, int> coord; ///coordinate
    int utilityValue;
    int cost;
public:
    MinQueueElement():coord(make_pair(-1,-1)), utilityValue(INT_MAX), cost(0){}
    MinQueueElement(int x, int y, int uv, int c):coord(make_pair(x, y)), utilityValue(uv), cost(c){}
};

class PriorityQueue{
public:
    int nrow, ncolumn;
    int startIndex;
    vector<MinQueueElement> minQueue;

    int **trace;
    int **onQueue;

public:
    PriorityQueue(int n, int m):nrow(n), ncolumn(m),startIndex(0){
        trace = new int*[nrow];
        onQueue = new int*[nrow];
        for(int i=0; i<nrow; i++){
            trace[i] = new int[ncolumn];
            onQueue[i] = new int[ncolumn];

            for(int j = 0; j<ncolumn; j++){
                trace[i][j] = -1;
                onQueue[i][j]=-1;
            }
        }
    }
    ~PriorityQueue(){
        for(int i=0; i<nrow; i++){
            delete trace[i];
            delete onQueue[i];
        }
        delete trace;
        delete onQueue;
    }
    void insertNewElement(int x, int y, int uv, int c);
    void move(int x, int y, int fx, int fy, int imove);
    bool empty();
    vector<int> traceBack(int x, int y, int s, int t);
    void pop();
    MinQueueElement front();
    MinQueueElement getCoordinate(int x, int y);
    bool hasVisited(int x, int y);
};

int ManhattanDistance(pair<int, int>, pair<int, int>);

class LearnedMatrix{
public:
    int **lMatrix;
    pair<int, int> currentPosition;
public:
    LearnedMatrix(){
        lMatrix = new int*[MATRIX_MAX_LENGTH*2+1];
        for(int i =0; i<MATRIX_MAX_LENGTH*2+1; i++){
            lMatrix[i]=new int[MATRIX_MAX_LENGTH*2+1];
            for(int j = 0; j<MATRIX_MAX_LENGTH*2+1; j++){
                lMatrix[i][j] = -1;
            }
        }
        currentPosition = make_pair(0, 0);
    }
    ~LearnedMatrix(){
        for(int i=0; i<MATRIX_MAX_LENGTH*2+1; i++){
            delete lMatrix[i];
        }
        delete lMatrix;
    }

    int getAtPosition(int, int);
};

class PacmanAgent{
public:
    //LearnedMatrix learnedMatrix;
    double level3_a = 0;
public:
    pair<int, int> findCurrentPosition(int nrow, int ncolumn, vector<int>inputMatrix[]);
    pair<int, int> findFoodPosition(int nrow, int ncolumn, vector<int>inputMatrix[]);
    vector<int> level1_BFS(int nrow, int ncolumn, vector<int>inputMatrix[]);
    vector<int> level1_A_Star(int nrow, int ncolumn, vector<int> inputMatrix[]);
    vector<int> level2(int nrow, int ncolumn, vector<int> inputMatrix[]);

    void move(int i, vector<int> inputMatrix[]);

    double calculateProbOfMov(double a, int t);
    bool random(double a);
    pair<double, pair<int, int>> playThisGame(int nrow, int ncolumn, vector<int> inputMatrix[], double a);

    double train(int nrow, int ncolumn, vector<int> inputMatrix[]);
    vector<int> level3(int nrow, int ncolumn, vector<int> inputMatrix[]);

    int level4(int nrow, int ncolumn, vector<int> inputMatrix[]);///play in turns
    void endGame();
};

#endif // _PACMANAGENT_H
