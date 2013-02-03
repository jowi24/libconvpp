/*
 * libiconv++
 *
 * Copyright (C) 2012-2013 Joachim Wilke <libiconv@joachim-wilke.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "CharsetConverter.h"

#include <iconv.h>
#include <langinfo.h>
#include <sys/types.h>

#include <vector>

namespace convert {

CharsetConverter::CharsetConverter(const std::string& fromEncoding, const std::string& toEncoding, bool ignoreError)
: ignoreError{ignoreError} {
	conv = iconv_open(toEncoding.length() ? toEncoding.c_str() : getDefaultCharset().c_str(), fromEncoding.c_str());
	if (conv == (iconv_t)-1) {
		if (errno == EINVAL)
			throw std::runtime_error("Unsupported conversion from " + toEncoding + " to " + fromEncoding);
		else
			throw std::runtime_error("Unknown error initializing converter.");
	}
}

CharsetConverter::~CharsetConverter() {
	iconv_close(conv);
}

std::string CharsetConverter::convert(const std::string& input) const {
	std::vector<char> inputBuffer(input.begin(), input.end());
	char* srcPtr = &inputBuffer[0];
	size_t srcSize = input.size();

	std::vector<char> buf(2048);
	std::string output;
	while (0 < srcSize) {
		char* dstPtr = &buf[0];
		size_t dstSize = buf.size();
		size_t res = iconv(conv, &srcPtr, &srcSize, &dstPtr, &dstSize);
		if (res == (size_t)-1) {
			if (errno == E2BIG)  {
				// ignore this error
			} else if (ignoreError) {
				// skip character
				++srcPtr;
				--srcSize;
			} else {
				switch (errno) {
				case EILSEQ:
				case EINVAL:
					throw std::runtime_error("Invalid multibyte chars.");
				default:
					throw std::runtime_error("Unknown error initializing converter.");
				}
			}
		}
		output.append(&buf[0], buf.size() - dstSize);
	}
	return output;
}

std::string CharsetConverter::ConvertToLocalEncoding(const std::string &input, const std::string &encoding)  {
	CharsetConverter c(encoding);
	return c.convert(input);
}


std::string CharsetConverter::getDefaultCharset() {
	if (setlocale(LC_CTYPE, ""))
		return nl_langinfo(CODESET);
	char *langPtr = getenv("LANG");
	if (langPtr) {
		std::string lang(langPtr);
		size_t pos = lang.find('.');
		if (pos == std::string::npos)
			return lang;
		return lang.substr(pos+1);
	}
	return "UTF-8";
}

} /* namespace logger */
