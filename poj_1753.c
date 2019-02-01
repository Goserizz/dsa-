//
//  poj_1753.c
//  Data Structure & Algorithm
//
//  Created by lrf on 2019/1/31.
//  Copyright © 2019 lrf. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short change[16] = {
        19, 39, 78, 140,
        305, 626, 1252, 2248,
        4880, 10016, 20032, 35968,
        12544, 29184, 58368, 51200
};

struct flip{
    char* try;
    short chess;
};

int main(){
    int prev = 16, now = 120, j, top;
    char c, i, k;
    short chess = 0;
    struct flip *flips = (struct flip *) malloc (16 * sizeof (struct flip));
    struct flip *temp;

    for (i = 0; i < 16; i ++) {
        while (scanf("%c", &c))
            if (c != 10)
                break;
        if (c == 'b')
            chess |= 1 << i;
    }

    if (chess == 0 || chess == -1){
        printf("0\n");
        return 0;
    }

    for (i = 0; i < 16; i ++) {
        flips[i].try = (char*) malloc (sizeof(char));
        flips[i].try[0] = i;
        flips[i].chess = chess ^ change[i];
        if (flips[i].chess == 0 || flips[i].chess == -1){
            printf("1\n");
            return 0;
        }
    }

    for (i = 1; i < 6; i ++) {
        top = 0;
        temp = (struct flip*) malloc (now * sizeof (struct flip));
        for (j = 0; j < prev; j++) {
            for (k = flips[j].try[i - 1] + 1; k < 16; k ++) {
                temp[top].try = (char*) malloc ((i + 1) * sizeof (char));
                memcpy (temp[top].try, flips[j].try, i);
                temp[top].try[i] = k;
                temp[top].chess = flips[j].chess ^ change[k];
                if (temp[top].chess == 0 || temp[top].chess == -1){
                    printf ("%d\n", i + 1);
                    return 0;
                }
                top ++;
            }
        }

        prev = now;
        now = now * (15 - i) / (i + 2);

        free (flips);
        flips = temp;
    }

    printf ("Impossible\n");
    return 0;
}
