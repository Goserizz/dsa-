//
// Created by lrf on 2019-01-31.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned short change[16] = {
        19, 39, 78, 140,
        305, 626, 1252, 2248,
        4880, 10016, 20032, 35968,
        12544, 29184, 58368, 51200
};

struct flip{
    char* try;
    unsigned short chess;
};

int main(){
    time_t start, stop;
    time (&start);
    FILE *fp = fopen ("answer.c", "w");
    int prev, now, j, top;
    char c, i, k, found;
    struct flip *flips, *temp;

    fprintf (fp, "#include <stdio.h>\n");
    fprintf (fp, "char answer[65536] = {\n");
    for (unsigned short chess = 0; chess != 65535; chess ++) {
        printf ("%d\n", chess);
        found = 0;
        prev = 16;
        now = 120;

        if (chess == 0) {
            fprintf (fp, "    0,\n");
            continue;
        }

        flips = (struct flip*) malloc (16 * sizeof (struct flip));
        for (i = 0; i < 16; i++) {
            flips[i].try = (char *) malloc (sizeof (char));
            flips[i].try[0] = i;
            flips[i].chess = chess ^ change[i];
            if (flips[i].chess == 0 || flips[i].chess == 65535) {
                for (j = 0; j < i + 1; j ++)
                    free (flips[j].try);
                free (flips);
                fprintf (fp, "    1,\n");
                found = 1;
                break;
            }
        }

        if (found == 1)
            continue;

        for (i = 1; i < 16; i++) {
            top = 0;
            temp = (struct flip *) malloc (now * sizeof(struct flip));
            for (j = 0; j < prev; j++) {
                for (k = flips[j].try[i - 1] + 1; k < 16; k++) {
                    temp[top].try = (char *) malloc((i + 1) * sizeof(char));
                    memcpy (temp[top].try, flips[j].try, i);
                    temp[top].try[i] = k;
                    temp[top].chess = flips[j].chess ^ change[k];
                    if (temp[top].chess == 0 || temp[top].chess == 65535) {
                        for (int o = 0; o < top + 1; o ++)
                            free (temp[o].try);
                        free (temp);
                        fprintf(fp, "    %d,\n", i + 1);
                        found = 1;
                        break;
                    }
                    top++;
                }

                if (found == 1)
                    break;
            }

            for (j = 0; j < prev; j ++)
                free(flips[j].try);
            free (flips);

            if (found == 1)
                break;

            flips = temp;
            prev = now;
            now = now * (15 - i) / (i + 2);
        }

        if (found == 1)
            continue;

        fprintf(fp, "    -1,\n");
    }

    fprintf (fp, "    0\n");
    fprintf (fp, "};\n");
    fprintf (fp, "int main() {\n");
    fprintf (fp, "\tchar c, i, a;\n");
    fprintf (fp, "\tunsigned short chess = 0;\n");
    fprintf (fp, "\tfor (i = 0; i < 16; i ++) {\n");
    fprintf (fp, "\t\twhile (scanf (\"%%c\", &c))\n");
    fprintf (fp, "\t\t\tif (c != 10) break;\n");
    fprintf (fp, "\t\tif (c == 'b') chess |= 1 << i;\n");
    fprintf (fp, "\t}\n");
    fprintf (fp, "\ta = answer[chess];\n");
    fprintf (fp, "\tif (a == -1) printf (\"Impossible\");\n");
    fprintf (fp, "\telse printf (\"%%d\", a);\n");
    fprintf (fp, "\treturn 0;\n");
    fprintf (fp, "}");
    fclose (fp);

    time (&stop);
    printf ("Done in %ld", stop - start);
    return 0;
}