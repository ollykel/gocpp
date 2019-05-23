#ifndef ALLOC_HH
#define ALLOC_HH

/**
 * @author Oliver Kelton, oakelton@gmail_com
 * @date May 22, 2019
 * Classes to allocate chunks of memory from a contiguous block of memory on
 * the stack or the heap, as the developer chooses.
 */

#include <iostream>

using namespace std;

namespace alloc {
	
	class AllocEmptyErr: public exception {
		virtual const char *what () const throw () {
			return "allocator out of memory";
		}//-- end what
	} alloc_empty;//-- end class AllocEmptyErr

	template <class T>
	class Allocator {
		protected:
		T *start;
		T *curr;
		T *limit;
		public:
		Allocator (T *src, const size_t len) {
			this->start = src;
			this->curr = src;
			this->limit = src + len;
		}//-- end constructor 1

		T* alloc () {
			if (this->curr == this->limit) throw alloc_empty;
			T *out = this->curr;
			this->curr++;
			return out;
		}//-- end T* alloc

		size_t capacity () {
			return this->limit - this->curr;
		}//-- end size_t capacity
	};//-- end class Allocator

};//-- end namespace alloc

#endif

