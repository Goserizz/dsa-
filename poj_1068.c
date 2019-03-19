#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int t, n;
    int *p, *w;
    scanf("%d", &t);
    for(int i = 0; i < t; i ++){
        scanf("%d", &n);
        p = (int *)malloc(n * sizeof(int));
        w = (int *)malloc(n * sizeof(int));
        memset(w, 0, n * sizeof(int));
        scanf("%d", &p[0]);
        w[0] = 1;
        for(int j = 1; j < n; j ++){
            scanf("%d", &p[j]);
            int k = j - 1;
            while(1){
                if(w[j] + p[k] == p[j]){
                    w[j] += w[k];
                    k -= w[k];
                }
                else{
                    w[j] ++;
                    break;
                }
                if (k == -1){
                    w[j] ++;
                    break;
                }
            }
        }
        for(int j = 0; j < n; j ++)
            printf("%d ", w[j]);
        printf("\n");
    }
    return 0;
}