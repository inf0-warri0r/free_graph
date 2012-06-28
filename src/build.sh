#!/bin/bash

gcc -Wall -c -fpic free_graph.c structs.h
gcc -Wall -shared -o libfree_graph.so free_graph.o structs.h
