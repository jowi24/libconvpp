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

#include "EntityConverter.h"

#include <map>
#include <sstream>
#include <string.h>

#include "CharsetConverter.h"

namespace convert {

const std::map<std::string, std::string> Entities = {
	{"&nbsp;",  " "},
	{"&iexcl;", "¡"},
	{"&cent;",  "¢"},
	{"&pound;", "£"},
	{"&curren;","€"}, //krazy:exclude=spelling
	{"&yen;",   "¥"},
	{"&brvbar;","Š"},
	{"&sect;",  "§"},
	{"&uml;",   "š"},
	{"&copy;",  "©"},
	{"&ordf;",  "ª"},
	{"&laquo;", "«"},
	{"&not;",   "¬"},
	{"&shy;",   "­"},
	{"&reg;",   "®"},
	{"&macr;",  "¯"},
	{"&deg;",   "°"},
	{"&plusmn;","±"},
	{"&sup2;",  "²"},
	{"&sup3;",  "³"},
	{"&acute;", "Ž"},
	{"&micro;", "µ"},
	{"&para;",  "¶"},
	{"&middot;","·"},
	{"&cedil;", "ž"},
	{"&sup1;",  "¹"},
	{"&ordm;",  "º"},
	{"&raquo;", "»"},
	{"&frac14;","Œ"},
	{"&frac12;","œ"},
	{"&frac34;","Ÿ"},
	{"&iquest;","¿"},
	{"&Agrave;","À"},
	{"&Aacute;","Á"},
	{"&Acirc;", "Â"},
	{"&Atilde;","Ã"},
	{"&Auml;",  "Ä"},
	{"&Aring;", "Å"},
	{"&AElig;", "Æ"},
	{"&Ccedil;","Ç"},
	{"&Egrave;","È"},
	{"&Eacute;","É"},
	{"&Ecirc;", "Ê"},
	{"&Euml;",  "Ë"},
	{"&Igrave;","Ì"},
	{"&Iacute;","Í"},
	{"&Icirc;", "Î"},
	{"&Iuml;",  "Ï"},
	{"&ETH;",   "Ð"},
	{"&Ntilde;","Ñ"},
	{"&Ograve;","Ò"},
	{"&Oacute;","Ó"},
	{"&Ocirc;", "Ô"},
	{"&Otilde;","Õ"},
	{"&Ouml;",  "Ö"},
	{"&times;", "×"},
	{"&Oslash;","Ø"},
	{"&Ugrave;","Ù"},
	{"&Uacute;","Ú"},
	{"&Ucirc;", "Û"},
	{"&Uuml;",  "Ü"},
	{"&Yacute;","Ý"},
	{"&THORN;", "Þ"},
	{"&szlig;", "ß"},
	{"&agrave;","à"},
	{"&aacute;","á"},
	{"&acirc;", "â"},
	{"&atilde;","ã"},
	{"&auml;",  "ä"},
	{"&aring;", "å"},
	{"&aelig;", "æ"},
	{"&ccedil;","ç"},
	{"&egrave;","è"},
	{"&eacute;","é"},
	{"&ecirc;", "ê"},
	{"&euml;",  "ë"},
	{"&igrave;","ì"},
	{"&iacute;","í"},
	{"&icirc;", "î"},
	{"&iuml;",  "ï"},
	{"&eth;",   "ð"},
	{"&ntilde;","ñ"},
	{"&ograve;","ò"},
	{"&oacute;","ó"},
	{"&ocirc;", "ô"},
	{"&otilde;","õ"},
	{"&ouml;",  "ö"},
	{"&divide;","÷"},
	{"&oslash;","ø"},
	{"&ugrave;","ù"},
	{"&uacute;","ú"},
	{"&ucirc;", "û"},
	{"&uuml;",  "ü"},
	{"&yacute;","ý"},
	{"&thorn;", "þ"},
	{"&yuml;",  "ÿ"},
	{"&amp;",   "&"},
};

std::string EntityConverter::DecodeEntities(const std::string &input) {
	std::string output = input;
	if (output.find("&") != std::string::npos) {
		// convert the entities from UTF-8 to current system character table
		CharsetConverter conv("UTF-8");

		// convert entities of format &#xFF; (unicode)
		while (output.find("&#x") != std::string::npos) {
			size_t pos = output.find("&#x");
			size_t end = output.find(";", pos);
			// get hex code
			std::string unicode = output.substr(pos+3, end - pos - 3);
			// convert to int
			std::stringstream ss;
			ss << std::hex << unicode;
			int codepoint;
			ss >> codepoint;
			// get corresponding char
			char out_buffer[8];
			memset(out_buffer, 0, 8);
			char *out = &(out_buffer[0]);
			wchar_t in_buffer = codepoint;
			char *in = (char *)&(in_buffer);
			size_t inlen = sizeof(in_buffer), outlen = sizeof(out_buffer);
			iconv_t cd;
			cd = iconv_open("utf-8", "ucs-2");
			iconv(cd, &in, &inlen, &out, &outlen);
			iconv_close(cd);
			// replace it
			output.replace(pos, end-pos+1, std::string(out_buffer));
		}

		// convert other entities with table
		for (auto entity : Entities) {
			std::string::size_type pos = output.find(entity.first);
			while (pos != std::string::npos) {
				output.replace(pos, entity.first.length(), conv.convert(entity.second));
				pos = output.find(entity.first, pos-1);
			}
		}
	}
	return output;
}


} /* namespace convert */
