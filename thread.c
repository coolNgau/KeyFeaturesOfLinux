#include <stdio.h>
#include <pthread.h>

void* startRoutine(void* msg) {
    const pthread_t me = pthread_self();
    printf("%s", (char*)msg);
    printf(" %lu\n--------------------\n", me);
    return NULL;
}

int main(int argc, char* argv[]) {
    char* msg = "hello from thread main ID:";
    const pthread_t me = pthread_self();
    printf("%s %lu\n--------------------\n", msg, me);

    pthread_t tid0, tid1, tid2;
    pthread_create(&tid0, NULL, startRoutine, (void*)("hello from thread0 ID:"));
    pthread_create(&tid1, NULL, startRoutine, (void*)("hello from thread1 ID:"));
    pthread_create(&tid2, NULL, startRoutine, (void*)("hello from thread2 ID:"));

    printf("join\nthread ID: %lu\nthread ID: %lu\nthread ID: %lu\n", tid0, tid1, tid2);

    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("3 threads have terminated\n");

    return 0;
}
// => trình tự thực thi mỗi lần chạy khác nhau, không thể tự quyết định đuơc
// => cần các kỹ năng đồng bộ.