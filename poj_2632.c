#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const char rotate_table_l[4][4] = {  // E, S, W, N
    'E', 'N', 'W', 'S',
    'S', 'E', 'N', 'W',
    'W', 'S', 'E', 'N',
    'N', 'W', 'S', 'E'
};

const char rotate_table_r[4][4] = {  // E, S, W, N
    'E', 'S', 'W', 'N',
    'S', 'W', 'N', 'E',
    'W', 'N', 'E', 'S',
    'N', 'E', 'S', 'W'
};

struct robot{
    int x, y;
    char pos;
};

struct table{
    char taken;
    int no;
};

void rotate(struct robot *r, char dir, int times){
    char *query;
    query = (dir == 'L' ? rotate_table_l : rotate_table_r);
    switch(r->pos){
        case 'E':
            r->pos = query[0 * 4 + times % 4];
            break;
        case 'S':
            r->pos = query[1 * 4 + times % 4];
            break;
        case 'W':
            r->pos = query[2 * 4 + times % 4];
            break;
        case 'N':
            r->pos = query[3 * 4 + times % 4];
            break;
    }
}

int main()
{
    int k, a, b, n, m, no, times, endx, endy, x, y;
    char dir, str[2];
    scanf("%d", &k);
    for(int i = 0; i < k; i ++){
        scanf("%d%d%d%d", &a, &b, &n, &m);
        struct table _table[a + 1][b + 1];
        memset(_table, 0, sizeof(struct table) * (a + 1) * (b + 1));
        struct robot robots[n + 1];
        for(int j = 1; j < n + 1; j ++){
            scanf("%d%d%s", &robots[j].x, &robots[j].y, str);
            robots[j].pos = str[0];
            _table[robots[j].x][robots[j].y].taken = 1;
            _table[robots[j].x][robots[j].y].no = j;
        }
        char wrong = 0;
        for(int j = 0; j < m; j ++){
            scanf("%d%s%d", &no, str, &times);
            if(wrong)
                continue;
            switch(str[0]){
                case 'L':
                case 'R':
                    rotate(&robots[no], str[0], times);
                    break;
                case 'F':
                    switch(robots[no].pos){
                        case 'E':
                            endx = robots[no].x + times;
                            x = robots[no].x;
                            y = robots[no].y;
                            for(int i = x + 1; i <= endx; i ++){
                                if(i > a){
                                    printf("Robot %d crashes into the wall\n", no);
                                    wrong = 1;
                                    goto _next;
                                }
                                if(_table[i][y].taken){
                                    printf("Robot %d crashes into robot %d\n", no, _table[i][y].no);
                                    wrong = 1;
                                    goto _next;
                                }
                            }
                            robots[no].x = endx;
                            _table[x][y].taken = 0;
                            _table[endx][y].taken = 1;
                            _table[endx][y].no = no;
                            break;
                        case 'S':
                            endy = robots[no].y - times;
                            x = robots[no].x;
                            y = robots[no].y;
                            for(int i = y - 1; i >= endy; i --){
                                if(i < 1){
                                    printf("Robot %d crashes into the wall\n", no);
                                    wrong = 1;
                                    goto _next;
                                }
                                if(_table[x][i].taken){
                                    printf("Robot %d crashes into robot %d\n", no, _table[x][i].no);
                                    wrong = 1;
                                    goto _next;
                                }
                            }
                            robots[no].y = endy;
                            _table[x][y].taken = 0;
                            _table[x][endy].taken = 1;
                            _table[x][endy].no = no;
                            break;
                        case 'W':
                            endx = robots[no].x - times;
                            x = robots[no].x;
                            y = robots[no].y;
                            for(int i = x - 1; i >= endx; i --){
                                if(i < 1){
                                    printf("Robot %d crashes into the wall\n", no);
                                    wrong = 1;
                                    goto _next;
                                }
                                if(_table[i][y].taken){
                                    printf("Robot %d crashes into robot %d\n", no, _table[i][y].no);
                                    wrong = 1;
                                    goto _next;
                                }
                            }
                            robots[no].x = endx;
                            _table[x][y].taken = 0;
                            _table[endx][y].taken = 1;
                            _table[endx][y].no = no;
                            break;
                        case 'N':
                            endy = robots[no].y + times;
                            x = robots[no].x;
                            y = robots[no].y;
                            for(int i = y + 1; i <= endy; i ++){
                                if(i > b){
                                    printf("Robot %d crashes into the wall\n", no);
                                    wrong = 1;
                                    goto _next;
                                }
                                if(_table[x][i].taken){
                                    printf("Robot %d crashes into robot %d\n", no, _table[x][i].no);
                                    wrong = 1;
                                    goto _next;
                                }
                            }
                            robots[no].y = endy;
                            _table[x][y].taken = 0;
                            _table[x][endy].taken = 1;
                            _table[x][endy].no = no;
                            break;
                    }
                    break;
            }
            _next:
            ;
        }
        if(!wrong)
            printf("OK\n");
    }
    return 0;
}