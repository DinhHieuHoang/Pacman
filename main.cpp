#include <bits/stdc++.h>
#include "pacmanagent.h"
#include "monsteragent.h"

using namespace std;

int level;
int n, m;
vector<char> matrix[1000];
vector<int> inputMatrix[1000];

int Map::point = 0;
pair<int, int> Map::pacmanPosition;
map<pair<int, int>, bool> Map::foodPositions;
map<pair<int, int>, int> Map::monsterPositions;

bool input(){
    char inputfilename[inputfile.length()+1];
    for(size_t i=0; i<inputfile.length(); i++){
        inputfilename[i] = inputfile[i];
    }
    inputfilename[inputfile.length()] = '\0';

    freopen(inputfilename, "r", stdin);
    cin>>level;
    cin>>n>>m;
    int inp;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin>>inp;
            inputMatrix[i].push_back(inp);
            matrix[i].push_back(MAP_CHARS[inp]);
        }
    }
    int x, y;
    cin>>x>>y;
    inputMatrix[x][y]=PACMAN_INT;
    fclose(stdin);
    return true;
}

bool output(){
    //freopen(outputfile, "w", stdout);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<MAP_CHARS[inputMatrix[i][j]];
        }
        cout<<endl;
    }
    //fclose(stdout);
    return true;
}

void outputMoves(vector<int> m){

    freopen("moveList.txt", "w", stdout);
    for(int i=0; i<m.size(); i++){
        cout<<m[i]<<endl;
    }
    fclose(stdout);
}

void outputToFile(vector<int> m){
    switch(level){
    case 1:
    case 2:
        cout<<"Path:"<<endl;
        for(auto i: m){
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<"Path length: "<<m.size()<<endl;
        cout<<"Game point: "<<10 - m.size()<<endl;
        break;
    case 3:
        cout<<"Path:"<<endl;
        for(auto i: m){
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<"Path length: "<<m.size()<<endl;
        cout<<"Game point: "<<Map::point<<endl;
        break;
    default:
        break;
    }
}

bool run(){
    PacmanAgent pacman;
    pacman.level3_a=0.01;
    int point;
    int cnt=0;
    int t;
    vector<int> moves;
    switch(level){
    case 1:
        moves = pacman.level1_A_Star(n,m,inputMatrix);
        if(moves.size()>=10){
            moves.clear();
        }
        if(moves.size()==0){
            point=0;
        }
        else{
            point = 10 - moves.size();
        }
        outputMoves(moves);
        freopen("result.txt","w",stdout);
        cout<<"Path length: "<<moves.size()<<endl;
        cout<<"Game point: "<<point<<endl;
        fclose(stdout);
        break;
    case 2:
        moves = pacman.level1_BFS(n,m,inputMatrix);
        if(moves.size()>=10){
            moves.clear();
        }
        if(moves.size()==0){
            point=0;
        }
        else{
            point = 10 - moves.size();
        }
        outputMoves(moves);
        freopen("result.txt","w",stdout);
        cout<<"Path length: "<<moves.size()<<endl;
        cout<<"Game point: "<<point<<endl;
        fclose(stdout);
        break;
    case 3:
        Map::init(n,m,inputMatrix);
        //cout<<Map::pacmanPosition.first<<Map::pacmanPosition.second<<endl;
        pacman.playThisGame(n, m, inputMatrix, pacman.level3_a, true);
        freopen("moveList.txt","r",stdin);
        while(cin>>t){
            cnt++;
        }
        freopen("result.txt","w",stdout);
        cout<<"Path length: "<<cnt<<endl;
        cout<<"Game point: "<<Map::point<<endl;
        fclose(stdout);
        break;
    case 4:
        break;
    default:
        cout<<"Invalid level"<<endl;
        break;
    }
    return true;
}

int main()
{
    srand(time(NULL));

    input();
    run();

//    input();
//    output();
//    Map::init(n, m, inputMatrix);
//    MonsterAgent myMonster(Map::monsterPositions.begin()->first);
//    int mov = myMonster.level4_1(n,m,inputMatrix);
//    myMonster.move(mov, inputMatrix);
//    output();
//    PacmanAgent myPacman;
//    myPacman.train(30,40,inputMatrix);
//    freopen("trainedParameters.txt","a",stdout);
//    cout<<myPacman.level3_a<<endl;
//    fclose(stdout);
    return 0;
}
