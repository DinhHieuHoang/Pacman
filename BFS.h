#pragma once
#ifndef _BFS_H
#define _BFS_H

#include <bits/stdc++.h>
#include "constants.h"
#include "pacmanagent.h"

using namespace std;

vector<int> searchPathBFS(pair<int, int> source, pair<int, int> destination, int nrow, int ncolumn, vector<int> inputMatrix[], int ourHero);

#endif // _BFS_H
