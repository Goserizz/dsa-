#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int t, n;
    scanf("%d", &t);
    for(int tc = 0; tc < t; tc ++){
        scanf("%d", &n);
        int **dis = (int **)malloc(n * sizeof(int *));
        for(int i = 0; i < n; i ++){
            dis[i] = (int *)malloc(n *sizeof(int));
            for(int j = 0; j < n; j ++)
                scanf("%d", &dis[i][j]);
        }

        int max = 0;
        char *selected = (char *)malloc(n * sizeof(char));
        int * min_dis = (int *)malloc(n * sizeof(int));
        memset(selected, 0, n * sizeof(char));
        for(int i = 0; i < n; i ++)
            min_dis[i] = dis[0][i];
        selected[0] = 1;
        for(int k = 0; k < n - 1; k ++){
            int min = 0x7fffffff, min_pos = -1;
            for(int i = 0; i < n; i ++){
                if(!selected[i] && min > min_dis[i]){
                    min = min_dis[i];
                    min_pos = i;
                }
            }
            if(min > max)
                max = min;
            selected[min_pos] = 1;
            for(int i = 0; i < n; i ++)
                if(dis[min_pos][i] < min_dis[i])
                    min_dis[i] = dis[min_pos][i];
        }
        printf("%d\n", max);
    }
}
