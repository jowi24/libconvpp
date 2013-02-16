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

#ifndef ENTITYCONVERTER_H_
#define ENTITYCONVERTER_H_

#include <string>

namespace convert {

class EntityConverter {
public:
	static std::string DecodeEntities(const std::string &s);
};

} /* namespace convert */

#endif /* ENTITYCONVERTER_H_ */
