#!/bin/bash

gcc -Wall -c -fpic free_graph.c fg_structs.h
gcc -Wall -shared -o libfree_graph.so free_graph.o fg_structs.h
