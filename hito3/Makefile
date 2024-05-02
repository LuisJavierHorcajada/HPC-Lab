DIROBJ := obj/
DIREXE := exec/

CFLAGS = -std=c++17 `pkg-config opencv4 --cflags` -O3
LDFLAGS = `pkg-config opencv4 --libs`
CC = g++


OPENMP := -fopenmp


# Default target to build the executable
all: dirs kmeans_c++ kmeans_OMP

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

# Target to build the executable
kmeans_c++: $(DIROBJ)kmeans_c++.o
	$(CC) $(CFLAGS) -o $(DIREXE)$@ $^ $(LDFLAGS)

kmeans_OMP: $(DIROBJ)kmeans_OMP.o
	$(CC) $(OPENMP) $(CFLAGS) -o $(DIREXE)$@ $^ $(LDFLAGS)

$(DIROBJ)kmeans_c++.o: kmeans_c++.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

$(DIROBJ)kmeans_OMP.o: kmeans_OMP.cpp
	$(CC) $(OPENMP) $(CFLAGS) -c $^ -o $@

# Run target that allows additional arguments to be passed
run_sequential: 
	./$(DIREXE)kmeans_c++ $(ARGS)

run_sequential_example:
	./$(DIREXE)kmeans_c++ -k 10 -i 200

run_OMP:
	./$(DIREXE)kmeans_OMP $(ARGS)

run:
	./$(DIREXE)kmeans_OMP -k 10 -i 300

clean : 
	rm -rf *~ core $(DIROBJ) $(DIREXE)
