#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
// 회전할 때 내구도가 깎인다.
// 출구에 도착하면 탈출한다.
int N,M,K;
int arr[11][11] = {0,};
struct Person{
    int x;
    int y;
};
vector<Person> v;

pair<int,int> EXIT;

int result = 0;


void move(){
    //상하 먼저
    //한 칸에 여러명 가능

    for(int i =0; i<v.size(); i++){
        if(v[i].x == -1) continue;
        int nx = EXIT.first - v[i].x; //x 차이 구하기
        int ny = EXIT.second - v[i].y; //y 차이 구하기
        int nextX = v[i].x; int nextY = v[i].y; //다음에 갈 곳 세팅

        if(nx!=0) nextX += nx/abs(nx); //x차이 있다면 nextX 세팅
        if(ny!=0) nextY += ny/abs(ny); //y차이 있다면 nextY 세팅

        //y의 차이가 없을 때는 x으로 보내야 하잖아
        //만약 y의 차이가 있으면 x의 차이가 더 작을 때 x로 먼저 보내는 거잖아
        if(ny == 0 && nx != 0 || (nx!=0 && abs(nx) <= abs(ny))){ //만약 x가 더 가깝거나 둘이 똑같다면 x쪽으로
            if(arr[nextX][v[i].y] == 0){ //y는 같고 x의 차이가 있는 곳이 벽이 없다면
                result += abs(nextX-v[i].x);
                v[i].x = nextX; //x를 다음 x로 보내
            }
            else if(arr[v[i].x][nextY] == 0){ //만약 x가 벽이 있다면 y를 확인
                result += abs(nextY-v[i].y);
                v[i].y = nextY;
            }
        }
        else{
            if(arr[v[i].x][nextY] == 0){ //x는 같고 y의 차이가 있는 곳이 벽이 없다면
                result += abs(nextY-v[i].y);
                v[i].y = nextY; //y를 다음 y로 보내
            }
            else if(arr[nextX][v[i].y] == 0){
                result += abs(nextX-v[i].x);
                v[i].x = nextX; //x를 다음 x로 보내
            }
        }
        if(v[i].x == EXIT.first && v[i].y == EXIT.second){
            v[i].x = -1;
        }
    }
//    v.clear();
//    v.assign(temp.begin(), temp.end());
}

void rotate(int x, int y, int d){
    int temp[11][11] = {0,};
    pair<int,int> Parent[11][11];
    pair<int,int> tempExit;
    for(int i = 0; i<d; i++){
        for(int j = 0; j<d; j++){
            if(EXIT.first == d-j+x-1 && EXIT.second == y+i){
                tempExit = {x+i, y+j};
            }
            temp[x+i][y+j] = arr[d-j+x-1][y+i];
//            Parent[x+i][y+j] = {d-j+x-1,y+i};
            Parent[d-j+x-1][y+i] = {x+i, y+j};
        }
    }
    for(int i = 0; i<d; i++) {
        for (int j = 0; j < d; j++) {
            arr[x + i][y + j] = temp[x + i][y + j];
            if (arr[x + i][y + j] > 0) arr[x + i][y + j]--;
        }
    }
    EXIT.first = tempExit.first;
    EXIT.second = tempExit.second;

    for(int i =0; i< v.size(); i++){
        if(v[i].x == -1) continue;
        if(v[i].x >= x && v[i].x < x+d && v[i].y >=y && v[i].y < y+d){
            int tempX = Parent[v[i].x][v[i].y].first;
            int tempY =Parent[v[i].x][v[i].y].second;
            v[i].x = tempX;
            v[i].y = tempY;
        }
    }
}
struct SQUARE{
    int x;int y; int d;
};

bool isTrue(int x, int y, int l){
    if(EXIT.first >=x && EXIT.first <x+l && EXIT.second >=y && EXIT.second < y+l ){
        for(int i =0; i<v.size(); i++){
            if(v[i].x == -1) continue;
            if(v[i].x >=x && v[i].x <x+l &&v[i].y >=y && v[i].y < y+l ){
                return true;
            }
        }
        return false;
    }
    else return false;
}
bool comp(SQUARE a, SQUARE b){
    if(a.d != b.d) return a.d < b.d;
    if(a.x != b.x) return a.x <b.x;
    return a.y < b.y;
}

SQUARE setSquare(){
    vector<SQUARE> temp;
    for(int l =2; l<=N; l++){
        for(int i =0; i<=N-l; i++){
            for(int j =0; j<=N-l; j++){
                if(isTrue(i,j,l)){
                    temp.push_back({i,j,l});
                }
            }
        }
    }
    if(temp.empty()) return {-1,-1,-1};
    sort(temp.begin(), temp.end(),comp);

    return temp[0];
}

void print(){
    for(int i =0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(i == EXIT.first && j==EXIT.second) cout<<setw(5)<<"EXIT"<<" ";
            else{
                bool flag = false;
                for(int q = 0; q<v.size(); q++){
                    if(v[q].x == i && v[q].y == j) {
                        cout<<setw(5)<<"P"<<" ";
                        flag = true;
                    }
                }
                if(!flag) cout<<setw(5)<<arr[i][j]<<" ";
            }

        }
        cout<<endl;
    }
    cout<<endl;
    for(int i =0; i<v.size(); i++){
        cout<<v[i].x<<" "<<v[i].y<<endl;
    }
}

void sol(){
    for(int i =0; i<K; i++){
        move();
    

        SQUARE s = setSquare();
        if(s.x == -1 && s.y==-1 && s.d == -1) return;
        
        rotate(s.x,s.y,s.d);
        
    }
}




int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>N>>M>>K;
    for(int i =0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin>>arr[i][j];
        }
    }
    for(int i =0; i<M; i++){
        int r,c;
        cin>>r>>c;
        v.push_back({r-1, c-1});
    }
    int r,c;
    cin>>r>>c;
    EXIT = {r-1,c-1};

    sol();
    cout<<result<<endl;
    cout<<EXIT.first+1<<" "<<EXIT.second+1;

    return 0;
}
//4 3 8
//0 0 0 0
//9 2 2 0
//0 1 0 1
//0 0 0 1
//1 1
//1 4
//4 1
//4 3
//3 3