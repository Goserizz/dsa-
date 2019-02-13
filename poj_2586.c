#include <stdio.h>

int main()
{
    int s, d, i, temp;
    while (scanf ("%d%d", &s, &d) == 2){
        for (i = 1; i < 5; i ++)
            if (i * s > (5 - i) * d)
                break;
        switch (i){
            case 1:
                printf ("Deficit\n");
                break;

            case 2:
                temp = 3 * s - 9 * d;
                if (temp > 0)
                    printf ("%d\n", temp);
                else
                    printf ("Deficit\n");
                break;

            case 3:
                temp = 6 * s - 6 * d;
                if (temp > 0)
                    printf ("%d\n", temp);
                else
                    printf ("Deficit\n");
                break;

            case 4:
                temp = 8 * s - 4 * d;
                if (temp > 0)
                    printf ("%d\n", temp);
                else
                    printf ("Deficit\n");
                break;

            case 5:
                temp = 10 * s - 2 * d;
                if (temp > 0)
                    printf ("%d\n", temp);
                else
                    printf ("Deficit\n");
                break;
        }
    }
}