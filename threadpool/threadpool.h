#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct job
{
    void* (*callback_function)(void* arg);
    void* arg;
    struct job *next;
};

struct threadpool
{
    int thread_num;
    struct job *head;
    struct job *tail;
    pthread_t *threads;
    pthread_mutex_t mutex;
    pthread_cond_t queue_not_empty;
    pthread_cond_t queue_empty;
    int queue_cur_num;
    int pool_close;
};

struct threadpool* threadpool_init(int thread_num);

void* thread_function(void* arg);

void threadpool_add_job(struct threadpool *pool, void* (*callback_function)(void* arg), void* arg);

void threadpool_destroy(struct threadpool *pool);
