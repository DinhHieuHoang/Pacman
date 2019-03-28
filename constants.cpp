#include <bits/stdc++.h>
#include "constants.h"
using namespace std;

const string inputfile = "input.txt";
const string outputfile = "output.txt";
const string trainingfile = "./trainingFiles/training";
const string validatingfile = "./validatingFiles/validating";
const string txtExtension = ".txt";
const int numOfTrainingFile = 150;

/// Map Configuration

const int MATRIX_MAX_LENGTH = 1000;

const int WALL_INT = 1;
const int FOOD_INT = 2;
const int PATH_INT = 0;
const int PACMAN_INT = 4;
const int MONSTER_INT = 3;

const int MOVE_COST = 1;
const int FOOD_SCORE = 10;

const char WALL_CHAR = 254;
const char FOOD_CHAR = 235;
const char PATH_CHAR = '.';
const char PACMAN_CHAR = 'P';
const char MONSTER_CHAR = 'M';

char MAP_CHARS[]={
    WALL_CHAR,
    FOOD_CHAR,
    PATH_CHAR,
    PACMAN_CHAR,
    MONSTER_CHAR
};

pair<int, int> MOVES[]={
    make_pair(0, 1),
    make_pair(1, 0),
    make_pair(0, -1),
    make_pair(-1, 0)
};

/// Level 3 Constants

const double LOWER_BOUND = 0.0;
const double UPPER_BOUND = 50.0;
const int TERN_SEARCH_LOOP_NUM = 25;
const int TERN_SEARCH_A_NUM = 5000;
const int MIN_POINT = -5;
