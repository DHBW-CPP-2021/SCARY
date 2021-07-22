#ifndef HACKATHON_2021_DIRECTION_H
#define HACKATHON_2021_DIRECTION_H

namespace LabyrinthGame::Geo
{
	enum class Direction : short unsigned
	{
		left,
		right,
		up,
		down
	};

	[[nodiscard]] bool isVertical(Direction direction);
	[[nodiscard]] bool isHorizontal(Direction direction);

	[[nodiscard]] Direction oppositeDirection(Direction d);

} // namespace LabyrinthGame

#endif //HACKATHON_2021_DIRECTION_H
