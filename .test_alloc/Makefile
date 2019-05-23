test: alloc_test
	./alloc_test

alloc_test: alloc_test.o
	gcc -lstdc++ alloc_test.o -o alloc_test

alloc_test.o: alloc_test.cc ../containers.hh.gch
	gcc -c -I../ alloc_test.cc

../containers.hh.gch: ../containers.hh
	gcc -c -I../ ../containers.hh

