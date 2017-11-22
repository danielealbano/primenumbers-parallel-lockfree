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

#include <stdlib.h>
#include <stdatomic.h>

#include "queue.h"

queue_node_t* queue_node_init() {
    return (queue_node_t*)malloc(sizeof(queue_node_t));
}

queue_t* queue_init() {
    queue_t* queue = malloc(sizeof(queue_t));
    atomic_exchange(&queue->head, ATOMIC_VAR_INIT(0));

    return queue;
}

queue_node_t* queue_consume_all(queue_t* queue) {
    queue_node_t* queue_node = (queue_node_t*)atomic_exchange(&queue->head, ATOMIC_VAR_INIT(0));
    return queue_node;
}

void queue_produce(queue_t* queue, queue_node_t* queue_node) {
    intptr_t queue_node_ptr = (intptr_t)queue_node;
    intptr_t head_ptr = atomic_load(&queue->head);
    atomic_store(&queue_node->next, head_ptr);

    while(!atomic_compare_exchange_weak_explicit(
            &queue->head,
            &queue_node->next,
            queue_node_ptr,
            memory_order_release,
            memory_order_relaxed)) {
        // do nothing
    }
}