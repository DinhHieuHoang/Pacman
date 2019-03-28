#include <bits/stdc++.h>

using namespace std;

string training = "../Pacman/trainingFiles/training";
string validating = "../Pacman/validatingFiles/validating";
string txt = ".txt";
int numOfFiles=150;

double probWall = 0.15;
double probFood = 0.5;
double probMonster = 0.1;
const int n = 30;
const int m = 40;

const int WALL_INT = 0;
const int FOOD_INT = 1;
const int PATH_INT = 2;
const int PACMAN_INT = 3;
const int MONSTER_INT = 4;

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

int random(){
    double a = rand()*1.0/RAND_MAX;
    if(a<probWall){
        return WALL_INT;
    }
    else if(a<probMonster+probWall){
        return MONSTER_INT;
    }
    else {
        double b = rand()*1.0/RAND_MAX;
        if(b<probFood){
            return FOOD_INT;
        }
        else{
            return PATH_INT;
        }
    }
}

int main()
{
    cout<<"probFood: "<<endl;
    cin>>probFood;
    srand(time(NULL));
    for(int i=1; i<=numOfFiles; i++){
        stringstream ss;
        ss<<i;
        string index = ss.str();

        string filename = training + index + txt;
        ofstream fout(filename);

        fout<<n<<" "<<m<<endl;


        int x = rand()%n;
        int y = rand()%m;

        for(int r=0; r<n; r++){
            for(int c=0; c<m; c++){
                if(r == x && c == y){
                    fout<<PACMAN_INT<<" ";
                }
                else{
                    int inp = random();
                    fout<<inp<<" ";
                }
            }
            fout<<endl;
        }

        fout.close();
    }
    for(int i=1; i<=numOfFiles; i++){
        stringstream ss;
        ss<<i;
        string index = ss.str();

        string filename = validating + index + txt;
        ofstream fout(filename);

        fout<<n<<" "<<m<<endl;


        int x = rand()%n;
        int y = rand()%m;

        for(int r=0; r<n; r++){
            for(int c=0; c<m; c++){
                if(r == x && c == y){
                    fout<<PACMAN_INT<<" ";
                }
                else{
                    int inp = random();
                    fout<<inp<<" ";
                }
            }
            fout<<endl;
        }

        fout.close();
    }
    return 0;
}
