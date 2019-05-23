/**
 * @author Oliver Kelton, oakelton@gmail.com
 * @date May 23, 2019
 * Tests for containers.hh
 */

#include <iostream>

#include "containers.hh"

using namespace std;

#define MEMORY_LEN 20

template <class Type>
bool unit_alloc (const char *name, size_t num_to_alloc, const bool should_fail) {
	bool has_failed = false;
	cout << "Testing alloc for " << name << ":\n";
	cout << "(num_to_alloc: " << num_to_alloc << ")\n";
	Type memory[MEMORY_LEN];
	Type *pool[MEMORY_LEN];
	printf("Stack memory addr: %p\n", memory);
	cont::Allocator<Type> allocator = cont::Allocator <Type> (memory, pool,
		MEMORY_LEN);
	cout << "Initialized allocator\n";
	try {
		Type *unit = NULL;
		for (; num_to_alloc; --num_to_alloc) {
			unit = allocator.allocate();
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

template <class T>
bool unit_stack (T *items, size_t len, size_t num_pop, bool should_fail) {
	printf("Testing stack (%zu items, should_fail %d):\n", len, should_fail);
	T memory[MEMORY_LEN];
	cont::Stack <T> stack = cont::Stack <T> (memory, MEMORY_LEN);
	try {
		for (T *item = items, *lim = items + len; item != lim; ++item) {
			cout << "\tPushing " << *item << " to stack...\n";
			stack.push(*item);
		}//-- end for item
		cout << "Done pushing to stack; now popping...\n";
		T curr;
		for (; num_pop; --num_pop) {
			curr = stack.pop();
			cout << "\tPopped: " << curr << "\n";
		}//-- end for len
	} catch (exception& e) {
		cout << "Failed: " << e.what() << "\n";
		if (should_fail) cout << "(expected to fail)\n";
		return !should_fail;
	}
	return should_fail;
}//-- end bool unit_stack

bool test_stack () {
	bool has_failed = false;
	cerr << "Testing stack:\n";
	int testers[7] = { 6, 12, 13, 7, 3, 2, 17 };
	has_failed = unit_stack <int> (testers, 7, 7, false) || has_failed;
	has_failed = unit_stack <int> (testers, 7, 10, true) || has_failed;
	cerr << "Done testing stack\n";
	return has_failed;
}//-- end test_stack

int main (const int argc, const char **argv) {
	cout << "Testing containers.hh...\n";
	bool failed = test_alloc();
	cout << "Alloc tests failed? " << failed << "\n";
	failed = test_stack();
	cout << "Stack tests failed? " << failed << "\n";
	cout << "Done testing containers.hh\n";
	return 0;
}//-- end int main


