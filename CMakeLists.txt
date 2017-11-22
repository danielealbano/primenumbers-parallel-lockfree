cmake_minimum_required(VERSION 3.8)
project(primenumbers_parallel_lockfree)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c queue.c queue.h search_primenumber_thread.c search_primenumber_thread.h print_primenumber_thread.c print_primenumber_thread.h threads.c threads.h main.h util.c util.h)
add_executable(primenumbers_parallel_lockfree ${SOURCE_FILES})