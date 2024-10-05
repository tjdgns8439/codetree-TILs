#include <iostream>
#include <vector>

using namespace std;
int N;
int M, H;
int K;
int t = 0;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int NORTH = 0;
int EAST = 1;
int SOUTH = 2;
int WEST = 3;
int p = 0;

//북 동 남 서
//서 북 동 남

vector<pair<int,int>> order;
int curOrder = 0;

struct RUNNER{
    int curI;
    int curJ;
    int dir;
};

pair<int,int> curCatcher;

//그래프
int v[101][101];
vector<RUNNER> runner;

bool isRange(int i, int j){
    return i>=0 && j>=0 && i<N && j<N;
}


bool runPossible(int x1, int y1,int x2, int y2 ){//거리 3인지
    if( abs(x1-x2) + abs(y1-y2) <= 3) return true;
    else return false; // 만약 false라면
}


void run(RUNNER &runnerNum, int dir){
    
    int tempI = runnerNum.curI + dx[dir];
    int tempJ = runnerNum.curJ + dy[dir];

    if(isRange(tempI, tempJ)){
        if(curCatcher.first == tempI && curCatcher.second == tempJ){
            return;
        }
        runnerNum.curI = tempI;
        runnerNum.curJ = tempJ;
    }
    else{
        dir = (dir+2)%4;
        tempI = runnerNum.curI + dx[dir];
        tempJ = runnerNum.curJ + dy[dir];
        runnerNum.dir = dir;
        if(curCatcher.first == tempI && curCatcher.second == tempJ){
            return;
        }
        runnerNum.curI = tempI;
        runnerNum.curJ = tempJ;
    }
}
void runCatcher(int dist, int dir){
    curCatcher.first = curCatcher.first + dx[dir];
    curCatcher.second = curCatcher.second + dy[dir];
}

void point(int t){
    int dir = order[curOrder].second;
    int cnt = 0;
    for(int i =0; i<3; i++){
        int nx = dx[dir]*i + curCatcher.first;
        int ny = dy[dir]*i + curCatcher.second;
        if(v[nx][ny] == 2) continue;
        else {
            for(int j =0; j<runner.size(); j++){
                if(runner[j].curI == nx && runner[j].curJ == ny){
                    runner[j].curI = -1; runner[j].curJ = -1;
                    cnt++;
                }
            }
        }
    }
    p += t*cnt;
}

void print(){
    cout<<curCatcher.first<<" "<<curCatcher.second<<endl;
    for(int i =0; i<runner.size(); i++){
        cout<<runner[i].curI<<" "<<runner[i].curJ<<" "<<runner[i].dir<<endl;
    }
    cout<<endl;
}

void sol(int t){
    // print();
    for(int i =0; i<runner.size(); i++){
        if(runner[i].curI == -1 && runner[i].curJ == -1) continue;
        if(runPossible(runner[i].curI, runner[i].curJ, curCatcher.first, curCatcher.second)){
            run(runner[i], runner[i].dir);
        }
    }
    // print();

    pair<int,int> cur = order[curOrder];
    runCatcher(cur.first, cur.second);

    curOrder++; curOrder = curOrder % order.size();
    point(t);

    // print();
}

void setOrder(){
    int idx = 0;
    for(int i =1; i<N; i++){
        order.push_back({i,idx%4}); idx++;
        order.push_back({i,idx%4}); idx++;
    }
    order.push_back({N-1,0});
    order.push_back({N-1,2});
    idx = 3;
    for(int i=N-1; i>=1; i--){
        order.push_back({i,idx%4}); idx++;
        order.push_back({i,idx%4}); idx++;
    }
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>N>>M>>H>>K;
    for(int i = 0; i<M; i++){
        int x, y, d;
        cin>>x>>y>>d;
        runner.push_back({x-1,y-1,d});
    }
    for(int i =0; i<H; i++){
        int x,y;
        cin>>x>>y;
        v[x-1][y-1] = 2;
    }

    curCatcher = {N/2, N/2};
    setOrder();
    for(int i =1; i<=K; i++){
        sol(i);
    }

    cout<<p;

    return 0;
}