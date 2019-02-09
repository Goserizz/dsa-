#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char c, ans = 0, change[4][4];
    int i, j;
    memset (change, 0, sizeof (char) * 16);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j ++) {
            while (scanf("%c", &c)) {
                if (c != 10)
                    break;
            }
            if (c == '+'){
                change[i][0] ++;
                change[i][1] ++;
                change[i][2] ++;
                change[i][3] ++;
                change[0][j] ++;
                change[1][j] ++;
                change[2][j] ++;
                change[3][j] ++;
                change[i][j] --;
            }
        }
    }

    for (i = 0; i < 4; i ++)
        for (j = 0; j < 4; j ++)
            if (change[i][j] % 2 == 1)
                ans ++;

    printf ("%d\n", ans);

    for (i = 0; i < 4; i ++)
        for (j = 0; j < 4; j ++)
            if (change[i][j] % 2 == 1)
                printf ("%d %d\n", i + 1, j + 1);
}
