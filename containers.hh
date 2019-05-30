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

	class AllocFullException: public exception {
		virtual const char *what () const throw () {
			return "allocator full";
		}//-- end what
	} alloc_full;//-- end class AllocFullException

	template <class T>
	class PreAllocator {
		protected:
		const T *memory;
		const T *limit;
		T *head;
		public:
		PreAllocator (size_t sz): memory(new T[sz]), limit(memory + sz) {
			this->head = this->memory;
		}//-- end constructor 1

		~PreAllocator () {
			delete this->memory;
		}//-- end destructor

		size_t capacity () {
			return this->limit - this->head;
		}//-- end size_t capacity

		bool is_full () {
			return this->head == this->limit;
		}//-- end bool is_full

		T *allocate () {
			if (this->is_full()) throw alloc_full;
			T *out = this->head;
			++this->head;
			return out;
		}//-- end T *allocate
	};//-- end class PreAllocator

};//-- end namespace cont

#endif

