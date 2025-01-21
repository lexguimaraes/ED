cmake_minimum_required(VERSION 3.28)
project(ED C)

set(CMAKE_C_STANDARD 90)

add_executable(teste_TG bibliotecas/TG/teste_TG.c)



add_executable(teste_TARVB bibliotecas/arvore-b/teste_TARVB.c bibliotecas/arvore-b/TARVB.c TLSE.c ./bibliotecas/TLSEINT.c)
add_executable(heap bibliotecas/heap/heap.c)
add_executable(hash bibliotecas/tabela_hash/teste_TH.c bibliotecas/tabela_hash/TH.c TLSE.c)
add_executable(teste_TARVBM bibliotecas/arvore-bp/teste_TARVBM.c bibliotecas/arvore-bp/TARVBM.c)