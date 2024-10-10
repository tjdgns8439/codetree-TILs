#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <set>
#include <unordered_map>

#define endl '\n'
using namespace std;
int Q;
int N, M,P;

struct RABBIT{
    int jumpCnt;
    int d;
    int x;
    int y;
    int pid;
    int point;
};

struct Point{
    int x; int y;
};

set<int> pidList;
vector<RABBIT> scoreRabbit;
unordered_map<int,RABBIT> rabbitList;

int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};

bool comp(RABBIT a, RABBIT b){
    if(a.jumpCnt != b.jumpCnt) return a.jumpCnt < b.jumpCnt;
    if(a.x+a.y != b.x + b.y) return a.x+a.y < b.x + b.y;
    if(a.x != b.x) return a.x < b.x;
    if(a.y != b.y) return a.y < b.y;
    return a.pid < b.pid;
}

bool pointComp(Point a, Point b){
    if(a.x+a.y != b.x+b.y) return a.x+a.y > b.x + b.y;
    if(a.x != b.x) return a.x > b.x;
    if(a.y != b.y) return a.y > b.y;
}
bool isRange(int i,int j){
    return i>=0 && j>=0 && i<N && j<M;
}
int setPoint(int pid){
    RABBIT cur = rabbitList[pid];
    vector<Point> p;
    int modx = cur.d%((N-1)*2);
    int mody = cur.d%((M-1)*2);

    pair<int,int> temp = {cur.x,cur.y}; int dir = 1;
    for(int i =0; i<modx; i++){//위로갈때
        int nx = dx[dir] + temp.first;
        int ny = cur.y;
        if(!isRange(nx,ny)){
            dir = (dir+2)%4;
            temp.first = dx[dir] + temp.first;
        }
        else temp.first = nx;
    }
    p.push_back({temp.first,temp.second});

    temp = {cur.x,cur.y}; dir = 3;
    for(int i =0; i<modx; i++){//아래로갈때
        int nx = dx[dir] + temp.first;
        int ny = cur.y;
        if(!isRange(nx,ny)){
            dir = (dir+2)%4;
            temp.first = dx[dir] + temp.first;
        }
        else temp.first = nx;
    }
    p.push_back({temp.first,temp.second});

    temp = {cur.x,cur.y}; dir = 0;
    for(int i =0; i<mody; i++){//오른쪽
        int nx = cur.x;
        int ny = dy[dir] + temp.second;
        if(!isRange(nx,ny)){
            dir = (dir+2)%4;
            temp.second = dy[dir] + temp.second;
        }
        else temp.second = ny;
    }
    p.push_back({temp.first,temp.second});

    temp = {cur.x,cur.y}; dir = 2;
    for(int i =0; i<mody; i++){//왼쪽
        int nx = cur.x;
        int ny = dy[dir] + temp.second;
        if(!isRange(nx,ny)){
            dir = (dir+2)%4;
            temp.second = dy[dir] + temp.second;
        }
        else temp.second = ny;
    }
    p.push_back({temp.first,temp.second});
    sort(p.begin(), p.end(), pointComp);

    rabbitList[pid].x = p[0].x;
    rabbitList[pid].y = p[0].y;
    return p[0].x + p[0].y;
}

bool scoreComp(RABBIT a, RABBIT b){
    if(a.x+a.y != b.x + b.y) return a.x+a.y > b.x + b.y;
    if(a.x != b.x) return a.x > b.x;
    if(a.y != b.y) return a.y > b.y;
    return a.pid > b.pid;
}

void go(int k, int s){
    for(int i =0; i<k; i++){
        vector<RABBIT> v;
        v.reserve(rabbitList.size());
        for(auto iter: rabbitList){
            v.push_back(iter.second);
        }
        sort(v.begin(), v.end(), comp);

        RABBIT selectedRabbit = v[0];
        rabbitList[selectedRabbit.pid].jumpCnt++;
        pidList.insert(selectedRabbit.pid);
        int score = setPoint(selectedRabbit.pid)+2;
        for(int iter = 1; iter<v.size(); iter++){
            rabbitList[v[iter].pid].point += score;
        }
    }
    for(auto iter : pidList){
        scoreRabbit.push_back(rabbitList[iter]);
    }
    sort(scoreRabbit.begin(), scoreRabbit.end(), scoreComp);
    RABBIT scoreR = scoreRabbit[0];
    rabbitList[scoreR.pid].point += s;

}

void result(){
    int cnt = 0;
    for(auto iter : rabbitList){
        cnt = max(cnt, iter.second.point);
    }
    cout<<cnt;
}
void reset(){
    pidList.clear();
    scoreRabbit.clear();
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>Q;
    for(int turn =0; turn<Q; turn++){
        int q; cin>>q;
        if(q == 100){
            cin>>N>>M>>P;
            for(int r =0; r<P; r++){
                int pid,d;
                cin>>pid>>d;
                rabbitList[pid] = {0,d,0,0,pid,0};
            }
        }
        else if(q == 200){
            int k,s;
            cin>>k>>s;
            go(k,s);
            reset();
        }
        else if(q == 300){
            int pid,l;
            cin>>pid>>l;
            rabbitList[pid].d *= l;
        }
        else if(q == 400){
            result();
        }

    }
    return 0;
}