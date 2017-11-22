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
#include <pthread.h>
#include <stdbool.h>

#include "main.h"
#include "queue.h"
#include "threads.h"
#include "print_primenumber_thread.h"

void* print_primenumber_thread_func(void* user_data) {
    queue_node_t* queue_node;
    queue_node_t* old_queue_node;
    print_primenumber_thread_status_t* status = (print_primenumber_thread_status_t*)user_data;

    do {
        queue_node = queue_consume_all(status->queue);

        while(queue_node != NULL) {
            printf("[PRINT] %llu\n", *(uint64_t *)queue_node->data);

            old_queue_node = queue_node;
            queue_node = (queue_node_t*)queue_node->next;

            free(old_queue_node->data);
            free(old_queue_node);
        }
    }
    while(terminate == false);

    printf("[PRINT] Thread ended\n");

    return NULL;
}

pthread_t* print_primenumber_thread_start(size_t threads_count, queue_t* queue) {
    pthread_t* thread;
    print_primenumber_thread_status_t* status;

    status = malloc(sizeof(print_primenumber_thread_status_t));
    status->queue = queue;

    thread = threads_init(threads_count);
    threads_spinup(
            thread,
            threads_count,
            print_primenumber_thread_func,
            status);

    return thread;
}

void print_primenumber_thread_wait(pthread_t* thread, size_t threads_count) {
    threads_join(thread, threads_count);
}
