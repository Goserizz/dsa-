#include <stdio.h>
#include <string.h>
#include <math.h>

char nn[10][10][2] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0,
        0, 0, 2, 0, 4, 0, 6, 0, 8, 0, 0, 1, 2, 1, 4, 1, 6, 1, 8, 1,
        0, 0, 3, 0, 6, 0, 9, 0, 2, 1, 5, 1, 8, 1, 1, 2, 4, 2, 7, 2,
        0, 0, 4, 0, 8, 0, 2, 1, 6, 1, 0, 2, 4, 2, 8, 2, 2, 3, 6, 3,
        0, 0, 5, 0, 0, 1, 5, 1, 0, 2, 5, 2, 0, 3, 5, 3, 0, 4, 5, 4,
        0, 0, 6, 0, 2, 1, 8, 1, 4, 2, 0, 3, 6, 3, 2, 4, 8, 4, 4, 5,
        0, 0, 7, 0, 4, 1, 1, 2, 8, 2, 5, 3, 2, 4, 9, 4, 6, 5, 3, 6,
        0, 0, 8, 0, 6, 1, 4, 2, 2, 3, 0, 4, 8, 4, 6, 5, 4, 6, 2, 7,
        0, 0, 9, 0, 8, 1, 7, 2, 6, 3, 5, 4, 4, 5, 3, 6, 2, 7, 1, 8
};

struct big_num {
    int num[101];
    int top;
};

void print (struct big_num bigNum){
    printf ("top: %d, ", bigNum.top);
    for (int i = bigNum.top - 1; i > -1; i --)
        printf ("%d", bigNum.num[i]);
    printf ("\n");
}

struct big_num big_pow (struct big_num root, int times){
    struct big_num now = root;
    int temp[101];
    int i, j, k;
    for (k = 0; k < times - 1; k ++) {
        memset (temp, 0, 101 * sizeof (int));
        for (i = 0; i < root.top; i++){
            for (j = 0; j < now.top; j ++){
                temp[i + j] += nn[root.num[i]][now.num[j]][0];
                temp[i + j + 1] += nn[root.num[i]][now.num[j]][1];
            }
        }
        for (i = 0; i < root.top + now.top; i ++) {
            temp[i + 1] += temp[i] / 10;
            now.num[i] = temp[i] % 10;
        }
        if (now.num[i - 1] != 0)
            now.top = now.top + root.top;
        else
            now.top = now.top + root.top - 1;
    }
    return now;
}

char comp (struct big_num one, struct big_num two){
    if (one.top > two.top)
        return 1;
    if (one.top < two.top)
        return -1;
    for (int i = one.top - 1; i > -1; i --){
        if (one.num[i] > two.num[i])
            return 1;
        if (one.num[i] < two.num[i])
            return -1;
    }
    return 0;
}

struct big_num bin_search (struct big_num power, long int lo, long int hi, int top, int times){
    struct big_num root;
    long int mi = (lo + hi) >> 1, temp = mi;
    for (int i = 0; i < top; i ++, temp /= 10)
        root.num[i] = temp % 10;
    root.top = top;

    char jud = comp (big_pow (root, times), power);

    if (jud > 0)
        return bin_search (power, lo, mi - 1, top, times);
    if (jud < 0)
        return bin_search (power, mi + 1, hi, top, times);

    return root;
}

int main()
{
    char c, temp[102];
    struct big_num power, root;
    int top = 0, times, i, bit;
    long int lo, hi;
    while (scanf ("%d %s", &times, temp)){
        lo = 1;
        for (i = 0; i < 102; i ++){
            if (temp[i] == '\0')
                break;
        }
        power.top = i;
        for (i = i - 1; i > -1; i --)
            power.num[power.top - i - 1] = temp[i] - 48;
        bit = power.top / times + (power.top % times == 0 ? 0 : 1);

        for (i = 0; i < bit - 1; i ++)
            lo *= 10;
        hi = pow (10, (double)(power.top) / (double)times);
        if (hi > lo * 10 - 1)
            hi = lo * 10 - 1;

        root = bin_search (power, lo, hi, bit, times);
        for (i = bit - 1; i > -1; i --)
            printf ("%d", root.num[i]);
        printf ("\n");
    }
}
