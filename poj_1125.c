#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 0x7fffffff

typedef struct{
    int heard_time;
    int contact_num;
    int *contact;
    int *contact_time;
} broker;

int main(){
    int broker_num;
    while(1){
        scanf("%d", &broker_num);
        if(broker_num == 0){
            break;
        }
        broker **brokers = (broker **)malloc(sizeof(broker *) * (broker_num + 1));
        for(int i = 1; i <= broker_num; i ++){
            brokers[i] = (broker *)malloc(sizeof(broker));
        }
        
        for(int i = 1; i <= broker_num; i ++){
            scanf("%d", &brokers[i]->contact_num);
            brokers[i]->contact = (int *)malloc(sizeof(int) * brokers[i]->contact_num);
            brokers[i]->contact_time = (int *)malloc(sizeof(int) * brokers[i]->contact_num);
            for(int j = 0; j < brokers[i]->contact_num; j ++){
                scanf("%d%d", &brokers[i]->contact[j], &brokers[i]->contact_time[j]);
            }
        }
        
        int best_broker=0, best_time=INF;
        for(int i = 1; i <= broker_num; i ++){
            for(int j = 1; j <= broker_num; j ++){
                brokers[j]->heard_time = INF;
            }
            brokers[i]->heard_time = 0;
            int *heard = (int *)malloc(sizeof(int) * (broker_num + 1));
            memset(heard, 0, sizeof(int) * (broker_num + 1));
            heard[i] = 1;
            
            int now = i;
            for(int k = 0; k < broker_num - 1; k ++){
                if(brokers[now]->heard_time == INF){
                    break;
                }
                for(int j = 0; j < brokers[now]->contact_num; j ++){
                    int contact = brokers[now]->contact[j];
                    int contact_time = brokers[now]->contact_time[j];
                    if(brokers[now]->heard_time + contact_time < brokers[contact]->heard_time && !heard[contact]){
                        brokers[contact]->heard_time = brokers[now]->heard_time + contact_time;
                    }
                }
                
                brokers[now]->heard_time = INF;
                heard[now] = 1;
                
                for(int j = 1; j <= broker_num; j ++){
                    if(brokers[j]->heard_time < brokers[now]->heard_time){
                        now = j;
                    }
                }
            }
            int max_time = INF;
            for(int j = 1; j <= broker_num; j ++){
                if(brokers[j]->heard_time != INF){
                    max_time = brokers[j]->heard_time;
                }
            }
            
            if(max_time < best_time){
                best_time = max_time;
                best_broker = i;
            }
        }
        if(best_time == INF){
            printf("disjoint\n");
        }
        else{
            printf("%d %d\n", best_broker, best_time);
        }
    }
}
