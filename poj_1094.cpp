#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class Node{
public:
    int inbound;
    char letter;
    vector <Node *> gt_nodes;
    
    Node(char letter){
        this->inbound = 0;
        this->letter = letter;
    }
    
    void virtualEraseNode(){
        for(int i = 0; i < gt_nodes.size(); i ++){
            gt_nodes[i]->inbound --;
        }
    }
    
    void recoverInbound(){
        for(int i = 0; i < gt_nodes.size(); i ++){
            gt_nodes[i]->inbound ++;
        }
    }
    
    bool pushBack(Node * node){
        for(int i = 0; i < this->gt_nodes.size(); i ++){
            if(this->gt_nodes[i] == node)
                return false;
        }
        this->gt_nodes.push_back(node);
        return true;
    }
};

void error_print(int n){
    printf("Inconsistency found after %d relations.\n", n + 1);
}

void undetermined_print(){
    printf("Sorted sequence cannot be determined.\n");
}

void detemined_print(int n, string seq){
    printf("Sorted sequence determined after %d relations: %s.\n", n + 1, seq.c_str());
}

int main(){
    int m, n, i;
    while(true){
        scanf("%d %d", &m, &n);
        if(m == 0 && n == 0)
            break;
        
        Node ** nodes = new Node * [m];
        for(i = 0; i < m; i ++){
            nodes[i] = new Node('A' + i);
        }
        
        bool end = false;
        
        for(i = 0; i < n; i ++){
            char x, y;
            scanf("\n%c<%c", &x, &y);
            if(end) continue;
            
            nodes[x - 'A']->pushBack(nodes[y - 'A']);
            
            int now_num, now = -1, zero_num = 0;;
            bool *checked = new bool[m];
            string ans = "";
            memset(checked, 0, sizeof(bool) * m);
            
            for(int k = 0; k < m; k ++)
                nodes[k]->inbound = 0;
            for(int k = 0; k < m; k ++)
                nodes[k]->recoverInbound();
            
            for(int j = 0; j < m; j ++){
                if(nodes[j]->inbound == 0)
                    zero_num ++;
            }
            
            if(zero_num == 0){
                error_print(i);
                end = true;
            }
            else if(zero_num > 1){
                for(int j = 0; j < m; j ++){
                    now_num = 0;
                    for(int k = 0; k < m; k ++){
                        if(checked[k])
                            continue;
                        if(nodes[k]->inbound == 0){
                            now_num ++;
                            now = k;
                        }
                    }
                    if(now_num == 0){
                        error_print(i);
                        end = true;
                        break;
                    }
                    else{
                        checked[now] = true;
                        nodes[now]->virtualEraseNode();
                    }
                }
                if(!end && i == n - 1){
                    undetermined_print();
                }
            }
            else{
                for(int j = 0; j < m; j ++){
                    /*
                    for(int k = 0; k < m; k ++)
                        printf("%d ", nodes[k]->inbound);
                    printf("\n");
                     */
                    now_num = 0;
                    for(int k = 0; k < m; k ++){
                        if(checked[k]){
                            continue;
                        }
                        if(nodes[k]->inbound == 0){
                            now_num ++;
                            now = k;
                        }
                    }
                    if(now_num == 1){
                        ans += nodes[now]->letter;
                        if(j == m - 1){
                            detemined_print(i, ans);
                            end = true;
                            break;
                        }
                        else{
                            checked[now] = true;
                            nodes[now]->virtualEraseNode();
                        }
                    }
                    else if(now_num == 0){
                        error_print(i);
                        end = true;
                        break;
                    }
                    else if(i == n - 1){
                        undetermined_print();
                        end = true;
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
}

/*
 Sorted sequence determined after 6 relations: DCAB.
 Sorted sequence determined after 29 relations: CFDAEBHGJI.
 Sorted sequence cannot be determined.
 Inconsistency found after 48 relations.
 Sorted sequence determined after 318 relations: GMNVKCHFOBRJDZLPXAYSEIWQTU. x
 Sorted sequence determined after 25 relations: ABCDEFGHIJKLMNOPQRSTUVWXYZ.
 Sorted sequence determined after 7 relations: BADCE.
 Sorted sequence determined after 158 relations: HNAMGIPCTBJFRLEODKSQ.
 Inconsistency found after 35 relations.
 Sorted sequence cannot be determined.
 Sorted sequence determined after 7 relations: ABDEC.
 Sorted sequence cannot be determined.
 Sorted sequence determined after 11 relations: ACDBFE.
 Sorted sequence cannot be determined.
 Sorted sequence cannot be determined.
 Sorted sequence determined after 179 relations: CHQNAMDLRFPGISBJOKET.

 */
