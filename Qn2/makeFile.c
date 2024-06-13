CC = gcc
CFLAGS = -Wall -Wextra

student_sort: student_sort.c
    $(CC) $(CFLAGS) -o student_sort student_sort.c

program_graph: program_graph.c
    $(CC) $(CFLAGS) -o program_graph program_graph.c

all: student_sort program_graph

clean:
    rm -f student_sort program_graph