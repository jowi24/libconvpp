/*
 * HttpClient.cpp
 *
 *  Created on: 18.01.2013
 *      Author: jo
 */


#include "gtest/gtest.h"

#include <libconv++/CharsetConverter.h>

namespace test {

class CharsetConverter : public ::testing::Test  {
public:

	const std::string input_iso_8859_15 = "Test\xC4\xD6\xDC\xE4\xF6\xFC\xDF\xA4-";
	const std::string input_utf_8 = "Test\xC3\x84\xC3\x96\xC3\x9C\xC3\xA4\xC3\xB6\xC3\xBC\xC3\x9F\xE2\x82\xAC-";

	CharsetConverter()
	{};

	void SetUp() {
	}
};

TEST_F(CharsetConverter, Convert8859ToUTF8) {
	convert::CharsetConverter conv("ISO-8859-15", "UTF-8");
	std::string output = conv.convert(input_iso_8859_15);
	ASSERT_STREQ(input_utf_8.c_str(), output.c_str());
}

TEST_F(CharsetConverter, Convert8859ToLocal) {
	std::string output = convert::CharsetConverter::ConvertToLocalEncoding(input_iso_8859_15, "ISO-8859-15");
	std::string expected = convert::CharsetConverter::ConvertToLocalEncoding(input_utf_8, "UTF-8");
	ASSERT_STREQ(expected.c_str(), output.c_str());
}



}


