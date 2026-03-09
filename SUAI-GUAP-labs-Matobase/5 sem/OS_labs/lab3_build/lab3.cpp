#include "lab3.h"
#include <windows.h>
#include <stdio.h>

unsigned int lab3_thread_graph_id()
{
    return 18;
}

const char* lab3_unsynchronized_threads()
{
    return "bcdi";
}

const char* lab3_sequential_threads()
{
    return "khi";
}

using namespace std;

HANDLE mutexUnsync;
void outUnsync(const string &str)
{
    for (int i = 0; i < 3; ++i)
    {
        auto res = WaitForSingleObject(mutexUnsync, INFINITE);
        if (res == WAIT_OBJECT_0)
        {
            cout << str << flush;
            ReleaseMutex(mutexUnsync);
        }
        computation();
    }
}

void outSync(const string &str,
             HANDLE curSem,
             HANDLE nextSem)
{
    for (int i = 0; i < 3; ++i)
    {
        auto res = WaitForSingleObject(curSem, INFINITE);
        if (res == WAIT_OBJECT_0)
        {
            cout << str << flush;
            ReleaseSemaphore(nextSem, 1, NULL);
        }
        computation();
    }
}

HANDLE semISync, semKSync, semHSync,
    mutexB, mutexI, mutexF, mutexH;

void graphB() {
    outUnsync("b");
    ReleaseSemaphore(mutexI, 1, NULL);
    WaitForSingleObject(mutexB, INFINITE);
    WaitForSingleObject(mutexB, INFINITE);
    outUnsync("b");
    ReleaseSemaphore(mutexI, 1, NULL);
    WaitForSingleObject(mutexB, INFINITE);
    WaitForSingleObject(mutexB, INFINITE);
    WaitForSingleObject(mutexB, INFINITE);
    outUnsync("b");
    ReleaseSemaphore(mutexI, 1, NULL);
    ReleaseSemaphore(mutexF, 1, NULL);
    ReleaseSemaphore(mutexH, 1, NULL);
    WaitForSingleObject(mutexB, INFINITE);
    WaitForSingleObject(mutexB, INFINITE);
    WaitForSingleObject(mutexB, INFINITE);
    WaitForSingleObject(mutexB, INFINITE);
    outUnsync("b");
    ReleaseSemaphore(mutexI, 1, NULL);
    ReleaseSemaphore(mutexH, 1, NULL);
    return ExitThread(0);
}

void graphA() {
    outUnsync("a");
    ReleaseSemaphore(mutexB, 1, NULL);
    ReleaseSemaphore(mutexI, 1, NULL);
    return ExitThread(0);
}

void graphC()
{
    outUnsync("c");
    ReleaseSemaphore(mutexB, 1, NULL);
    ReleaseSemaphore(mutexI, 1, NULL);
    return ExitThread(0);
}

void graphD()
{
    outUnsync("d");
    ReleaseSemaphore(mutexB, 1, NULL);
    ReleaseSemaphore(mutexI, 1, NULL);
    return ExitThread(0);
}

void graphE()
{
    outUnsync("e");
    ReleaseSemaphore(mutexB, 1, NULL);
    ReleaseSemaphore(mutexI, 1, NULL);
    ReleaseSemaphore(mutexF, 1, NULL);
    ReleaseSemaphore(mutexH, 1, NULL);
    return ExitThread(0);
}

void graphF()
{
    outUnsync("f");
    ReleaseSemaphore(mutexI, 1, NULL);
    ReleaseSemaphore(mutexH, 1, NULL);
    ReleaseSemaphore(mutexB, 1, NULL);
    WaitForSingleObject(mutexF, INFINITE);
    WaitForSingleObject(mutexF, INFINITE);
    WaitForSingleObject(mutexF, INFINITE);
    WaitForSingleObject(mutexF, INFINITE);
    outUnsync("f");
    ReleaseSemaphore(mutexI, 1, NULL);
    ReleaseSemaphore(mutexH, 1, NULL);
    return ExitThread(0);
}

void graphG()
{
    outUnsync("g");
    ReleaseSemaphore(mutexI, 1, NULL);
    ReleaseSemaphore(mutexF, 1, NULL);
    ReleaseSemaphore(mutexH, 1, NULL);
    return ExitThread(0);
}

void graphH()
{
    outUnsync("h");
    ReleaseSemaphore(mutexI, 1, NULL);
    ReleaseSemaphore(mutexB, 1, NULL);
    ReleaseSemaphore(mutexF, 1, NULL);
    WaitForSingleObject(mutexH, INFINITE);
    WaitForSingleObject(mutexH, INFINITE);
    WaitForSingleObject(mutexH, INFINITE);
    WaitForSingleObject(mutexH, INFINITE);
    outUnsync("h");
    ReleaseSemaphore(mutexI, 1, NULL);
    outSync("h", semHSync, semISync);
    return ExitThread(0);
}

void graphM()
{
    outUnsync("m");
    return ExitThread(0);
}

void graphK()
{
    outSync("k", semKSync, semHSync);
    return ExitThread(0);
}

void graphI()
{
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphA, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphB, NULL, 0, NULL);
    outUnsync("i");
    ReleaseSemaphore(mutexB, 1, NULL);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphC, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphD, NULL, 0, NULL);
    outUnsync("i");
    ReleaseSemaphore(mutexB, 1, NULL);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphE, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphF, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphH, NULL, 0, NULL);
    outUnsync("i");
    ReleaseSemaphore(mutexB, 1, NULL);
    ReleaseSemaphore(mutexF, 1, NULL);
    ReleaseSemaphore(mutexH, 1, NULL);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphG, NULL, 0, NULL);
    outUnsync("i");
    ReleaseSemaphore(mutexH, 1, NULL);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    WaitForSingleObject(mutexI, INFINITE);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphK, NULL, 0, NULL);
    outSync("i", semISync, semKSync);

    auto idM = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphM, NULL, 0, NULL);
    WaitForSingleObject(idM, INFINITE);
    CloseHandle(idM);
    return ExitThread(0);
}


int lab3_init()
{
    mutexUnsync = CreateMutex(NULL, FALSE, NULL);
    mutexB = CreateSemaphore(NULL, 0, 4, NULL);
    mutexI = CreateSemaphore(NULL, 0, 4, NULL);
    mutexF = CreateSemaphore(NULL, 0, 4, NULL);
    mutexH = CreateSemaphore(NULL, 0, 4, NULL);
    semKSync = CreateSemaphore(NULL, 1, 1, NULL);
    semISync = CreateSemaphore(NULL, 0, 1, NULL);
    semHSync = CreateSemaphore(NULL, 0, 1, NULL);

    auto idI = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)graphI, NULL, 0, NULL);
    WaitForSingleObject(idI, INFINITE);
    CloseHandle(idI);
    CloseHandle(mutexUnsync);
    CloseHandle(mutexI);
    CloseHandle(mutexB);
    CloseHandle(mutexF);
    CloseHandle(mutexH);
    CloseHandle(semISync);
    CloseHandle(semKSync);
    CloseHandle(semHSync);

    return 0;
}
