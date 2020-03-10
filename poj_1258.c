#include <stdio.h>
#include <stdlib.h>

#define INF 0x7fffffff
int main(){
    int N;
    while(scanf("%d", &N) != EOF){
        int fibers[100][100];
        for(int i = 0; i < N; i ++)
            for(int j = 0; j < N; j ++)
                scanf("%d", &fibers[i][j]);
        
        int val[100];
        char selected[100];
        val[0] = 0;
        selected[0] = 1;
        for(int i = 1; i < N; i ++){
            val[i] = fibers[0][i];
            selected[i] = 0;
        }
        
        int answer = 0;
        for(int i = 1; i < N; i ++){
            int min_fiber = INF, min_farmer = -1;
            for(int j = 0; j < N; j ++)
                if(!selected[j] && val[j] < min_fiber){
                    min_fiber = val[j];
                    min_farmer = j;
                }
            answer += min_fiber;
            selected[min_farmer] = 1;
            for(int j = 0; j < N; j ++)
                if(!selected[j] && val[j] > fibers[min_farmer][j])
                    val[j] = fibers[min_farmer][j];
        }
        
        printf("%d\n", answer);
    }
}
