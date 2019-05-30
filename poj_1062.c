#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum status {OPEN, CLOSE} stat_t;

typedef struct{
    int to;
    int disc;
}edge_t;

typedef struct{
    int price;
    int class;
    int outdegr;
    edge_t *edges;
    stat_t stat;
}good_t;

int DFS(int now, int high, int low, int m, good_t *goods){
    int ret = 0;
    if(goods[now].class > high){
        if(goods[now].class > low + m){
            return ret;
        }
        else{
            high = goods[now].class;
        }
    }
    else if(goods[now].class < low){
        if(goods[now].class < high - m){
            return ret;
        }
        else{
            low = goods[now].class;
        }
    }

    goods[now].stat = OPEN;
    ret = goods[now].price;
    for(int i = 0; i < goods[now].outdegr; i ++){
        int to = goods[now].edges[i].to;
        if(goods[to].stat == OPEN){
            continue;
        }
        int disc = goods[now].edges[i].disc;

        int temp = DFS(to, high, low, m, goods);
        if(temp != 0 && ret > temp + disc){
            ret = temp + disc;
        }
    }

    goods[now].stat = CLOSE;
    return ret;
}

int main(){
    int m,n;
    scanf("%d%d", &m, &n);
    good_t *goods = (good_t *)malloc((n + 1) * sizeof(good_t));
    for(int i = 1; i <= n; i ++){
        scanf("%d%d%d", &goods[i].price, &goods[i].class, &goods[i].outdegr);
        goods[i].edges = (edge_t *)malloc(goods[i].outdegr * sizeof(edge_t));
        goods[i].stat = CLOSE;

        for(int j = 0; j < goods[i].outdegr; j ++){
            scanf("%d%d", &goods[i].edges[j].to, &goods[i].edges[j].disc);
        }
    }

    goods[1].stat = OPEN;
    printf("%d", DFS(1, goods[1].class, goods[1].class, m, goods));
    return 0;
}
/*
1 4
10000 3 2
2 8000
3 5000
1000 2 1
4 200
3000 2 1
4 200
50 2 0
*/