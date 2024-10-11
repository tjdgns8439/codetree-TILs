#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <unordered_set>
using namespace std;
int L,N,Q;
struct PERSON{
    int x;
    int y;
    int h;
    int w;
    int k;
};
PERSON personList[31];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int chess[51][51] = {0,};// 체스판 정보
int personMap[51][51] = {0,}; //사람 정보
int firstPersonK[51] = {0,}; //사람 정보
int result = 0;

bool isRange(int i, int j){
    return i>=0 & j>=0 && i<L && j<L && chess[i][j] != 2;
}
int curIdx = 0;
vector<int> v;
void move(int idx, int d){
    if(idx != curIdx) v.push_back(idx);
    PERSON* curPerson = &personList[idx];
    int temp[51][51] = {0,};
    for(int i = curPerson->x; i < curPerson->x + curPerson->h; i++){
        for(int j = curPerson->y; j < curPerson->y + curPerson->w; j++ ){
            int nx = dx[d] + i;
            int ny = dy[d] + j;
            temp[nx][ny] = personMap[i][j];
            personMap[i][j] = 0;
        }
    }
    pair<int,int> start={0,0};
    for(int i = curPerson->x; i < curPerson->x + curPerson->h; i++){
        for(int j = curPerson->y; j < curPerson->y + curPerson->w; j++ ){
            int nx = dx[d] + i;
            int ny = dy[d] + j;
            personMap[nx][ny] = temp[nx][ny];
            if(i == curPerson->x && j == curPerson->y){
                start = {nx,ny};
            }
        }
    }
    curPerson->x = start.first;
    curPerson->y = start.second;
}
bool can_move(int idx, int d){ //내려가면서 마주친 애들 모두
    //상우좌하
    PERSON curPerson = personList[idx];
    //상
    for(int i = curPerson.x; i < curPerson.x + curPerson.h; i++){
        for(int j = curPerson.y; j < curPerson.y + curPerson.w; j++ ){
            int nx = dx[d] + i;
            int ny = dy[d] + j;
            if(!isRange(nx,ny)){
                return false;
            }
            if( personMap[nx][ny] != 0 && personMap[nx][ny] != idx) {
                if(!can_move(personMap[nx][ny], d) ) return false;
            }
        }
    }
    move(idx, d);
    return true;
}

void deletePerson(int idx){
    int cnt =0;
    PERSON* person = &personList[idx];
    for(int x = person->x; x<person->x+person->h; x++){
        for(int y = person->y; y<person->y + person->w; y++){
            if(chess[x][y] == 1) cnt++;
        }
    }
    person->k -= cnt;
    if(person->k < 0){
        person->k = 0;
        for(int x = person->x; x<person->x+person->h; x++){
            for(int y = person->y; y<person->y + person->w; y++){
                personMap[x][y] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>L>>N>>Q;
    for(int i =0; i<L; i++){
        for(int j =0; j<L; j++){
            cin>>chess[i][j];
        }
    }

    for(int i =1; i<=N; i++){
        int r,c,h,w,k;
        cin>>r>>c>>h>>w>>k;
        personList[i] = {r-1,c-1,h,w,k};
        firstPersonK[i] = k;
    }
    //set person map
    for(int i =1; i<=N; i++){
        PERSON person = personList[i];
        for(int x = person.x; x<person.x+person.h; x++){
            for(int y = person.y; y<person.y + person.w; y++){
                personMap[x][y] = i;
            }
        }
    }

    for( int i =0; i<Q; i++){
        int idx,d;
        cin>>idx>>d;
        curIdx = idx;
        if(personList[idx].k <= 0) continue;
        if(!can_move(idx,d)) continue;
        for(int j =0; j<v.size(); j++){
            deletePerson(v[j]);
        }
        v.clear();

    }

    for(int i =1; i<=N; i++){
        if(personList[i].k <= 0 ) continue;
        result = result + firstPersonK[i] - personList[i].k;
    }




    cout<<result;

    return 0;
}