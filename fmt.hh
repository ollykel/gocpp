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

		typedef struct _Specifier {
			int flags;
			int width;
			int precision;
			int length;
			char type;
		} Specifier;

		size_t parse_specifier (Specifier *dest, const char *origin) {
			size_t n_read = 0;
			for (char *curr = origin; *curr != '\0' && !is_letter(*curr); ++curr) {
				// TODO: finish this
				++n_read;
			}//-- end for curr
			return n_read;
		}//-- end size_t parse_specifier

		size_t write_int (Writer &w, const int radix, int i) {
			char buf[128];
			char *out = buf + (sizeof(buf) - 1);
			size_t len = 0;
			bool is_neg = i < 0;
			if (is_neg) i = ~i + 1;
			int curr = 0;
			do {
				curr = i % radix;
				if (curr > 9) curr += NUM_LETTER_GAP;
				*out = '0' + (char) curr;
				i /= radix, --out, ++len;
			} while (i != 0); //-- end do while
			if (is_neg) {
				*out = '-';
				++len;
			} else {
				++out;
			}
			return (size_t) w.write(out, len);
		}//-- end size_t write_int

		size_t fmt_int (Writer& w, const char *specs, size_t specs_len, const int i) {
			int radix = 0;
			const char *lim = specs + specs_len;
			for (char *curr = specs; curr != lim || !is_digit(*curr); ++curr) {
				radix *= 10;
				radix += *curr - '0';
			}//-- end for curr
			if (!radix) radix = 10;
			return write_int(w, radix, i);
		}//-- end size_t fmt_int
	};//-- end private namespace

	size_t fprintf (io::Writer& w, const char* form...) {
		size_t w_len = 0;
		bool escaped = false, to_fmt = false;
		va_list args;
		va_start(args, form);
		for (char *curr = form; *curr != '\0'; ++curr) {
			if (!escaped && *curr == '%') {
				
			}
			if (*curr == '\\' && !escaped) {
				escaped = true;
			} else {
				escaped = false;
			}
			if ()
			++w_len;
		}//-- end for char *curr
		va_end(args);
	}//-- end size_t fprintf
};//-- end namespace fmt

#endif

