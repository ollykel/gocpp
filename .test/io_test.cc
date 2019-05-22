/**
 * @author Oliver Kelton, oakelton@gmail.com
 * @date <DATETIME>
 * <DESCRIPTION>
 */

#include <iostream>
#include "../io.hh"
#include "../os.hh"

#define TEST_FILE_A "./test_a.txt"
#define TEST_FILE_B "./test_b.txt"

using namespace std;

int main (const int argc, const char **argv) {
	cerr << "Testing io.hh:\n";
	os::RFile input = os::RFile(TEST_FILE_A);
	os::WFile output = os::WFile(TEST_FILE_B);
	ssize_t n_read = io::copy_n(os::out, input, 10);
	cerr << "N read: " << n_read << "\n";
	input.close();
	output.close();
	return 0;
}//-- end int main


