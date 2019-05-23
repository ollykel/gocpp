test: alloc_test
	./alloc_test

alloc_test: alloc_test.o
	gcc -lstdc++ alloc_test.o -o alloc_test

alloc_test.o: alloc_test.cc ../alloc.hh.gch
	gcc -c -I../ alloc_test.cc

../alloc.hh.gch: ../alloc.hh
	gcc -c -I../ ../alloc.hh

