#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t locks[5];

typedef struct args{
    int id;
    char *name;
} args;

void *eat(void *arg){
    int id = ((args *) arg) -> id;
    char *name = ((args *) arg) -> name;
    int forks[2];
    int counter = 0;

    forks[0] = id;
    
    if(id == 0){
        forks[1] = 5 - 1;
    }else{
        forks[1] = id - 1;
    }

    while(1){
        pthread_mutex_lock(&locks[forks[0]]);
        printf("i'm %s and i take the left fork\n", name);
        pthread_mutex_lock(&locks[forks[1]]);
        printf("i'm %s and i take the right fork\n", name);
    
        printf("i'm %s and i'm eating\n", name);
        sleep(1);
        counter++;
        printf("i'm %s and i'm done eating %d times\n", name, counter);

        pthread_mutex_unlock(&locks[forks[0]]);
        printf("i'm %s and i leave the left fork\n", name);
        pthread_mutex_unlock(&locks[forks[1]]);
        printf("i'm %s and i leave the right fork\n", name);
    }

    return NULL;     
}

int main(){
    pthread_t philosophers[5];

    args arg0 = {0, "0: alberto"};
    args arg1 = {1, "1: francesco"};
    args arg2 = {2, "2: stefano"};
    args arg3 = {3, "3: gianmarco"};
    args arg4 = {4, "4: steve"};

    pthread_create(&philosophers[0], NULL, eat, &arg0);
    pthread_create(&philosophers[1], NULL, eat, &arg1);
    pthread_create(&philosophers[2], NULL, eat, &arg2);
    pthread_create(&philosophers[3], NULL, eat, &arg3);
    pthread_create(&philosophers[4], NULL, eat, &arg4);

    pthread_join(philosophers[0], NULL);
    pthread_join(philosophers[1], NULL);
    pthread_join(philosophers[2], NULL);
    pthread_join(philosophers[3], NULL);
    pthread_join(philosophers[4], NULL);

    return 0;
}
