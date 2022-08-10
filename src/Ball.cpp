#include "Ball.h"
#include "Paddle.h"
#include "Frame.h"
#include "Brick.h"

Ball::Ball(const sf::Vector2f& position, const sf::Vector2f& size)
	:MovingObject(position, size, &Resources::instance().getTexture(TextureType::Ball)),
	m_angle(0.0f), m_ballSpeed(0.0f), m_dir(0, -1)
{
}

void Ball::move(const sf::Time& delta)
{
	m_sprite.move(m_dir * m_ballSpeed * delta.asSeconds());
}

void Ball::setAngle(const FRAME_P& place)
{
	// if ball hits the frames - change ball direction accordingly

	switch (place)
	{
	case FRAME_P::LEFT_P:
		m_dir.x *= -1;
		break;
	case FRAME_P::RIGHT_P:
		m_dir.x *= -1;
		break;
	case FRAME_P::UP_P:
		m_dir.y *= -1;
		break;
	case FRAME_P::PADDALE_P:
		m_dir.y *= -1;
		break;
	default:
		break;
	}
}

void Ball::setAngle()
{
	//when start the game - set baal starting angle and speed

	m_ballSpeed = BALL_SPEED;
	
	m_angle = ((rand() % 150) * (PI / 180));
	m_dir.x = cos(m_angle) * m_ballSpeed;
	m_dir.y = -(sin(m_angle) * m_ballSpeed);
}

void Ball::setDirection(const sf::Vector2f& dir)
{
	m_dir = dir;
}

void Ball::setStrongBall(const bool& strongBall)
{
	m_strongBall = strongBall;
}

void Ball::handleCollision(GameObject& otherobj)
{
	otherobj.handleCollision(*this);
}

void Ball::handleCollision(Paddle& paddle)
{
	setAngle(FRAME_P::PADDALE_P);
}

void Ball::handleCollision(Frame& frame)
{
	if (isBlocked())
	{
		frame.handleCollision(*this);
		setBlock(false);
	}

	//if the game is not on mute mode - play collision sound

	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Wall));
		m_sound.play();
	}
}

void Ball::handleCollision(Brick& brick)
{
	//if the game is not on mute mode - play collision sound

	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Brick));
		m_sound.play();
	}
	
	if (!m_strongBall)	//check if the "strong-ball gift" is on
	{
		auto  ballRect = getGlobalBounds();
		float ballWidth = ballRect.width;
		float ballHeight = ballRect.height;
		float ballLeft = ballRect.left;
		float ballTop = ballRect.top;

		// Create four contact points for the ball
		sf::Vector2f ballLeftPoint(ballLeft, ballTop + (ballHeight / 2.f));					// Middle of left side
		sf::Vector2f ballRightPoint(ballLeft + ballWidth, ballTop + (ballHeight / 2.f));	// Middle of right side
		sf::Vector2f ballTopPoint(ballLeft + (ballWidth / 2.f), ballTop);					// Middle of top
		sf::Vector2f ballBottomPoint(ballLeft + (ballWidth / 2.f), ballTop + ballHeight);	// Middle of bottom

		// If contact is on the left or right of the ball, adjust angle properly
		if (brick.getGlobalBounds().contains(ballLeftPoint) || brick.getGlobalBounds().contains(ballRightPoint))
			m_dir.x *= -1;

		// If contact is on the top or top of the ball, adjust angle properly
		else if (brick.getGlobalBounds().contains(ballTopPoint) || brick.getGlobalBounds().contains(ballBottomPoint))
			m_dir.y *= -1;
	}

	brick.handleCollision(*this);
}

bool Ball::isBlocked()
{
	if (m_clock.getElapsedTime().asMilliseconds() > 50)
		m_blocked = true;
	return m_blocked;
}

void Ball::setBlock(bool block)
{
	if (!block)
		m_clock.restart();
	m_blocked = block;
}
