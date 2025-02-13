#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[]) {
    pid_t pid;
    pid = fork();

    if (pid > 0) {
        pid_t myPid = getpid();
        printf("my pid=%d, I am the parent of pid=%d!\n", myPid, pid);
        printf("PID(%d) - current nice value: %d\n", getpid(), nice(0));
        nice(19);
        printf("PID(%d) - new nice value: %d\n", getpid(), nice(0));
    } else if (pid == 0) {
        pid_t parentPid = getppid();
        pid_t myPid = getpid();

        printf("my pid=%d, I am the child of pid=%d!\n", myPid, parentPid);
        printf("PID(%d) - current nice value: %d\n", getpid(), nice(0));
        nice(-19);
        printf("PID(%d) - new nice value: %d\n", getpid(), nice(0));

    } else if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    for(int i = 0; i <  2147482455; i++)
    {
        
    }
    end = clock();

    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    printf("PID(%d) - I finished with time = %.6f!!!\n", getpid(),cpu_time_used);

    sleep(5);
    return 0;
}
// với nice value bằng nhau thì thời chạy 2 tiến trinh gần giống nhau không đổi nhiều

// với nice value khác nhau thì tiến trình có nice value cao ( pri thấp ) có xu hướng chạy châm
 // hơn so với tiến trình có nice thấp(pri cao)