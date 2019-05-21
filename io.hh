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
		virtual size_t write (void *src, size_t len) = 0;//-- end size_t write
	};//-- enc class Writer

	class Reader {
		public:
		virtual size_t read (void *dest, size_t len) = 0;//-- end size_t read
	};//-- end class Reader

	class ReadWriter: public Reader, public Writer {};//-- end class ReadWriter
};//-- end namespace io

#endif

