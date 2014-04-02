
int work (int thread_id, int num_threads) {
    struct timespec sleeptime;
    sleeptime.tv_sec = 1.0; sleeptime.tv_nsec = 1000000;
    nanosleep(&sleeptime, NULL);
    return 0;
}


