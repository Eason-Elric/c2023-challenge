project(level1)

add_executable(p01_running_letter p01_running_letter/main.cpp)

add_executable(p02_is_prime p02_is_prime/main.cpp)

add_executable(p03_all_primes "p03_all_primes/main(1).cpp")

add_executable(p03_all_primes_ "p03_all_primes/main(2).cpp")

add_executable(p04_goldbach p04_goldbach/main.cpp)

add_executable(p05_encrypt_decrypt p05_encrypt_decrypt/main.cpp)

add_executable(p06_hanoi p06_hanoi/main.cpp)

add_executable(p07_maze p07_maze/main.cpp
        p07_maze/Maze.h
        p07_maze/Move.h
        p07_maze/ConstData.h
)

add_executable(p08_push_boxes p08_push_boxes/main.cpp
        p08_push_boxes/RandomMap.h
        p08_push_boxes/Archive.h
)

add_executable(p09_linked_list p09_linked_list/main.cpp)

add_executable(p10_warehouse p10_warehouse/main.cpp
)