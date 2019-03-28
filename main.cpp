#include <bits/stdc++.h>

using namespace std;

const int TERN_SEARCH_A_NUM = 5000;

int main()
{
    freopen("../Pacman/output.txt","r", stdin);
    freopen("stats.txt", "w", stdout);

    map<int, int> maxPoints;
    map<int, int> mrks;
    map<int, int> points;
    int mrk, maxPoint, point;
    for(int i=0; i<TERN_SEARCH_A_NUM; i++){
        cin>>point>>maxPoint>>mrk;

        if(maxPoints.find(maxPoint)==maxPoints.end()){
            maxPoints[maxPoint]=1;
        }
        else{
            maxPoints[maxPoint]++;
        }

        if(mrks.find(mrk)==mrks.end()){
            mrks[mrk]=1;
        }
        else{
            mrks[mrk]++;
        }
        if(points.find(point)==points.end()){
            points[point]=1;
        }
        else{
            points[point]++;
        }
    }

    cout<<"MAX POINTS:"<<endl;
    for(map<int, int>::iterator i=maxPoints.begin(); i!=maxPoints.end(); ++i){
        cout<<i->first<<": "<<i->second<<endl;
    }

    cout<<"MARKS:"<<endl;
    for(map<int, int>::iterator i=mrks.begin(); i!=mrks.end(); ++i){
        cout<<i->first<<": "<<i->second<<endl;
    }

    cout<<"POINTS:"<<endl;
    double expPoint = 0.0;
    for(map<int, int>::iterator i=points.begin(); i!=points.end(); ++i){
        cout<<i->first<<": "<<i->second<<endl;
        expPoint+=i->first * i->second;
    }

    cout<<"EXPECTED POINT:"<<endl;
    cout<<expPoint/TERN_SEARCH_A_NUM<<endl;

    fclose(stdin);
    fclose(stdout);
    return 0;
}
