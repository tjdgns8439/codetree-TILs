#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>

#define endl '\n'
using namespace std;
int N,M,K;
struct TOP{
    int power;
    int time;
    int x;
    int y;
};
int t = 1;
TOP arr[11][11];
int dx[4]  = {0,1,0,-1};
int dy[4]  = {1,0,-1,0};
int bombDx[8] = {0,1,1,1,0,-1,-1,-1};
int bombDy[8] = {1,-1,0,1,-1,0,1,-1};

pair<int,int> appender;
pair<int,int> target;
bool visited[11][11] = {false,};
vector<pair<int,int>> plusTop;
bool comp(TOP a, TOP b){
    if(a.power != b.power) return a.power < b.power;
    if(a.time != b.time) return a.time > b.time;
    if(a.x+a.y != b.x + b.y) return a.x+a.y > b.x+b.y;
    return a.y > b.y;
}
void setAppenderAndTarget(){
    vector<TOP> v;
    for(int i =0; i<N; i++){
        for(int j =0; j<M; j++){
            if(arr[i][j].power != 0){
                v.push_back(arr[i][j]);
            }
        }
    }
    sort(v.begin(), v.end(), comp);
    //todo: v의 사이즈가 0이라면?
    appender = {v[0].x, v[0].y};
    arr[appender.first][appender.second].power = arr[appender.first][appender.second].power + N + M;
    target = {v[v.size()-1].x, v[v.size()-1].y};
    arr[appender.first][appender.second].time = t;


}
int dist[11][11] = {0,};
pair<int,int> parent[11][11];

void reset(){
    for(int i =0; i<N; i++){
        for(int j = 0; j<M; j++){
            dist[i][j] = 0;
            parent[i][j] = {0,0};
            visited[i][j] = false;
        }
    }
    plusTop.clear();
}

void bfs(){
    queue<pair<int,int>> q;
    q.push({appender.first, appender.second});
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i =0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0) nx += N;
            if(ny < 0) ny += M;
            if(nx == N) nx -= N;
            if(ny == M) ny -= M;
            if(!visited[nx][ny] && arr[nx][ny].power > 0){
                q.push({nx,ny});
                dist[nx][ny] = dist[x][y]+1;
                parent[nx][ny] = {x,y};
                visited[nx][ny] = true;
            }
        }
    }
}
void laser(){
    bool temp[11][11] = {false,};
    pair<int,int> cur = target;
    int minus = arr[appender.first][appender.second].power;
    arr[cur.first][cur.second].power -= minus;

    while(true){
        if(cur.first == appender.first && cur.second == appender.second){
            break;
        }
        else{
            cur = parent[cur.first][cur.second];
            temp[cur.first][cur.second] = true;
            arr[cur.first][cur.second].power -= (minus/2);
        }
    }
    for(int i =0; i<N; i++){
        for(int j = 0; j<M; j++){
            if( i == appender.first && j == appender.second) continue;
            if( i == target.first && j == target.second) continue;
            if( arr[i][j].power <= 0) continue;
            if( temp[i][j] ) continue;
            plusTop.push_back({i,j});
        }
    }
}
void bomb(){
    bool temp[11][11] = {false,};
    int minus = arr[appender.first][appender.second].power;
    for(int d =0; d<8; d++){
        int nx = bombDx[d] + target.first;
        int ny = bombDy[d] + target.second;
        if(nx < 0) nx += N;
        if(ny < 0) ny += M;
        if(nx == N) nx -= N;
        if(ny == M) ny -= M;
        if(nx == appender.first && ny == appender.second){
            continue;
        }
        else {
            temp[nx][ny] = true;
            arr[nx][ny].power -= minus;
        }
    }
    for(int i =0; i<N; i++){
        for(int j = 0; j<M; j++){
            if( i == appender.first && j == appender.second) continue;
            if( i == target.first && j == target.second) continue;
            if( temp[i][j] ) continue;
            if( arr[i][j].power <= 0) continue;
            plusTop.emplace_back(i,j);
        }
    }
}
void append(){
    bfs();

    if(visited[target.first][target.second]){
        laser();
    }
    else bomb();

    for(int i =0; i<plusTop.size(); i++){
        arr[plusTop[i].first][plusTop[i].second].power ++;
    }

    reset();
}

void sol(){
    t++;
    setAppenderAndTarget();
    append();
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>N>>M>>K;
    for(int i =0; i<N; i++){
        for(int j =0; j<M; j++){
            int num;
            cin>>num;
            arr[i][j] = {num,0, i, j};
        }
    }
    while(K--){
        sol();

    }
    int result = 0;
    for(int i =0; i< N; i++){
        for(int j = 0; j<N; j++){
            result = max(result,arr[i][j].power);
        }
    }
    cout<<result;
    return 0;
}