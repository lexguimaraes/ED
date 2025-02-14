cmake_minimum_required(VERSION 3.28)
project(Revisao_p1_ed C)

set(CMAKE_C_STANDARD 99)


add_executable(Q5 Q5.c TG.c)

add_executable(Q3 Q3.c
        TABB.c)
add_executable(Q4 Q4.c
        TAB.c)