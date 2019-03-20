#pragma once
#ifndef _AGENT_H
#define _AGENT_H

#include <bits/stdc++.h>
#include "constants.h"
#include "pacmanagent.h"

using namespace std;

class Map{
public:
    static int point;
    static pair<int, int> pacmanPosition;
    static map<pair<int, int>, bool> foodPositions;
    static map<pair<int, int>, bool> monsterPositions;

public:
    static void init(int nrow, int ncolumn, vector<int> inputMatrix[]);
    static void chooseRandomMap();
};

#endif // _AGENT_H
