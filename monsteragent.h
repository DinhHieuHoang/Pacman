#pragma once
#ifndef _MONSTERAGENT_H
#define _MONSTERAGENT_H

#include <bits/stdc++.h>
#include "constants.h"
#include "Astar.h"
#include "agent.h"

using namespace std;

class MonsterAgent{
public:
    pair<int, int> currentPosition;
public:
    MonsterAgent(){}
    MonsterAgent(pair<int, int> c):currentPosition(c){}

    void move(int i, vector<int> inputMatrix[]);

    int level4_1(int nrow, int ncolumn, vector<int> inputMatrix[]);
};


#endif // _MONSTERAGENT_H
