#include "lab2.h"
#include <cstring>
#include <semaphore.h>

unsigned int lab2_thread_graph_id()
{
    return 2;
}

const char* lab2_unsynchronized_threads()
{
    return "bcde";
}

const char* lab2_sequential_threads()
{
    return "ikm";
}

using namespace std;

pthread_mutex_t mutexUnsynchronizedEdge;
void handleTaskUnsynchronized(const string &edgeId)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&mutexUnsynchronizedEdge);
        std::cout << edgeId << std::flush;
        pthread_mutex_unlock(&mutexUnsynchronizedEdge);
        computation();
    }
}

void handleTaskSynchronized(const string &edgeId,
                            sem_t &currentTask,
                            sem_t &nextTask)
{
    for (int i = 0; i < 3; ++i) {
        sem_wait(&currentTask);
        std::cout << edgeId << std::flush;
        sem_post(&nextTask);
        computation();
    }
}

sem_t mutexEdgeIdISync, mutexEdgeIdKSync, mutexEdgeIdMSync,
    mutexEdgeIdFSync, mutexEdgeIdESync, mutexEdgeIdB, mutexEdgeIdE, mutexEdgeIdI;

void *edgeIdE(void *ptr);
void *edgeIdC(void *ptr);
void *edgeIdA(void *ptr);
void *edgeIdI(void *ptr);
void *edgeIdD(void *ptr);
void *edgeIdG(void *ptr);
void *edgeIdF(void *ptr);
void *edgeIdH(void *ptr);
void *edgeIdB(void *ptr) {
    pthread_t idA;
    pthread_create(&idA, 0, edgeIdA, NULL);
    handleTaskUnsynchronized("b");
    sem_wait(&mutexEdgeIdB);
    pthread_t idE;
    pthread_create(&idE, 0, edgeIdE, NULL);
    pthread_t idD;
    pthread_create(&idD, 0, edgeIdD, NULL);
    pthread_t idC;
    pthread_create(&idC, 0, edgeIdC, NULL);
    handleTaskUnsynchronized("b");
    sem_wait(&mutexEdgeIdB);
    sem_wait(&mutexEdgeIdB);
    sem_wait(&mutexEdgeIdB);
    sem_post(&mutexEdgeIdE);

    pthread_t idI;
    pthread_create(&idI, 0, edgeIdI, NULL);
    pthread_t idF;
    pthread_create(&idF, 0, edgeIdF, NULL);
    pthread_t idG;
    pthread_create(&idG, 0, edgeIdG, NULL);
    pthread_t idH;
    pthread_create(&idH, 0, edgeIdH, NULL);
    pthread_join(idI, NULL);
    return ptr;
}

void *edgeIdA(void *ptr) {
    handleTaskUnsynchronized("a");
    sem_post(&mutexEdgeIdB);
    return ptr;
}

void *edgeIdC(void *ptr)
{
    handleTaskUnsynchronized("c");
    sem_post(&mutexEdgeIdB);
    return ptr;
}

void *edgeIdD(void *ptr)
{
    handleTaskUnsynchronized("d");
    sem_post(&mutexEdgeIdB);
    return ptr;
}

void *edgeIdE(void *ptr)
{
    handleTaskUnsynchronized("e");
    sem_post(&mutexEdgeIdB);
    sem_wait(&mutexEdgeIdE);
    handleTaskUnsynchronized("e");
    sem_post(&mutexEdgeIdI);
    return ptr;
}

void *edgeIdF(void *ptr)
{
    handleTaskUnsynchronized("f");
    sem_post(&mutexEdgeIdI);
    return ptr;
}

void *edgeIdG(void *ptr)
{
    handleTaskUnsynchronized("g");
    sem_post(&mutexEdgeIdI);
    return ptr;
}

void *edgeIdH(void *ptr)
{
    handleTaskUnsynchronized("h");
    sem_post(&mutexEdgeIdI);
    return ptr;
}

void *edgeIdN(void *ptr);
void *edgeIdM(void *ptr);
void *edgeIdK(void *ptr);
void *edgeIdI(void *ptr)
{
    handleTaskUnsynchronized("i");

    sem_wait(&mutexEdgeIdI);
    sem_wait(&mutexEdgeIdI);
    sem_wait(&mutexEdgeIdI);
    sem_wait(&mutexEdgeIdI);
    pthread_t idM;
    pthread_create(&idM, NULL, edgeIdM, NULL);
    pthread_t idK;
    pthread_create(&idK, NULL, edgeIdK, NULL);
    handleTaskSynchronized("i", mutexEdgeIdISync, mutexEdgeIdKSync);
    sem_wait(&mutexEdgeIdI);

    pthread_t idN;
    pthread_create(&idN, 0, edgeIdN, NULL);
    pthread_join(idN, NULL);
    return ptr;
}

void *edgeIdK(void *ptr)
{
    handleTaskSynchronized("k", mutexEdgeIdKSync, mutexEdgeIdMSync);
    return ptr;
}

void *edgeIdM(void *ptr)
{
    handleTaskSynchronized("m", mutexEdgeIdMSync, mutexEdgeIdISync);
    sem_post(&mutexEdgeIdI);
    return ptr;
}

void *edgeIdN(void *ptr)
{
    handleTaskUnsynchronized("n");
    return ptr;
}

int lab2_init()
{
    pthread_mutex_init(&mutexUnsynchronizedEdge, NULL);
    sem_init(&mutexEdgeIdB, 0, 0);
    sem_init(&mutexEdgeIdI, 0, 0);
    sem_init(&mutexEdgeIdE, 0, 0);
    sem_init(&mutexEdgeIdKSync, 0, 0);
    sem_init(&mutexEdgeIdFSync, 0, 0);
    sem_init(&mutexEdgeIdISync, 0, 1);
    sem_init(&mutexEdgeIdMSync, 0, 0);
    sem_init(&mutexEdgeIdESync, 0, 0);

    pthread_t idEdgeB;
    pthread_create(&idEdgeB, 0, edgeIdB, NULL);
    pthread_join(idEdgeB, NULL);

    pthread_mutex_destroy(&mutexUnsynchronizedEdge);
    sem_destroy(&mutexEdgeIdI);
    sem_destroy(&mutexEdgeIdB);
    sem_destroy(&mutexEdgeIdE);
    sem_destroy(&mutexEdgeIdISync);
    sem_destroy(&mutexEdgeIdKSync);
    sem_destroy(&mutexEdgeIdESync);
    sem_destroy(&mutexEdgeIdFSync);
    sem_destroy(&mutexEdgeIdMSync);

    return 0;
}

