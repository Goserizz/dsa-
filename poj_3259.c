#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int F, N, M, W, j, from, to, time;
    scanf("%d", &F);
    char *ans = (char *)malloc(F * sizeof(char));
    int top = 0;
    for(int i = 0; i < F; i ++){
        scanf("%d%d%d", &N, &M, &W);

        int paths[501][501];
        memset(paths, 0, sizeof(paths));
        int values[500];
        for(j = 1; j <= N; j ++){
            values[j] = 0x7fffffff;
        }

        for(j = 0; j < M; j ++){
            scanf("%d%d%d", &from, &to, &time);
            if(paths[from][to] == 0){
                paths[from][to] = time;
                paths[to][from] = time;
            }
            else{
                if(paths[from][to] > time){
                    paths[from][to] = time;
                }
                if(paths[to][from] > time){
                    paths[to][from] = time;
                }
            }
        }

        for(j = 0; j < W; j ++){
            scanf("%d%d%d", &from, &to, &time);
            if(paths[from][to] == 0){
                paths[from][to] = -time;
            }
            else if(paths[from][to] > -time){
                paths[from][to] = -time;
            }
        }

        values[1] = 0;
        char cont = 1;
        for(j = 0; j < N - 1; j ++){
            if(cont){
                cont = 0;
                for(int x = 1; x <= N; x ++){
                    for(int y = 1; y <= N; y ++){
                        if( values[x] != 0x7fffffff &&
                            paths[x][y] != 0        &&
                            values[y] > values[x] + paths[x][y] ){
                            cont = 1;
                            values[y] = values[x] + paths[x][y];
                        }
                    }
                }
            }
        }

        for(int x = 1; x <= N; x ++){
            for(int y = 1; y <= N; y ++){
                if(paths[x][y] != 0 &&
                   values[x] + paths[x][y] < values[y]){
                       //printf("YES\n");
                       ans[top ++] = 1;
                       goto _next;
                   }
            }
        }
        ans[top ++] = 0;
        _next : ;
    }

    for(int i = 0; i < top; i ++){
        printf(ans[i] ? "YES\n" : "NO\n");
    }
    return 0;
}
/*
2
3 3 1
1 2 2
1 3 4
2 3 1
3 1 3
3 2 1
1 2 3
2 3 4
3 1 8
*/