/**
 * MIT License
 *
 * Copyright (c) 2017 Daniele Salvatore Albano
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

#include "main.h"
#include "threads.h"
#include "queue.h"
#include "search_primenumber_thread.h"

void* search_primenumber_thread_func(void *user_data) {
    search_primenumber_thread_status_t* status;
    queue_node_t* queue_node;
    uint64_t low = 0, high = 0;
    int is_not_primenumber, number;

    printf("[SEARCH] Thread started\n");
    status = (search_primenumber_thread_status_t*)user_data;

    high = atomic_load(&status->high);
    while ((low = atomic_fetch_add(&status->low, 1)) < high) {
        is_not_primenumber = 0;

        for(number = 2; number <= low / 2; ++number) {
            if(low % number == 0) {
                is_not_primenumber = 1;
                break;
            }
        }

        if (is_not_primenumber == 0) {
            uint64_t* low_temp = malloc(sizeof(uint64_t));
            *low_temp = low;

            queue_node = queue_node_init();
            queue_node->data = low_temp;

            queue_produce(status->queue, queue_node);
        }
    }

    printf("[SEARCH] Thread ended\n");

    return NULL;
}

pthread_t* search_primenumber_thread_start(size_t threads_count, queue_t* queue) {
    pthread_t* threads;
    search_primenumber_thread_status_t* status;

    status = (search_primenumber_thread_status_t*)malloc(sizeof(search_primenumber_thread_status_t));
    status->queue = queue;
    atomic_store(&status->low, PRIMENUMBER_LOW);
    atomic_store(&status->high, PRIMENUMBER_HIGH);

    printf("Starting %d threads\n", (int)threads_count);

    threads = threads_init(threads_count);
    threads_spinup(threads, threads_count, search_primenumber_thread_func, status);

    return threads;
}

void search_primenumber_thread_wait(pthread_t* threads, size_t threads_count) {
    threads_join(threads, threads_count);
}
