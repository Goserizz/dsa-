#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    while(1){
        int n;
        char **type, **dis;
        
        scanf("%d", &n);
        if(n == 0)
            break;
        type = (char **)malloc(n * sizeof(char *));
        dis = (char **)malloc(n * sizeof(char *));
        for(int i = 0; i < n; i ++){
            dis[i] = (char *)malloc(n * sizeof(char));
            memset(dis[i], 0, n * sizeof(char));
            type[i] = (char *)malloc(8 * sizeof(char));
            scanf("%s", type[i]);
        }
        
        for(int i = 0; i < n; i ++)
            for(int j = i + 1; j < n; j ++)
                for(int k = 0; k < 7; k ++)
                    if(type[i][k] != type[j][k])
                        dis[i][j] ++;
        
        for(int i = 0; i < n; i ++)
            for(int j = i + 1; j < n; j ++)
                dis[j][i] = dis[i][j];
        
        char *dist = (char *)malloc(n * sizeof(char));  // distance between inside and outside
        char *selected = (char *)malloc(n * sizeof(char));  // 0 for unselected, 1 for selected
        memset(selected, 0, n * sizeof(char));
        
        selected[0] = 1;
        for(int i = 0; i < n; i ++){
            dist[i] = dis[0][i];
        }
        
        int sum = 0;
        for(int i = 0; i < n-1; i ++){
            int min_dis = 8, min_pos = -1;
            for(int j = 0; j < n; j ++){
                if(selected[j])
                    continue;
                if(dist[j] < min_dis){
                    min_dis = dist[j];
                    min_pos = j;
                }
            }
            selected[min_pos] = 1;
            sum += min_dis;
            for(int j = 0; j < n; j ++)
                if(dist[j] > dis[min_pos][j])
                    dist[j] = dis[min_pos][j];
        }
        
        printf("The highest possible quality is 1/%d.\n", sum);
    }
}
