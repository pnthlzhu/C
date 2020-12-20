#include "threadpool.h"

struct threadpool* threadpool_init(int thread_num)
{
    struct threadpool* pool = NULL;

    pool = (struct threadpool*)malloc(sizeof(struct threadpool));
    if (pool == NULL)
    {
	perror("malloc failed!");
	return NULL;
    }

    pool->thread_num = thread_num;
    pool->queue_cur_num = 0;
    pool->head = NULL;
    pool->tail = NULL;

    if (pthread_mutex_init(&(pool->mutex), NULL))
    {
	perror("pthread_mutex_init failed!");
	return NULL;
    }

    if (pthread_cond_init(&(pool->queue_not_empty), NULL))
    {
	perror("pthread_cond_init failed!");
        return NULL;
    }

    if (pthread_cond_init(&(pool->queue_empty), NULL))
    {
        perror("pthread_cond_init failed!");
        return NULL;
    }

    pool->threads = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);

    if (pool->threads == NULL)
    {
        perror("malloc failed!");
	return NULL;
    }

    pool->pool_close = 0;

    for (int i = 0;i < pool->thread_num;i++)
    {
        pthread_create(&(pool->threads[i]), NULL, thread_function, (void*)pool);
    }

    return pool;
}

void* thread_function(void* arg)
{
    struct threadpool *pool = (struct threadpool *)arg;
    struct job *task = NULL;

    while (1)
    {
        pthread_mutex_lock(&(pool->mutex));

	//fprintf(stderr, "thread id:%d is execute\n", (int)pthread_self());
	while (pool->queue_cur_num == 0 && !pool->pool_close)
	{
	    pthread_cond_wait(&(pool->queue_not_empty), &(pool->mutex));
	}

	if (pool->pool_close)
	{
            pthread_mutex_unlock(&(pool->mutex));
	    pthread_exit(NULL);
	}

	pool->queue_cur_num--;
	task = pool->head;

	if (pool->queue_cur_num == 0)
	{
            pool->head = pool->tail = NULL;
	    pthread_cond_signal(&(pool->queue_empty));
	}
	else
	{
            pool->head = task->next;
	}

	pthread_mutex_unlock(&(pool->mutex));

        fprintf(stderr, "thread id:%d is execute\n", (int)pthread_self());

	(*(task->callback_function))(task->arg);
	free(task);
	task = NULL;
    }
}

void threadpool_add_job(struct threadpool* pool, void* (*callback_function)(void* arg), void* arg)
{
    pthread_mutex_lock(&(pool->mutex));

    if (pool->pool_close)
    {
	pthread_mutex_unlock(&(pool->mutex));
        return;
    }

    struct job *task = (struct job *)malloc(sizeof(struct job));
    if (task == NULL)
    {
        fprintf(stderr, "threadpool_add_job failed!");
	return;
    }

    task->callback_function = callback_function;
    task->arg = arg;
    task->next = NULL;

    if (pool->head == NULL)
    {
	pool->head = pool->tail = task;
	pthread_cond_broadcast(&(pool->queue_not_empty));
    }
    else
    {
        pool->tail->next = task;
	pool->tail = task;
    }

    pool->queue_cur_num++;


    pthread_mutex_unlock(&(pool->mutex));
}

void threadpool_destroy(struct threadpool* pool)
{
    pthread_mutex_lock(&(pool->mutex));

    if (pool->pool_close)
    {
        pthread_mutex_unlock(&(pool->mutex));
	return;
    }

    while (pool->queue_cur_num != 0)
    {
        pthread_cond_wait(&(pool->queue_empty), &(pool->mutex));
    }

    pool->pool_close = 1;
    pthread_mutex_unlock(&(pool->mutex));

    pthread_cond_broadcast(&(pool->queue_not_empty));

    for (int i = 0;i < pool->thread_num;i++)
    {
        pthread_join(pool->threads[i], NULL);
    }

    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->queue_empty));
    pthread_cond_destroy(&(pool->queue_not_empty));

    if (pool->threads != NULL)
    {
	free(pool->threads);
	pool->threads = NULL;
    }

    struct job *task = NULL;
    while (pool->head != NULL)
    {
        task = pool->head;
	pool->head = task->next;
	free(task);
	task = NULL;
    }

    if (pool != NULL)
    {
        free(pool);
	pool = NULL;
    }
}
