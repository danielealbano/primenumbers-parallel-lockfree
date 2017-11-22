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
#include <stdbool.h>
#include <pthread.h>

#include "main.h"
#include "queue.h"
#include "util.h"
#include "print_primenumber_thread.h"
#include "search_primenumber_thread.h"

int main(int argc, char** argv) {
    queue_t *queue;
    pthread_t *search_primenumber_threads;
    pthread_t *print_primenumber_thread;
    size_t search_primenumber_threads_count;
    int core_count;

    core_count = util_core_count();

    if (THREADS_PRINT_COUNT + 1 > core_count) {
        fprintf(stderr, "Unable to start a search threads, reduce the THREADS_PRINT_COUNT const, too few cores!\n");
        fflush(stderr);
        return 1;
    }

    search_primenumber_threads_count = (size_t) core_count - THREADS_PRINT_COUNT;
    terminate = false;

    queue = queue_init();

    print_primenumber_thread = print_primenumber_thread_start(
            THREADS_PRINT_COUNT,
            queue);

    search_primenumber_threads = search_primenumber_thread_start(
            search_primenumber_threads_count,
            queue);

    search_primenumber_thread_wait(
            search_primenumber_threads,
            search_primenumber_threads_count);

    terminate = true;

    print_primenumber_thread_wait(
            print_primenumber_thread,
            THREADS_PRINT_COUNT);

    printf("Done!");

    return 0;
}
