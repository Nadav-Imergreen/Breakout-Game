#include "Frame.h"

#include "Ball.h"
#include "Paddle.h"

Frame::Frame(const sf::Vector2f& position, const sf::Vector2f& size, const FRAME_P& place)
	:StaticObject(position, size), m_place(place)
{
}

void Frame::handleCollision(GameObject& otherobj)
{
	otherobj.handleCollision(*this);
}

void Frame::handleCollision(Ball& ball)
{
	//change ball direction
	ball.setAngle(getPlace());
}

const FRAME_P& Frame::getPlace() const
{
	return m_place;
}


void Frame::handleCollision(Paddle& paddle)
{
	paddle.handleCollision(*this);
}
