#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node{
    char kind, val;
    struct node *lc, *rc;
};
void print_tree(struct node *now, int indent){
    if(now->rc != NULL)
        print_tree(now->rc, indent + 1);
    for(int i = 0; i < indent; i ++)
        printf("\t");
    printf("%c\n", now->kind);
    if(now->lc != NULL)
        print_tree(now->lc, indent + 1);
}
char cal_try(char *try, struct node *now){
    switch(now->kind){
        case 'K':
            if(cal_try(try, now->lc) && cal_try(try, now->rc))
                return 1;
            else
                return 0;
        case 'A':
            if(!cal_try(try, now->lc) && !cal_try(try, now->rc))
                return 0;
            else
                return 1;
        case 'N':
            if(cal_try(try, now->lc))
                return 0;
            else
                return 1;
        case 'C':
            if(cal_try(try, now->lc) && !cal_try(try, now->rc))
                return 0;
            else
                return 1;
        case 'E':
            if(cal_try(try, now->lc) == cal_try(try, now->rc))
                return 1;
            else
                return 0;
        default:
            return try[now->kind - 112];
    }
}
int main()
{
    int i, top, used_num, j;
    char str[101], used[5], try[5], ohuo;
    struct node *root = (struct node *)malloc(sizeof(struct node));
    struct node *cursor;
    struct node *stack[100];
    while(scanf("%s", str)){
        cursor = root;
        top = 0;
        used_num = 0;
        memset(used, 0, 5 * sizeof(char));
        memset(try, 0, 5 * sizeof(char));
        if(str[0] == '0')
            break;
        for (i = 0; i < strlen(str); i ++){
            switch(str[i]){
                case 'K':
                case 'A':
                case 'C':
                case 'E':
                    cursor->kind = str[i];
                    cursor->lc = (struct node *)malloc(sizeof(struct node));
                    cursor->rc = (struct node *)malloc(sizeof(struct node));
                    stack[top ++] = cursor->rc;
                    cursor = cursor->lc;
                    break;
                case 'N':
                    cursor->kind = 'N';
                    cursor->lc = (struct node *)malloc(sizeof(struct node));
                    cursor = cursor->lc;
                    break;
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                    used[str[i] - 112] = 1;
                    cursor->kind = str[i];
                    if (top != 0)
                        cursor = stack[-- top];
                    break;
            }
        }
        for(i = 0; i < 5; i ++)
            if(used[i])
                used[used_num ++] = i;
        ohuo = 0;
        for(i = 0; i < 1 << used_num; i ++){
            for(j = 0; j < used_num; j ++)
                try[used[j]] = i >> j & 1;
            if(!cal_try(try, root)){
                ohuo = 1;
                break;
            }
        }
        if(ohuo)
            printf("not\n");
        else
            printf("tautology\n");
    }
    return 0;
}