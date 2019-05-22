#ifndef IO_HH
#define IO_HH

/**
 * @author Oliver Kelton, oakelton@gmail_com
 * @date May 21, 2019
 * C++ approximation of Golang's io package, including interfaces such as
 * Reader, Writer, ReadWriter, etc. as abstract classes.
 */

#include <iostream>

using namespace std;

namespace io {
	class Writer {
		public:
		virtual ssize_t write (const void *src, const size_t len) = 0;//-- end size_t write
	};//-- enc class Writer

	class WriterTo {
		public:
		virtual ssize_t write_to (Writer& w) = 0;
	};//-- end class WriterTo

	class Reader {
		public:
		virtual ssize_t read (void *dest, const size_t len) = 0;//-- end size_t read
	};//-- end class Reader

	class ReaderFrom {
		public:
		virtual ssize_t read_from (Reader& r) = 0;
	};//-- end class ReaderFrom

	class Seeker {
		public:
		virtual ssize_t seek (const size_t offset, const int whence) = 0;
	};//-- end class Seeker

	class ReadWriter: public Reader, public Writer {};//-- end class ReadWriter

	ssize_t copy_n (Writer& dst, Reader& src, const size_t n) {
		const char *buffer = new char [n];
		ssize_t len = src.read((void *) buffer, n);
		len = dst.write(buffer, len);
		delete[] buffer;
		return len;
	}//-- end size_t copy_n

	class Buffer: public Writer, public WriterTo {
		protected:
		void *start;
		void *index;
		size_t cap;
		public:
		Buffer (void *dest, size_t len) {
			this->start = dest;
			this->index = dest;
			this->cap = len;
		}//-- end constructor
		
		ssize_t write (const void *src, const size_t len) {
			const size_t size = len < this->cap ? len : this->cap;
			memcpy(this->index, src, size);
			this->index = (char *) this->index + size;
			this->cap -= size;
			return size;
		}//-- end ssize_t write

		ssize_t write_to (Writer& w) {
			size_t len = ((char *) this->index - (char *) this->start);
			return w.write(this->start, len);
		}//-- end ssize_t write_to

		void reset () {
			this->cap += ((char *) this->index - (char *) this->start);
			this->index = this->start;
		}//-- end void reset
		
		ssize_t flush (Writer& w) {
			ssize_t n_written = this->write_to(w);
			this->reset();
			return n_written;
		}//-- end ssize_t flush
	};//-- end class Buffer
};//-- end namespace io

#endif

