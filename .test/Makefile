test: io_test
ifneq (,$(wildcard ./test_b.txt))
	rm ./test_b.txt
endif
	./io_test

io_test: ./io_test.o
	gcc -lstdc++ -O2 ./io_test.o -o io_test

io_test.o: ./io_test.cc ../io.hh.gch ../os.hh.gch
	gcc -c -I../ ./io_test.cc

../io.hh.gch: ../io.hh
	gcc -c ../io.hh

../os.hh.gch: ../os.hh
	gcc -c ../os.hh

