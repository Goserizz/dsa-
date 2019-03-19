#include <stdio.h>
#include <stdlib.h>
struct point{
    int x, y;
};
int main()
{
    int row, column, entry;
    while(1){
        scanf("%d%d%d", &row, &column, &entry);
        if(row == 0)
            break;
        struct point *path = (struct point*)malloc(row * column * sizeof(struct point));
        path[0].x = entry - 1;
        path[0].y = 0;
        int top = 0;
        char **map = (char**)malloc(column * sizeof(char*));
        for(int i = 0; i < column; i ++)
            map[i] = (char*)malloc(row * sizeof(char));
        for(int i = 0; i < row; i ++)
            for(int j = 0; j < column; j ++)
                while(scanf("%c", &map[j][i]))
                    if(map[j][i] != 10)
                        break;
        while(path[top].x < column && path[top].x > -1 && path[top].y < row && path[top].y > -1){
            switch(map[path[top].x][path[top].y]){
                case 'N':
                    top ++;
                    path[top].x = path[top - 1].x;
                    path[top].y = path[top - 1].y - 1;
                    break;
                case 'E':
                    top ++;
                    path[top].x = path[top - 1].x + 1;
                    path[top].y = path[top - 1].y;
                    break;
                case 'S':
                    top ++;
                    path[top].x = path[top - 1].x;
                    path[top].y = path[top - 1].y + 1;
                    break;
                case 'W':
                    top ++;
                    path[top].x = path[top - 1].x - 1;
                    path[top].y = path[top - 1].y;
                    break;
            }
            for(int i = 0; i < top; i ++){
                if(path[i].x == path[top].x && path[i].y == path[top].y){
                    printf("%d step(s) before a loop of %d step(s)\n", i, top - i);
                    goto _next;
                }
            }
        }
        printf("%d step(s) to exit\n", top);
        _next:
            ;
    }
}