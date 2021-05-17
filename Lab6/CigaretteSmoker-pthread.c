/*
CSc332 OS Lab
Instructor: Nikita Acharya
Author: Tenzin Tashi
Lab 6 Cigarette Smokers
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock_m;
pthread_mutex_t agent_m;
pthread_mutex_t smoker_tobacco_c;
pthread_mutex_t smoker_match_c;
pthread_mutex_t smoker_paper_c;


void * agent(void * arg){
    int N = 10;
    for(int i = 0;i < N;i++) {

        int randNum = rand() % 3;
        if(randNum == 0)
        {
            printf("Put tobacco and paper on the table. \n");
            pthread_mutex_unlock(&smoker_match_c);// Wake up the smoker with match
        }
        else if(randNum == 1)
        {
            printf("Put tobacco and match on the table. \n");
            pthread_mutex_unlock(&smoker_paper_c);// Wake up the smoker with paper
        }
        else 
        {
            printf("Put match and paper on the table. \n");
            pthread_mutex_unlock(&smoker_tobacco_c); // Wake up the smoker with tobacco
        }
        sleep(1);
        pthread_mutex_lock(&agent_m); // Agent sleeps
    }
    exit(1);
    
}


void * smoker_tobacco(void * arg){
    while(1) {
        pthread_mutex_lock(&smoker_tobacco_c);
        pthread_mutex_lock(&lock_m);
        printf("Smoker_1 with tobacco: picks up the match and paper. \n");
        printf("Smoker_1 smokes.\n");
        sleep(1);
        pthread_mutex_unlock(&agent_m);
        pthread_mutex_unlock(&lock_m);
    }
}

void * smoker_paper(void * arg){
    while(1) {
        pthread_mutex_lock(&smoker_paper_c);
        pthread_mutex_lock(&lock_m);
        printf("Smoker_2 with paper: picks up the match and tobacco. \n");
        printf("Smoker_2 smokes.\n");
        sleep(1);
        pthread_mutex_unlock(&agent_m);
        pthread_mutex_unlock(&lock_m);
    }
}

void * smoker_match(void * arg){
    while(1) {
        pthread_mutex_lock(&smoker_match_c);
        pthread_mutex_lock(&lock_m);
        printf("Smoker_3 with matches: picks up the paper and tobacco. \n");
        printf("Smoker_3 smokes.\n");
        sleep(1);
        pthread_mutex_unlock(&agent_m);
        pthread_mutex_unlock(&lock_m);
    }
}

int main(int argc, char *argv[])
{
    pthread_t agent_t, smoker_tobacco_t, smoker_paper_t, smoker_match_t;
    
    if (pthread_create(&agent_t,NULL,agent,NULL) != 0) {
        fprintf (stderr, "Error creating thread\n");
        exit (1);
    }
    
    if (pthread_create(&smoker_tobacco_t,NULL,smoker_tobacco,NULL) != 0) {
        fprintf (stderr, "Error creating  thread\n");
        exit (1);
    }
    
    if (pthread_create(&smoker_paper_t,NULL,smoker_paper,NULL) != 0) {
        fprintf (stderr, "Error creating thread\n");
        exit (1);
    }
    
    if (pthread_create(&smoker_match_t,NULL,smoker_match,NULL) != 0) {
        fprintf (stderr, "Error creating thread\n");
        exit (1);
    }
    
    pthread_mutex_init(&lock_m, NULL);
    pthread_mutex_init(&agent_m, NULL);
    pthread_mutex_init(&smoker_tobacco_c, NULL);
    pthread_mutex_init(&smoker_match_c, NULL);
    pthread_mutex_init(&smoker_paper_c, NULL);

    pthread_mutex_lock(&smoker_tobacco_c);
    pthread_mutex_lock(&smoker_match_c);
    pthread_mutex_lock(&smoker_paper_c);
    pthread_mutex_lock(&agent_m);

    pthread_join(agent_t, NULL);

    pthread_kill(smoker_tobacco_t, SIGTERM);
    pthread_kill(smoker_match_t, SIGTERM);
    pthread_kill(smoker_paper_t, SIGTERM);

}