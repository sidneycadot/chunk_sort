
CC=$(CXX)
CXXFLAGS=-W -Wall -O3 -std=c++17

chunk_sort_benchmark : chunk_sort_benchmark.o sidney_sort.o denis_sort.o

chunk_sort_benchmark.o : chunk_sort_benchmark.cc sidney_sort.h denis_sort.h

sidney_sort.o : sidney_sort.cc sidney_sort.h

sidney_sort.o : denis_sort.cc denis_sort.h

clean :
	$(RM) chunk_sort_benchmark *.o *~
