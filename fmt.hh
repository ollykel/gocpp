#ifndef FMT_HH
#define FMT_HH

/**
 * @author Oliver Kelton, oakelton@gmail_com
 * @date May 22, 2019
 * Analog to Golang's fmt package.
 */

#include <iostream>
#include <cstdarg>

#include "io.hh"

using namespace std;

namespace fmt {
	namespace {
		const int NUM_LETTER_GAP = 'A' - '9';

		bool is_letter (char c) {
			return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
		}//-- end bool is_letter

		bool is_digit (char c) {
			return c >= '0' && c <= '9';
		}//-- end bool is_number
};//-- end namespace fmt

#endif

