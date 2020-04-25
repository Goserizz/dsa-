#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

bool **line;
bool *used;
int *result;
int x_num, y_num;

class interest{
public:
    int x, y;
    int next_num;
    
    interest(int x, int y){
        this->x = x;
        this->y = y;
        next_num = 0;
    }
};

int find_order(vector<interest> &v, int x, int y){
    for(int i = 0; i < v.size(); i ++){
        if(x == v[i].x && y == v[i].y){
            return i;
        }
    }
    return -1;
}

bool found(int x){
    for(int i = 0; i < y_num; i ++){
        if(!used[i] && line[x][i]){
            used[i] = true;
            if(result[i] == -1 || found(result[i])){
                result[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main(){
    int n, h, w;
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        scanf("%d %d\n", &h, &w);
        bool **sweden = new bool* [h];
        for(int j = 0; j < h; j ++){
            sweden[j] = new bool [w];
            memset(sweden[j], 0, w * sizeof(bool));
        }
        char c;
        for(int j = 0; j < h; j ++){
            for(int k = 0; k < w; k ++){
                scanf("%c", &c);
                if(c == '*')
                    sweden[j][k] = true;
            }
            scanf("%c", &c);
        }
        
        vector<interest> x, y;
        bool now = true; // true for x, false for y
        for(int j = 0; j < h + w - 1; j ++){
            for(int k = (j - w > -1 ? j - w + 1 : 0); k < h && k <= j; k ++){
                int l = j - k;
                if(sweden[k][l]){
                    now ? x.push_back(interest(k, l)) : y.push_back(interest(k, l));
                }
            }
            now = !now;
        }
        
        x_num = x.size();
        y_num = y.size();
        line = new bool* [x_num];
        for(int j = 0; j < x_num; j ++){
            line[j] = new bool [y_num];
            memset(line[j], 0, sizeof(bool) * y_num);
        }
        used = new bool [y_num];
        result = new int [y_num];
        for(int j = 0; j < y_num; j ++)
            result[j] = -1;
        
        for(int j = 0; j < x_num; j ++){
            int tx = x[j].x, ty = x[j].y;
            if(tx != h - 1 && sweden[tx + 1][ty]){
                line[j][find_order(y, tx + 1, ty)] = true;
            }
            if(ty != w - 1 && sweden[tx][ty + 1]){
                line[j][find_order(y, tx, ty + 1)] = true;
            }
            if(tx != 0 && sweden[tx - 1][ty]){
                line[j][find_order(y, tx - 1, ty)] = true;
            }
            if(ty != 0 && sweden[tx][ty - 1]){
                line[j][find_order(y, tx, ty - 1)] = true;
            }
        }
        
        for(int j = 0; j < x_num; j ++){
            memset(used, 0, y_num * sizeof(bool));
            found(j);
        }
        
        int ans = 0;
        for(int j = 0; j < y_num; j ++){
            if(result[j] != -1)
                ans ++;
        }
        printf("%d\n", x_num + y_num - ans);
    }
}

/*
-------------test data-------------
8
40 10
**********
**********
**********
**********
**********
**********
**********
**********
**********
**********
**********
**o*******
**oo******
**********
**********
**********
**********
**********
**********
**********
****oo****
**********
**********
**********
**********
**********
*****ooo**
*****o*o**
*****ooo**
**********
**********
**********
**********
**********
**********
**********
**********
**********
**********
**********
7 9
ooo**oooo
**oo*ooo*
o*oo**o**
ooooooooo
*******oo
o*o*oo*oo
*******oo
10 1
*
*
*
o
*
*
*
*
*
*
2 1
o
o
40 10
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*ooooooo*o
o*o***o*o*
*oo*o*oo*o
o*o***o*o*
*o*ooo*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
o*o*o*o*o*
*o*o*o*o*o
37 10
oooooooooo
o**ooooooo
o*oo**oooo
o*****oooo
oo**oooooo
oooooooooo
o**ooooooo
o*o**ooooo
o******ooo
oooooooooo
o***oooooo
o**ooooooo
oooooo***o
o*********
o***ooo**o
oo*oooo**o
oo****oo*o
oooooooooo
oooooooooo
oooooooooo
oooo****oo
ooo**oo**o
oooo****oo
**oooooooo
oooooooooo
oooo*ooooo
oo****oooo
oooo**oooo
oooo*ooo*o
o*****o**o
o*o******o
ooooo*oo*o
o**oo*oo**
oo****oo*o
ooo***oooo
ooo*****oo
oooooooooo
9 10
**********
*oooooooo*
*o******o*
*o*oooo*o*
*o*oooo*o*
*o*oooo*o*
*o******o*
*oooooooo*
**********
2 1
*
*
-----------answer------------
 195
 17
 5
 0
 193
 58
 26
 1
*/
