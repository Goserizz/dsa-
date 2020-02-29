#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_index(char ** currencies, char *name, int n){
    for(int i = 0; i < n; i ++)
        if(!strcmp(currencies[i], name))
            return i;
    return -1;
}
int main(){
    int n, m, num = 0;
    while(1){
        scanf("%d", &n);
        if(n == 0)
            break;
        num ++;
        
        char **currencies = (char **)malloc(n * sizeof(char*));
        for(int i = 0; i < n; i ++){
            currencies[i] = (char *)malloc(20 * sizeof(char));
            scanf("%s", currencies[i]);
        }
        
        double **rates = (double **)malloc(n * sizeof(double*));
        for(int i = 0; i < n; i ++){
            rates[i] = (double *)malloc(n * sizeof(double));
            for(int j = 0; j < n; j ++)
                rates[i][j] = 0;
        }
        
        scanf("%d", &m);
        for(int i = 0; i < m; i ++){
            char c1[20], c2[20];
            double rate;
            scanf("%s %lf %s", c1, &rate, c2);
            rates[find_index(currencies, c1, n)][find_index(currencies, c2, n)] = rate;
        }
        
        for(int k = 0; k < n; k ++)
            for(int i = 0; i < n; i ++)
                for(int j = 0; j < n; j ++)
                    if(i !=k && j !=k && rates[i][j] < rates[i][k] * rates[k][j])
                        rates[i][j] = rates[i][k] * rates[k][j];
        
        char found = 0;
        for(int i = 0; i < n; i ++){
            if(rates[i][i] > 1){
                found = 1;
                break;
            }
        }
        printf("Case %d: ", num);
        printf(found ? "Yes\n" : "No\n");
    }
    
}
