/**
 * @author Oliver Kelton, oakelton@gmail.com
 * @date <DATETIME>
 * <DESCRIPTION>
 */

#include <iostream>
#include <string.h>

#include "../io.hh"
#include "../os.hh"

#define TEST_FILE_A "./test_a.txt"
#define TEST_FILE_B "./test_b.txt"

using namespace std;

bool test_buffer () {
	cerr << "Testing buffer:\n";
	const size_t buf_len = 100;
	char dest[buf_len];
	io::Buffer buf = io::Buffer(dest, buf_len);
	os::RFile input = os::RFile(TEST_FILE_A);
	io::copy_n(buf, input, 20);
	input.close();
	const char *str = "\n'Ello world!\n";
	const size_t len = strlen(str);
	buf.write(str, len);
	buf.flush(os::out);
	cerr << "Done testing buffer\n";
	return false;
}//-- end test_buffer

int main (const int argc, const char **argv) {
	cerr << "Testing io.hh:\n";
	os::RFile input = os::RFile(TEST_FILE_A);
	ssize_t n_read = io::copy_n(os::out, input, 100);
	cerr << "N read: " << n_read << "\n";
	input.close();
	bool failed = test_buffer();
	cerr << "Test failed? " << failed << "\n";
	return 0;
}//-- end int main


