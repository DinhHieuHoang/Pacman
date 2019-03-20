#pragma once
#ifndef _ASTAR_H
#define _ASTAR_H

#include <bits/stdc++.h>
#include "constants.h"
#include "pacmanagent.h"

using namespace std;

vector<int> searchPath(pair<int, int> source, pair<int, int> destination, int nrow, int ncolumn, vector<int> inputMatrix[], int ourHero);

#endif // _ASTAR_H
