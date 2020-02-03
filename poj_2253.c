#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define square(x) (x)*(x)

int main(){
    int scenario = 1;
    while(1){
        int stone_num;
        scanf("%d", &stone_num);
        if(stone_num == 0){
            break;
        }
        
        int *stonex, *stoney;
        stonex = (int *)malloc(sizeof(int) * stone_num);
        stoney = (int *)malloc(sizeof(int) * stone_num);
        scanf("%d%d", &stonex[0], &stoney[0]);
        scanf("%d%d", &stonex[stone_num-1], &stoney[stone_num-1]);
        for(int i = 1; i < stone_num-1; i ++)
            scanf("%d%d", &stonex[i], &stoney[i]);
        
        int **dist = (int **)malloc(sizeof(int *) * stone_num);
        for(int i = 0; i < stone_num; i ++)
            dist[i] = (int *)malloc(sizeof(int) * stone_num);
        for(int i = 0; i < stone_num; i ++)
            for(int j = i; j < stone_num; j ++)
                dist[i][j] = dist[j][i] = square(stonex[i] - stonex[j]) + square(stoney[i] - stoney[j]);
        
        for(int k = 0; k < stone_num; k ++)
            for(int i = 0; i < stone_num; i ++)
                for(int j = i + 1; j < stone_num; j ++)
                    if(dist[k][i] < dist[i][j] && dist[k][j] < dist[i][j])
                        dist[i][j] = dist[j][i] = (dist[k][i] > dist[k][j] ? dist[k][i] : dist[k][j]);
        
        
        printf("Scenario #%d\nFrog Distance = %.3f\n\n", scenario, sqrt((double)(dist[0][stone_num-1])));
        scenario ++;
    }
}
