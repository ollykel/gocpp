/**
 * @author Oliver Kelton, oakelton@gmail.com
 * @date May 23, 2019
 * Tests for alloc.hh
 */

#include <iostream>

#include "alloc.hh"

using namespace std;

#define MEMORY_LEN 20

template <class Type>
bool unit_alloc (const char *name, size_t num_to_alloc, const bool should_fail) {
	bool has_failed = false;
	cout << "Testing alloc for " << name << ":\n";
	cout << "(num_to_alloc: " << num_to_alloc << ")\n";
	Type memory[MEMORY_LEN];
	printf("Stack memory addr: %p\n", memory);
	alloc::Allocator<Type> allocator = alloc::Allocator <Type> (
		memory, sizeof(memory) / sizeof(Type));
	cout << "Initialized allocator\n";
	try {
		Type *unit = NULL;
		for (; num_to_alloc; --num_to_alloc) {
			unit = allocator.alloc();
			printf("\tUnit addr: %p\n", unit);
		}//-- end for num_to_alloc
	} catch (exception& e) {
		cout << "Failed: " << e.what() << "\n";
		has_failed = true;
		if (should_fail) cout << "(Expected to fail)\n";
	}//-- end try-catch
	if (should_fail && !has_failed) {
		cout << "Should have failed\n";
	}
	cout << "Done testing alloc for " << name << "\n\n";
	return (has_failed && !should_fail) || (!has_failed && should_fail);
}//-- end bool unit_alloc

class Foobar {
	int a;
	int b;
	char c;
};//-- end class Foobar

bool test_alloc () {
	bool has_failed = false;
	cout << "Testing alloc:\n";
	has_failed = has_failed || unit_alloc <int> ("int", 5, false);
	has_failed = has_failed || unit_alloc <Foobar> ("Foobar", 10, false);
	has_failed = has_failed || unit_alloc <long int> ("long int", 30, true);
	has_failed = has_failed || unit_alloc <Foobar> ("Foobar", 19, false);
	cout << "Done testing alloc\n";
	return has_failed;
}//-- end test_alloc

int main (const int argc, const char **argv) {
	cout << "Testing alloc.hh...\n";
	bool failed = test_alloc();
	cout << "Tests failed? " << failed << "\n";
	cout << "Done testing alloc.hh\n";
	return 0;
}//-- end int main


