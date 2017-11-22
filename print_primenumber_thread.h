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

#ifndef PRINT_PRIMENUMBER_THREAD_H
#define PRINT_PRIMENUMBER_THREAD_H

struct print_primenumber_thread_status {
    queue_t* queue;
};

typedef struct print_primenumber_thread_status print_primenumber_thread_status_t;

void* print_primenumber_thread_func(void* user_data);
pthread_t* print_primenumber_thread_start(size_t threads_count, queue_t* queue);
void print_primenumber_thread_wait(pthread_t* thread, size_t threads_count);

#endif //PRINT_PRIMENUMBER_THREAD_H
