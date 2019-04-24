cmake_minimum_required(VERSION 3.14)
project(rainbow-table)

set(CMAKE_C_STANDARD 99)

find_package(OpenSSL REQUIRED)

add_executable(main main.c trie.c trie.h)
target_link_libraries(main OpenSSL::Crypto)