#ifndef IO_HH
#define IO_HH

/**
 * @author Oliver Kelton, oakelton@gmail_com
 * @date May 21, 2019
 * C++ approximation of Golang's io package, including interfaces such as
 * Reader, Writer, ReadWriter, etc. as abstract classes.
 */

#include <iostream>
#include <stdio.h>

using namespace std;

namespace io {
	class Writer {
		public:
		virtual size_t write (void *src, size_t len) = 0;//-- end size_t write
	};//-- enc class Writer

	class WriterTo {
		public:
		virtual size_t write_to (Writer& w) = 0;
	};//-- end class WriterTo

	class Reader {
		public:
		virtual size_t read (void *dest, size_t len) = 0;//-- end size_t read
	};//-- end class Reader

	class ReaderFrom {
		public:
		virtual size_t read_from (Reader& r) = 0;
	};//-- end class ReaderFrom

	class Seeker {
		public:
		virtual size_t seek (size_t offset, int whence) = 0;
	};//-- end class Seeker

	class ReadWriter: public Reader, public Writer {};//-- end class ReadWriter

	size_t copy_n (Writer& dst, Reader& src, size_t n) {
		char *buffer = new char [n];
		size_t len = src.read(buffer, n);
		len = dst.write(buffer, len);
		delete[] buffer;
		return len;
	}//-- end size_t copy_n

	class File {
		protected:
		FILE *src;

		File (const char *name, const char *mode) {
			this->src = fopen(name, mode);
		}//-- end constructor

		public:
		~File () {
			fclose(this->src);
		}//-- end destructor
	};//-- end class File

	class RFile: public File, public Reader {
		public:
		RFile (const char *name) : File(name, "r") {}
		size_t read (void *dest, size_t len) {
			size_t n = fread(dest, 1, len, this->src);
			return n;
		}//-- end size_t read
	};//-- end class RFIile

	class WFile: public File, public Writer {
		public:
		WFile (const char *name): File(name, "w") {}
		size_t write (void *src, size_t len) {
			size_t n = fwrite(src, 1, len, this->src);
			return n;
		}//-- end size_t write
	};//-- end class WFile

	class RWFile: public File, public ReadWriter {
		public:
		RWFile (const char *name) : File(name, "rw") {}//-- end constructor
		size_t read (void *dest, size_t len) {
			size_t n = fread(dest, 1, len, this->src);
			return n;
		}//-- end size_t read
		size_t write (void *src, size_t len) {
			size_t n = fwrite(src, 1, len, this->src);
			return n;
		}//-- end size_t write
	};//-- end class RWFile
};//-- end namespace io

#endif

