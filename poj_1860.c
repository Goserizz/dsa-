#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    double  from_rate;
    double  from_comm;
    double  to_rate;
    double  to_comm;
    int     from;
    int     to;
}exch_t;

typedef struct node{
    int         curr_no;
    struct node *next;
}node_t;


typedef struct{
    node_t  *tail;
    node_t  *root;
}quene_t;

int main(){
    int     N, M, S;
    double  V, temp;
    scanf("%d%d%d%lf", &N, &M, &S, &V);

    double *value = (double *)malloc((N + 1) * sizeof(double));
    exch_t *exch = (exch_t *)malloc(M * sizeof(exch_t));

    memset(value, 0, (N + 1) * sizeof(double));

    for(int i = 0; i < M; i ++){
        scanf("%d%d%lf%lf%lf%lf", 
            &exch[i].from, &exch[i].to, 
            &exch[i].from_rate, &exch[i].from_comm, 
            &exch[i].to_rate, &exch[i].to_comm);
    }

    int cont = 1;
    value[S] = V;
    while(cont){
        cont = 0;
        for(int i = 0; i < M; i ++){
            if(value[exch[i].from] != 0){
                temp = (value[exch[i].from] - exch[i].from_comm) * exch[i].from_rate;
                if(temp > value[exch[i].to]){
                    cont = 1;
                    value[exch[i].to] = temp;
                    if(exch[i].to == S){
                        printf("YES\n");
                        return 0;
                    }
                }
            }
            if(value[exch[i].to] != 0){
                temp = (value[exch[i].to] - exch[i].to_comm) * exch[i].to_rate;
                if(temp > value[exch[i].from]){
                    cont = 1;
                    value[exch[i].from] = temp;
                    if(exch[i].from == S){
                        printf("YES\n");
                        return 0;
                    }
                }
            }
        }
    }

    printf("NO\n");
    return 0;
}
/*
45 43 8 32.460000
40 6 90.90 17.59 45.28 89.70
29 18 37.97 55.13 84.48 52.81
45 26 59.25 99.43 27.79 90.84
7 42 57.94 54.76 90.96 64.60
27 12 18.69 31.72 66.78 65.72
31 4 48.09 14.86 56.63 18.38
23 1 96.51 39.40 14.79 23.51
22 25 85.68 78.28 77.54 0.17
18 5 28.25 56.09 2.81 25.39
34 42 91.34 9.29 34.51 99.34
20 32 39.35 63.72 58.26 19.53
36 34 1.79 61.68 23.29 4.84
30 12 70.83 5.46 4.05 31.37
16 37 39.47 57.44 59.00 79.05
16 14 68.12 5.58 35.39 19.28
13 44 27.08 32.10 75.83 47.52
45 37 6.31 81.34 22.96 54.24
24 19 41.55 58.31 93.99 84.14
28 36 73.32 80.70 37.02 33.93
6 21 56.88 6.52 76.14 30.43
18 35 83.55 30.02 41.25 89.11
17 37 70.84 51.14 44.76 29.99
14 2 42.34 26.79 51.95 93.56
40 6 63.46 83.44 82.66 15.09
27 20 34.61 61.69 10.23 35.04
29 13 83.62 38.65 88.51 27.75
30 22 59.09 3.86 63.35 57.85
4 18 11.24 97.52 8.80 11.15
38 42 79.71 33.62 3.36 36.53
38 45 90.65 72.52 18.35 54.58
33 45 16.35 58.44 57.71 88.69
1 43 84.41 35.96 72.06 27.57
13 9 46.36 94.47 81.63 88.19
42 10 41.22 1.63 98.33 85.94
9 3 40.00 49.78 46.31 86.28
11 37 27.72 17.84 56.89 86.23
45 10 99.57 92.25 71.49 1.57
8 14 19.47 82.06 32.79 90.53
23 37 26.54 38.20 99.18 86.79
10 42 98.34 36.13 88.52 98.24
13 30 85.81 43.84 54.64 33.83
31 8 53.55 51.02 46.20 87.65
30 8 92.31 36.44 91.82 23.12
*/