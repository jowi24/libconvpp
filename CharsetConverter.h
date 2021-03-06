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

#include <stdexcept>

#include <iconv.h>

namespace convert {

class CharsetConverter {
private:
	iconv_t conv;
	bool ignoreError;
public:
	CharsetConverter(const std::string& fromEncoding, const std::string& toEncoding = "", bool ignoreError = true);
	~CharsetConverter();
	std::string convert(const std::string& input) const;
	static std::string GetDefaultCharset();
	static std::string ConvertToLocalEncoding(const std::string &input, const std::string &encoding);
};

}
