#pragma once
#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <bits/stdc++.h>

using namespace std;

extern const string inputfile;
extern const string outputfile;

/// Map Configuration

extern const int MATRIX_MAX_LENGTH;

extern const int WALL_INT;
extern const int FOOD_INT;
extern const int PATH_INT;
extern const int PACMAN_INT;
extern const int MONSTER_INT;

extern const int MOVE_COST;
extern const int FOOD_SCORE;

extern const char WALL_CHAR;
extern const char FOOD_CHAR;
extern const char PATH_CHAR;
extern const char PACMAN_CHAR;
extern const char MONSTER_CHAR;

extern char MAP_CHARS[5];

extern pair<int, int> MOVES[4];

/// Level 3 Constants

/**
Here, we choose the probability function of each turn is 1/(1+a*t) where t is the index of the turn (base 1)
The problem is how to choose good constant a.
We decided to use Ternary search to find a within the exclusive range from LOWER_BOUND to UPPER_BOUND.
TERN_SEARCH_LOOP_NUM is the number of loops executed in Ternary search.
TERN_SEARCH_A_NUM is the number of times Pacman explores the map with considered constant a.
MIN_POINT is the threshold that if the game point is below that threshold, the current game is terminated.

The choice of next move is made by considering which tile has food. If many tiles have foods, these tiles also have equal probability to be chosen.
Otherwise, if there is no tile having food, all tiles also have equal probability to be chosen.

The training file's format:
- the first line consists of one integer which is the number of maps in the file
- in each map:
  - the first line consists of two integers which are the number of rows n and the number of columns m, respectively.
  - each of the next n lines consists of m integers which are the entries of each row.
*/

extern const double LOWER_BOUND;
extern const double UPPER_BOUND;
extern const int TERN_SEARCH_LOOP_NUM;
extern const int TERN_SEARCH_A_NUM;
extern const int MIN_POINT;

extern const string trainingfile;

#endif
