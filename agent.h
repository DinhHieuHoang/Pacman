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
    static map<pair<int, int>, int> monsterPositions;

public:
    static void init(int nrow, int ncolumn, vector<int> inputMatrix[]);
    static int chooseRandomMap(int &nrow, int &ncolumn, vector<int> inputMatrix[], string sss);
    static void loadMap(int chosenFile, int &nrow, int &ncolumn, vector<int> inputMatrix[], string sss);
    static bool isFinished();
};

#endif // _AGENT_H
