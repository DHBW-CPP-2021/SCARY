#include "gtest/gtest.h"
#include "../../../LabyrinthGameLib/Utils/Utils.h"
#include "../../../LabyrinthGameLib/GameSettings.h"

using namespace LabyrinthGame;


TEST(testConversions, all) {
	for (unsigned short x = 0; x < GameSettings::WIDTH; x++)
	{
		for (unsigned short y = 0; y < GameSettings::HEIGHT; y++)
		{
			Geo::Coordinate input(x, y);
			GameSettings::CoordType oneD = Utils::compute1DFrom2D(input);
			Geo::Coordinate result = Utils::compute2DFrom1D(oneD);
			ASSERT_EQ(input, result);
		}
	}
}


