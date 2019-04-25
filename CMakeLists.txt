cmake_minimum_required(VERSION 3.14)
project(rainbow-table)

set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_executable(main main.c trie.c trie.h random.c random.h tinymt/tinymt64.h tinymt/tinymt64.c
        generator.c generator.h configsamples.c configsamples.h config.h solver.c solver.h)
target_link_libraries(main OpenSSL::Crypto)
target_link_libraries(main Threads::Threads)