#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct zone{
    double left;
    double right;
};

void quick_sort (struct zone *zones, int left, int right){
    if (left >= right)
        return;
    int lo = left, hi = right;
    struct zone pivot = zones[lo];
    while (lo < hi) {
        while (zones[hi].left >= pivot.left && lo < hi)
            hi--;
        zones[lo] = zones[hi];
        while (zones[lo].left <= pivot.left && lo < hi)
            lo++;
        zones[hi] = zones[lo];
    }
    zones[lo] = pivot;
    quick_sort (zones, left, lo - 1);
    quick_sort (zones, lo + 1, right);
}

int main()
{
    int n, d, i, j, Case = 1, ans;
    double x, y, len, right;
    struct zone *zones;
    char found;
    while (1){
        ans = 0;
        found = 1;
        scanf ("%d%d", &n, &d);
        if (n == 0 && d == 0)
            break;
        zones = (struct zone*) malloc (n * sizeof (struct zone));

        for (i = 0; i < n; i ++){
            scanf ("%lf%lf", &x, &y);
            if (found == 0)
                continue;
            if (y > d || y < 0){
                found = 0;
                continue;
            }
            len = sqrt ((double)(d * d) - y * y);
            zones[i].left = x - len;
            zones[i].right = x + len;
        }

        if (found) {
            quick_sort(zones, 0, n - 1);
            i = 0;
            while (i < n){
                right = zones[i].right;
                for (j = i + 1; j < n; j++) {
                    if (zones[j].left > right)
                        break;
                    if (zones[j].right < right)
                        right = zones[j].right;
                }
                ans++;
                i = j;
            }
            printf("Case %d: %d\n", Case, ans);
        }
        else
            printf("Case %d: -1\n", Case);
        Case ++;

        free (zones);
    }

    return 0;
}