#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <unordered_set>
using namespace std;
int K,M;
int arr[5][5];
queue<int> orderTreasure;

struct TREASURE{
    int value;
    int dir;
    int x;
    int y;
};

void print(){
    for(int i = 0; i<5; i++){
        for(int j = 0; j<5; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}


void rotate90(int x, int y){
    int temp[3][3] = {0,};
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            temp[i][j] = arr[2-j+x][i+y];
        }
    }
    for(int i =0; i<3; i++){
        for(int j =0; j<3; j++){
            arr[x+i][y+j] = temp[i][j];
        }
    }
}
int dx[4]  = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
bool isRange(int i , int j){
    return i>=0 && j>=0 && i<5&& j<5;
}
vector<pair<int,int>> erasePoint;


int findValue(bool erase){
    int cnt = 0;
    bool visited[5][5]={false,};
    queue<pair<int,int>> q;
    for(int i =0; i<5; i++){
        for(int j =0; j<5; j++){
            if(visited[i][j]) continue;
            int temp = 1;
            visited[i][j] = true;
            q.push({i,j});
            while(!q.empty()){
                int fx = q.front().first;
                int fy = q.front().second;
                q.pop();
                for(int d = 0; d<4; d++){
                    int nx = fx + dx[d];
                    int ny = fy + dy[d];
                    if(isRange(nx,ny) && !visited[nx][ny] && arr[i][j] == arr[nx][ny]){
                        q.push({nx,ny});
                        visited[nx][ny] = true;
                        temp++;
                    }
                }
            }
            if(temp >= 3) {
                cnt += temp;
                if(erase) erasePoint.emplace_back(i,j);
            }
        }
    }
    return cnt;
}
bool comp(TREASURE a, TREASURE b){
    if(a.value != b.value) return a.value > b.value;
    if(a.dir != b.dir) return a.dir <  b.dir;
    if(a.y != b.y) return a.y < b.y;
    if(a.x != b.x) return a.x < b.x;
}
void rm(int x, int y){
    bool visited[5][5] = {false,};
    queue<pair<int,int>> tempQ;
    tempQ.push({x,y});
    visited[x][y] = true;
    int cur = arr[x][y];
    arr[x][y] = 0;
    while(!tempQ.empty()){
        int fx = tempQ.front().first;
        int fy = tempQ.front().second;
        tempQ.pop();
        for(int i =0; i< 4; i++){
            int nx = fx + dx[i];
            int ny = fy + dy[i];
            if(isRange(nx,ny) && !visited[nx][ny] && cur == arr[nx][ny]){
                arr[nx][ny] = 0;
                tempQ.push({nx,ny});
            }
        }
    }

}
void realErase(){
    for(int vi = 0; vi < erasePoint.size(); vi++){
        int x = erasePoint[vi].first;
        int y = erasePoint[vi].second;
        rm(x,y);
    }
}

void pushTreasure(){
    for(int j=0; j<5; j++){
        for(int i =4; i>=0; i--){
            if(arr[i][j] == 0){
                arr[i][j] = orderTreasure.front();
                orderTreasure.pop();
            }
        }
    }
}

int result = 0;
void rotate(){
    vector<TREASURE> v;
    for(int x = 0; x<3; x++){
        for(int y = 0; y<3; y++){
            for(int i =1; i<=4; i++) {
                rotate90(x, y);
                if (i == 4) break;
                int value = findValue(false);
                v.push_back({value, i, x, y});
            }
        }
    }
    sort(v.begin(), v.end(), comp);
    if(v.empty()) return;
    TREASURE start = v[0];
    if(v[0].value == 0) return;
    for(int i =0; i<start.dir; i++){
        rotate90(start.x, start.y);
    }
    while(true){
        int value = findValue(true);
        if(value<=0){
            break;
        }
        else{
            realErase();
            erasePoint.clear();
            pushTreasure();
            result+=value;
        }
    }
}


void sol(){
    rotate();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>K>>M;
    for(int i =0; i<5; i++){
        for(int j =0 ; j<5; j++){
            cin>>arr[i][j];
        }
    }
    for(int i =0; i<M; i++){
        int num;
        cin>>num;
        orderTreasure.push(num);
    }
    for(int i =0; i<K; i++){
        sol();
        if(result == 0) break;
        cout<<result<<" ";
        result = 0;
    }

    return 0;
}