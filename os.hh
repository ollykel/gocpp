#ifndef OS_HH
#define OS_HH

/**
 * @author Oliver Kelton, oakelton@gmail_com
 * @date May 21, 2019
 * Implements file handling systems, etc. Based on Golang os package.
 */

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include "io.hh"

using namespace std;

namespace os {
	static const mode_t DEF_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	static const int STD_WFLAGS = O_CREAT | O_DSYNC;

	class File {
		protected:
		int fdes;

		File (const int fdes) {
			this->fdes = fdes;
		}//-- end constructor 1
		
		File (const char *name, const int flags, const mode_t mode) {
			if (mode) {
				this->fdes = open(name, flags, mode);
			} else {
				this->fdes = open(name, flags);
			}
		}//-- end constructor 2

		public:
		int close () {
			return ::close(this->fdes);
		}//-- end int cose

		int fd () {
			return this->fdes;
		}//-- end int fd
	};//-- end class File

	class RFile: public File, public io::Reader {
		protected:
		RFile (const int fdes) : File(fdes) {}
		public:
		RFile (const char *name) : File(name, O_RDONLY, 0) {}
		ssize_t read (void *dest, const size_t len) {
			return ::read(this->fdes, dest, len);
		}//-- end size_t read
	};//-- end class RFIile

	class WFile: public File, public io::Writer {
		protected:
		WFile (const int fdes) : File(fdes) {}
		public:
		WFile (const char *name) : File(name, O_WRONLY | STD_WFLAGS | O_TRUNC, DEF_MODE) {}
		ssize_t write (const void *src, const size_t len) {
			return ::write(this->fdes, src, len);
		}//-- end size_t write
	};//-- end class WFile

	class RWFile: public File, public io::ReadWriter {
		public:
		RWFile (const char *name) : File(name, O_RDWR | STD_WFLAGS | O_TRUNC, DEF_MODE) {}
		ssize_t read (void *dest, const size_t len) {
			return ::read(this->fdes, dest, len);
		}//-- end size_t read
		ssize_t write (const void *src, const size_t len) {
			return ::write(this->fdes, src, len);
		}//-- end size_t write
	};//-- end class RWFile

	class AFile: public File, public io::Writer {
		public:
		AFile (const char *name) : File(name, O_WRONLY | STD_WFLAGS | O_APPEND, 0) {}
		ssize_t write (const void *src, const size_t len) {
			return ::write(this->fdes, src, len);
		}//-- end size_t write
	};//-- end class AFile
	
	namespace {
		class StdRFile: public RFile {
			public:
			StdRFile (const int fdes) : RFile(fdes) {}
		};//-- end static class StdRFile

		class StdWFile: public WFile {
			public:
			StdWFile (const int fdes) : WFile(fdes) {}
		};//-- end class StdWFile
	};//-- end anonymous namespace

	// Standard Files
	RFile in = StdRFile(0);
	WFile out = StdWFile(1);
	WFile err = StdWFile(2);
};//-- end namespace os

#endif

