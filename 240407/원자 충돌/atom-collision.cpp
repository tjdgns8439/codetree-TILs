#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int n,m,k;
struct Atom{
    long long mg,dir,s,x,y;
};
vector<Atom> arr[50][50];
long long dx[8] = {-1,-1,0,1,1,1,0,-1};
long long dy[8] = {0,1,1,1,0,-1,-1,-1};
vector<Atom> temp;
vector<Atom> bombTemp;

void atomMove(Atom atom){
    long long dir = atom.dir;
    long long nx = ((dx[dir]*atom.s + atom.s*n) + atom.x)%n;
    long long ny = ((dy[dir]*atom.s + atom.s*n) + atom.y)%n;
    atom.x = nx;
    atom.y = ny;
    temp.push_back(atom);
}

bool didir[8] = {0,1,0,1,0,1,0,1};
void bomb(long long i, long long j){
    bool dd = didir[arr[i][j][0].dir];
    bool isEqual = true;

    for(long long x =1; x<arr[i][j].size(); x++){
        Atom a = arr[i][j][x];
        if(didir[a.dir] != dd) {
            isEqual = false;
            break;
        }
    }
    long long tempM = 0;
    long long tempS = 0;

    for(long long x =0; x<arr[i][j].size(); x++){
        tempM += arr[i][j][x].mg;
        tempS += arr[i][j][x].s;
    }
    tempM /= 5;
    tempS /= arr[i][j].size();

    if(tempM != 0){
        if(isEqual){
            //짝수
            for(long long idx =0; idx<8; idx++){
                if(idx % 2 == 1) continue;
                Atom atom{};
                atom.dir = idx;
                atom.s = tempS;
                atom.mg = tempM;
                atom.x = i;
                atom.y = j;
                bombTemp.push_back(atom);
            }
        }
        else{
            //홀수
            for(long long idx =0; idx<8; idx++){
                if(idx % 2 == 0) continue;
                Atom atom{};
                atom.dir = idx;
                atom.s = tempS;
                atom.mg = tempM;
                atom.x = i;
                atom.y = j;
                bombTemp.push_back(atom);
            }
        }
    }
}

void isBomb(){
    for(long long i =0; i<n; i++){
        for(long long j =0 ; j<n; j++){
            if(arr[i][j].size() > 1 ){
                bomb(i, j);
                arr[i][j].clear();
            }
        }
    }
    for(auto atom : bombTemp){
        arr[atom.x][atom.y].push_back(atom);
    }
    bombTemp.clear();

    return;
}
/*
4 4 5
1 4 7 1 2
3 3 1 8 5
4 3 6 10 4
4 4 10 7 3
 */
void print(){
    for(int i =0; i<n; i++){
        for(int j =0; j<n; j++){
            cout<<arr[i][j].size()<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void move(){
    for(long long i =0; i<n; i++){
        for(long long j =0 ; j<n; j++){
            for(long long a = 0; a < arr[i][j].size(); a++){
                Atom atom = arr[i][j][a];
                atomMove(atom);
            }
            arr[i][j].clear();
        }
    }

    for(auto atom : temp){
        arr[atom.x][atom.y].push_back(atom);
    }
    temp.clear();
    isBomb();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin>>n>>m>>k;
    for(long long i =0; i<m; i++){
        long long x, y, mg, s, d;
        cin>>x>>y>>mg>>s>>d;
        Atom atom{};
        atom.x = x-1;
        atom.y = y-1;
        atom.mg = mg;
        atom.s = s;
        atom.dir = d;
        arr[atom.x][atom.y].push_back(atom);
    }

    for(long long test =0; test<k; test++){
        move();
//        print();
    }

    long long sum = 0;
    for(long long i =0; i<n; i++){
        for(long long j = 0; j<n; j++){
            for(long long t = 0; t<arr[i][j].size(); t++){
                sum += arr[i][j][t].mg;
            }
        }
    }

    cout<<sum;

    return 0;
}