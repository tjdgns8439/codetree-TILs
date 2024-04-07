#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int n,m,k;
struct Atom{
    int mg,dir,s,x,y;
};

vector<Atom> arr[50][50];
int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,1,1,1,0,-1,-1,-1};

vector<Atom> temp[50][50];
void atomMove(Atom atom){
    int dir = atom.dir;
    int nx = atom.x;
    int ny = atom.y;
    for(int i =0; i<atom.s; i++){
        nx = (dx[dir] + nx + n)%n;
        ny = (dy[dir] + ny + n)%n;
    }
    temp[nx][ny].push_back(atom);
}

void bomb(int i, int j){
    int dir = arr[i][j][0].dir;
    bool isEqual = true;
    for(int x =1; x<arr[i][j].size(); x++){
        Atom a = arr[i][j][x];
        if(a.dir != dir) {
            isEqual = false;
            break;
        }
    }
    int tempM = 0;
    int tempS = 0;

    for(int x =0; x<arr[i][j].size(); x++){
        tempM += arr[i][j][x].mg;
        tempS += arr[i][j][x].s;
    }
    tempM /= 5;
    tempS /= arr[i][j].size();
    arr[i][j].clear();
    if(tempM != 0){
        if(isEqual){
            //짝수
            for(int idx =0; idx<8; idx++){
                if(idx % 2 != 0) continue;
                Atom atom{};
                atom.dir = idx;
                atom.s = tempS;
                atom.mg = tempM;
                atom.x = i;
                atom.y = j;
                arr[i][j].push_back(atom);
            }
        }
        else{
            //홀수
            for(int idx =0; idx<8; idx++){
                if(idx % 2 != 1) continue;
                Atom atom{};
                atom.dir = idx;
                atom.s = tempS;
                atom.mg = tempM;
                atom.x = i;
                atom.y = j;
                arr[i][j].push_back(atom);
            }
        }
    }
    else{
        arr[i][j].clear();
    }
}


bool isBomb(){
    bool isEnd = true;
    for(int i =0; i<n; i++){
        for(int j =0 ; j<n; j++){
            if(arr[i][j].size() > 1 ){
                bomb(i, j);
                isEnd = false;
            }
        }
    }
    return isEnd;
}
/*
 * for(int x = 0; x<n; x++){
        for(int y = 0; y<n; y++){
            cout<<arr[x][y].size()<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
 */
void move(){

    for(int i =0; i<n; i++){
        for(int j =0 ; j<n; j++){
            for(int a = 0; a < arr[i][j].size();a++){
                Atom atom = arr[i][j][a];
                atomMove(atom);
            }
            arr[i][j].clear();
        }
    }

    for(int i =0; i<n; i++){
        for(int j =0 ; j<n; j++){
            for(int a = 0; a < temp[i][j].size();a++){
                Atom atom = temp[i][j][a];
                arr[i][j].push_back(atom);
            }
            temp[i][j].clear();
        }
    }

    isBomb();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n>>m>>k;
    for(int i =0; i<m; i++){
        int x, y, mg, s, d;
        cin>>x>>y>>mg>>s>>d;
        Atom atom{};
        atom.mg = mg;
        atom.dir = d;
        atom.x = x-1;
        atom.y = y-1;
        atom.s = s;
        arr[x-1][y-1].push_back(atom);
    }

    for(int i =0; i<k; i++){
        move();
    }
    int sum = 0;
    for(int i =0; i<n; i++){
        for(int j = 0; j<n; j++){
            for(int t = 0; t<arr[i][j].size(); t++){
                sum += arr[i][j][t].mg;
            }
        }
    }

    cout<<sum;

    return 0;
}
//5 2 8
//5 3 3 3 5
//3 3 10 8 6