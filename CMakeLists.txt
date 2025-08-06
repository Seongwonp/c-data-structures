cmake_minimum_required(VERSION 3.30)
project(CProject C)

set(CMAKE_C_STANDARD 11)

add_executable(CProject
        #        CardConverter/card_converter.c
#        CardConverter/card_converter.h
#        Sosu/sosu.c
#        Sosu/sosu.h
#        List/spare_array.c
#        List/spare_array.h
#        List/list.c
#        List/list.h
#        List/circle_double_linked_list.c
#        List/circle_double_linked_list.h
        Stack/stack.c
        Stack/stack.h
#        Stack/postfix.c
#        Stack/postfix.h
#        Stack/calculator.c
#        Stack/calculator.h
        Queue/queue.c
        Queue/queue.h
#        Queue/ring_queue.c
        Graph/graph.c
        Graph/graph.h
        Sort/sort.c
        Sort/sort.h
        CardConverter/card_converter.c
        #        Heap/Heap.c
#        Heap/Heap.h
#        Set/union_find.c
#        Set/union_find.h
#        Hash/chain_hash.c
#        Hash/chain_hash.h
#        Hash/open_address.c
#        Hash/open_address.h
#        Recursive/recursive.c
#        Recursive/recursive.h
#        Tree/tree_order.c
#        Tree/tree_order.h
#        Tree/binary_tree.c
#        Tree/binary_tree.h
)
