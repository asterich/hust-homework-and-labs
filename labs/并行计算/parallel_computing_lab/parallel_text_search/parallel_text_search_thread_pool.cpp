#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stddef.h>

#include <chrono>

#define MAX_LINE_LENGTH 256
#define MAX_THREADS 8
#define QUEUE_SIZE 1024

struct tpool;
typedef struct tpool tpool_t;

typedef void (*thread_func_t)(void *arg);

tpool_t *tpool_create(size_t num);
void tpool_destroy(tpool_t *tm);

bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg);
void tpool_wait(tpool_t *tm);

struct tpool_work {
    thread_func_t      func;
    void              *arg;
    struct tpool_work *next;
};
typedef struct tpool_work tpool_work_t;

struct tpool {
    tpool_work_t    *work_first;
    tpool_work_t    *work_last;
    pthread_mutex_t  work_mutex;
    pthread_cond_t   work_cond;
    pthread_cond_t   working_cond;
    size_t           working_cnt;
    size_t           thread_cnt;
    bool             stop;
};

static tpool_work_t *tpool_work_create(thread_func_t func, void *arg)
{
    tpool_work_t *work;

    if (func == NULL)
        return NULL;

    work       = (tpool_work_t *)malloc(sizeof(*work));
    work->func = func;
    work->arg  = arg;
    work->next = NULL;
    return work;
}

static void tpool_work_destroy(tpool_work_t *work)
{
    if (work == NULL)
        return;
    free(work);
}


static tpool_work_t *tpool_work_get(tpool_t *tm)
{
    tpool_work_t *work;

    if (tm == NULL)
        return NULL;

    work = tm->work_first;
    if (work == NULL)
        return NULL;

    if (work->next == NULL) {
        tm->work_first = NULL;
        tm->work_last  = NULL;
    } else {
        tm->work_first = work->next;
    }

    return work;
}

static void *tpool_worker(void *arg)
{
    tpool_t      *tm = (tpool_t *)arg;
    tpool_work_t *work;

    while (1) {
        pthread_mutex_lock(&(tm->work_mutex));

        while (tm->work_first == NULL && !tm->stop)
            pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));

        if (tm->stop)
            break;

        work = tpool_work_get(tm);
        tm->working_cnt++;
        pthread_mutex_unlock(&(tm->work_mutex));

        if (work != NULL) {
            work->func(work->arg);
            tpool_work_destroy(work);
        }

        pthread_mutex_lock(&(tm->work_mutex));
        tm->working_cnt--;
        if (!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL)
            pthread_cond_signal(&(tm->working_cond));
        pthread_mutex_unlock(&(tm->work_mutex));
    }

    tm->thread_cnt--;
    pthread_cond_signal(&(tm->working_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    return NULL;
}

tpool_t *tpool_create(size_t num)
{
    tpool_t   *tm;
    pthread_t  thread;
    size_t     i;

    if (num == 0)
        num = 2;

    tm             = (tpool_t *)calloc(1, sizeof(*tm));
    tm->thread_cnt = num;

    pthread_mutex_init(&(tm->work_mutex), NULL);
    pthread_cond_init(&(tm->work_cond), NULL);
    pthread_cond_init(&(tm->working_cond), NULL);

    tm->work_first = NULL;
    tm->work_last  = NULL;

    for (i=0; i<num; i++) {
        pthread_create(&thread, NULL, tpool_worker, tm);
        pthread_detach(thread);
    }

    return tm;
}

void tpool_destroy(tpool_t *tm)
{
    tpool_work_t *work;
    tpool_work_t *work2;

    if (tm == NULL)
        return;

    pthread_mutex_lock(&(tm->work_mutex));
    work = tm->work_first;
    while (work != NULL) {
        work2 = work->next;
        tpool_work_destroy(work);
        work = work2;
    }
    tm->work_first = NULL;
    tm->stop = true;
    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));

    tpool_wait(tm);

    pthread_mutex_destroy(&(tm->work_mutex));
    pthread_cond_destroy(&(tm->work_cond));
    pthread_cond_destroy(&(tm->working_cond));

    free(tm);
}

bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg)
{
    tpool_work_t *work;

    if (tm == NULL)
        return false;

    work = tpool_work_create(func, arg);
    if (work == NULL)
        return false;

    pthread_mutex_lock(&(tm->work_mutex));
    if (tm->work_first == NULL) {
        tm->work_first = work;
        tm->work_last  = tm->work_first;
    } else {
        tm->work_last->next = work;
        tm->work_last       = work;
    }

    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));

    return true;
}

void tpool_wait(tpool_t *tm)
{
    if (tm == NULL)
        return;

    pthread_mutex_lock(&(tm->work_mutex));
    while (1) {
        if (tm->work_first != NULL || (!tm->stop && tm->working_cnt != 0) || (tm->stop && tm->thread_cnt != 0)) {
            pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
        } else {
            break;
        }
    }
    pthread_mutex_unlock(&(tm->work_mutex));
}

struct ThreadData {
    char filename[MAX_LINE_LENGTH * 2];
    char target_string[MAX_LINE_LENGTH];
};

void worker(void *arg) {
    ThreadData* data = (ThreadData*)arg;
    char line[MAX_LINE_LENGTH];

    FILE* file = fopen(data->filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int line_number = 1;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (strstr(line, data->target_string) != NULL) {
            printf("%s:%d:%s", data->filename, line_number, line);
        }
        line_number++;
    }

    free(data);
    fclose(file);
}

void search_files(const char* folder_path, const char* target_string) {
    DIR* directory;
    struct dirent* entry;

    directory = opendir(folder_path);
    if (directory == NULL) {
        perror("Error opening directory");
        return;
    }

    tpool_t *tm = tpool_create(MAX_THREADS);

    while ((entry = readdir(directory)) != NULL) {
        ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));
        snprintf(data->filename, sizeof(data->filename), "%s/%s", folder_path, entry->d_name);
        strcpy(data->target_string, target_string);
        tpool_add_work(tm, worker, data);
    }

    tpool_wait(tm);
    tpool_destroy(tm);
    closedir(directory);
}

void search_files_sequential(const char* folder_path, const char* target_string) {
    DIR* directory;
    struct dirent* entry;

    directory = opendir(folder_path);
    if (directory == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(directory)) != NULL) {
        char filename[MAX_LINE_LENGTH * 2];
        snprintf(filename, sizeof(filename), "%s/%s", folder_path, entry->d_name);

        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return;
        }

        char line[MAX_LINE_LENGTH];
        int line_number = 1;
        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            if (strstr(line, target_string) != NULL) {
                printf("%s:%d:%s", filename, line_number, line);
            }
            line_number++;
        }

        fclose(file);
    }

    closedir(directory);
}

struct Timer {
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<float> duration;

    Timer(std::string _name) : name(_name) {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << name << " ";
        printf("Time: %f\n", duration.count());
    }
};

int main() {
    char target_string[MAX_LINE_LENGTH];
    scanf("%s", target_string);
    {
        Timer timer("Sequential");
        search_files_sequential("./texts", target_string);
    }
    {
        Timer timer("Parallel");
        search_files("./texts", target_string);
    }
    return 0;
}
