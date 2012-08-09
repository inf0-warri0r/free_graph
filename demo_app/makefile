#Author :Tharindra Galahena
#Project:free_graph - graph drawing library for c/c++ (linux) -demo app
#Date   :28/06/2012

CC    = gcc
FILES = demo.c
FLAGS = -lfree_graph
GTK_LIBS = $(shell pkg-config --libs gtk+-2.0)
GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)

all:	
	$(CC) -g -o demo $(FILES) $(FLAGS) $(GTK_LIBS) $(GTK_FLAGS) 
