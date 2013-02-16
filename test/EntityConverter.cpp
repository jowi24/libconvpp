/*
 * HttpClient.cpp
 *
 *  Created on: 18.01.2013
 *      Author: jo
 */


#include "gtest/gtest.h"

#include <libconv++/EntityConverter.h>

namespace test {

class EntityConverter : public ::testing::Test  {
public:

	EntityConverter()
	{};

	void SetUp() {
	}
};

TEST(EntityConverter, ConvertEntitiesUTF) {
	ASSERT_STREQ("TestÄTestä", convert::EntityConverter::DecodeEntities("Test&#xC4;Test&#xE4;").c_str());
}

TEST(EntityConverter, ConvertEntities) {
	ASSERT_STREQ("TestÄTestä", convert::EntityConverter::DecodeEntities("Test&Auml;Test&auml;").c_str());
}


}


