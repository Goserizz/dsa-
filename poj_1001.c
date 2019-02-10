#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    printf("\n");
    char r[7];
    int n;
    int *exp, *temp = NULL, *result;
    int i, j = 0, k, dot, mul;
    exp = (int*) malloc (5 * sizeof(int));
    result = (int*) malloc (5 * sizeof(int));
    
    while (scanf ("%s%d", r, &n) == 2){
        for (i = 5, j = 0; i > -1; i --)
            if (r[i] != '.')
                exp[j ++] = r[i] - 48;
            else
                dot = 5 - i;
        
        memcpy (result, exp, 5 * sizeof (int));
        
        for (k = 2; k < n + 1; k ++){
            temp = (int*) malloc (5 * k * sizeof (int));
            memset (temp, 0, 5 * k * sizeof (int));
            for (i = 0; i < 5; i ++){
                j = 0;
                for (j = 0; j < 5 * k - 5; j ++){
                    mul = exp[i] * result[j];
                    temp[j + i] += mul % 10;
                    temp[j + i + 1] += mul / 10;
                    // printf ("%d: %d\n", j + i, temp[j + i]);
                }
            }
            free (result);
            result = temp;
        }
        
        for (i = 0; i < 5 * n; i ++){
            result[i + 1]  += result[i] / 10;
            result[i] %= 10;
        }
        
        i = 5 * n - 1;
        while (result[i] == 0 && i > dot * n - 1)
            i --;
        j = 0;
        while (result[j] == 0)
            j ++;
        for (; i > dot * n - 1; i --)
            printf ("%d", result[i]);
        if (j <= i){
            printf (".");
            for (; i >= j; i --)
                printf ("%d", result[i]);
        }
        printf ("\n");
    }
    return 0;
}
