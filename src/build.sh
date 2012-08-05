#!/bin/bash

gcc -Wall -c -fpic free_graph.c fg_error.c fg_structs.h
gcc -Wall -shared -o libfree_graph.so free_graph.o fg_error.o fg_structs.h
