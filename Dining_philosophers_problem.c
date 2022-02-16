#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define __MAX_NUM__ 5

pthread_mutex_t locks[__MAX_NUM__];

typedef struct args{
    int id;
    char *nome;
} args;

void *mangia(void *arg){
    int id = ((args *) arg) -> id;
    char *nome = ((args *) arg) -> nome;
    int forks[2];
    int counter = 0;

    forks[0] = id;
    
    if(id == 0){
        forks[1] = __MAX_NUM__ - 1;
    }else{
        forks[1] = id - 1;
    }

    while(1){
        pthread_mutex_lock(&locks[forks[0]]);
        printf("i'm %s and i take the left fork\n", nome);
        pthread_mutex_lock(&locks[forks[1]]);
        printf("i'm %s and i take the right fork\n", nome);
    
        printf("i'm %s and i'm eating\n", nome);
        sleep(1);
        counter++;
        printf("i'm %s and i'm done eating %d times\n", nome, counter);

        pthread_mutex_unlock(&locks[forks[0]]);
        printf("i'm %s and i leave the left fork\n", nome);
        pthread_mutex_unlock(&locks[forks[1]]);
        printf("i'm %s and i leave the right fork\n", nome);
    }

    return NULL;     
}

int main(){
    pthread_t filosofi[__MAX_NUM__];

    args arg0 = {0, "0: alberto"};
    args arg1 = {1, "1: francesco"};
    args arg2 = {2, "2: stefano"};
    args arg3 = {3, "3: gianmarco"};
    args arg4 = {4, "4: steve"};

    pthread_create(&filosofi[0], NULL, mangia, &arg0);
    pthread_create(&filosofi[1], NULL, mangia, &arg1);
    pthread_create(&filosofi[2], NULL, mangia, &arg2);
    pthread_create(&filosofi[3], NULL, mangia, &arg3);
    pthread_create(&filosofi[4], NULL, mangia, &arg4);

    pthread_join(filosofi[0], NULL);
    pthread_join(filosofi[1], NULL);
    pthread_join(filosofi[2], NULL);
    pthread_join(filosofi[3], NULL);
    pthread_join(filosofi[4], NULL);

    return 0;
}
