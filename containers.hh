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

	// Allocator

	class AllocEmptyErr: public exception {
		virtual const char *what () const throw () {
			return "allocator out of memory";
		}//-- end what
	} alloc_empty;//-- end class AllocEmptyErr

	template <class T, const size_t size>
	class Allocator: public allocator<T> {
		protected:
		const T memory[size];
		const T *limit;
		T *curr;
		Stack <T*, size> pool;
		public:
		Allocator () : memory(), limit(memory + size) {
			this->curr = (T*) memory;
		}//-- end constructor 1

		T* allocate () {
			if (!this->pool.is_empty()) {
				return this->pool.pop();
			}
			if (this->curr == this->limit) throw alloc_empty;
			T *out = this->curr;
			this->curr++;
			return out;
		}//-- end T* alloc

		T* allocate (size_t len) {
			if (this->curr + len > this->limit) throw alloc_empty;
			T *out = this->curr;
			this->curr += len;
			return out;
		}//-- end T* alloc

		void deallocate (T *item) {
			this->pool.push(item);
		}//-- end void deallocate

		size_t capacity () {
			return this->limit - this->curr + this->pool.size();
		}//-- end size_t capacity

		bool is_empty () {
			return this->curr == this->limit && this->pool.is_empty();
		}//-- end bool is_full
	};//-- end class Allocator

};//-- end namespace cont

#endif

