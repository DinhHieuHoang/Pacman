#ifndef _GBFS_H_
#define _GBFS_H_

#include <bits/stdc++.h>
#include "constants.h"
#include "pacmanagent.h"

// Pacman moves so that the distance to nearest food - sum of distance to all other monster is greatest
int GBFS(pair<int, int> src, int row, int col, vector<int> inputMaxtrix[], vector<pair<int, int>> monsterPos, int monsPos);
pair<int, int> nearestFood(pair<int, int> src, int row, int col, vector<int> inputMaxtrix[]);


#endif