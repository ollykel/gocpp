#ifndef CONTAINERS_HH
#define CONTAINERS_HH

/**
 * @author Oliver Kelton, oakelton@gmail_com
 * @date May 23, 2019
 * Contains common container classes, as well as a stack-based allocator.
 */

#include <iostream>
#include <memory>

using namespace std;

namespace cont {
	
	class StackFullErr: public exception {
		public:
		virtual const char *what () const throw () {
			return "stack full";
		}//-- end const char *what
	} stack_full;

	class StackEmptyErr: public exception {
		public:
		virtual const char *what () const throw () {
			return "stack empty";
		}//-- end const char *what
	} stack_empty;

	template <class T, const size_t mem_size>
	class Stack {
		protected:
		const T memory[mem_size];
		const T *limit;
		T *head;
		public:
		Stack (): memory(), limit(memory + mem_size) {
			this->head = (T*) memory;
		}//-- end constructor

		bool is_empty () {
			return this->head == this->memory;
		}//-- end bool is_empty

		bool is_full() {
			return this->head == this->limit;
		}//-- end bool is_full

		size_t size() {
			return this->head - this->memory;
		}//-- end size_t size

		void push (T item) {
			if (this->is_full()) throw stack_full;
			*this->head = item;
			this->head++;
		}//-- end void push

		T pop () {
			if (this->is_empty()) throw stack_empty;
			this->head--;
			return *this->head;
		}//-- end T pop
	};//-- end class Stack

};//-- end namespace cont

#endif

