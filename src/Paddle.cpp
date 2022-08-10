#include "Paddle.h"
#include "Ball.h"
#include "Frame.h"
#include "ResizePaddleGift.h"
#include "FastPaddleGift.h"
#include "StrongBallGift.h"

Paddle::Paddle(const sf::Vector2f& position, const sf::Vector2f& size)
	:MovingObject(position, size, &Resources::instance().getTexture(TextureType::Paddle))
{
	m_paddleSpeed = PADDLE_SPEED;
}

void Paddle::move(const sf::Time& delta)
{
	m_sprite.move(m_direction * delta.asSeconds()* m_paddleSpeed);
	setStepSize(m_direction * delta.asSeconds() * m_paddleSpeed);
}

void Paddle::setDirection(const sf::Vector2f& direction)
{
	if(m_changeDir)                   //apply a gift that change keyboard direction
		m_direction = direction*-1.f;
	else
		m_direction = direction;
}

void Paddle::stop()
{
	m_sprite.move(-m_stepSize);
}

void Paddle::handleCollision(GameObject& otherobj)
{
	if (&otherobj == this) return;

	otherobj.handleCollision(*this);
}

void Paddle::handleCollision(Ball& ball)
{
	//if the game is not on mute mode - play collision sound
	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Paddle));
		m_sound.play();
	}

	ball.setAngle();
}

void Paddle::handleCollision(Frame& frame)
{
	stop();
}

void Paddle::handleCollision(ResizePaddleGift& resizePaddleGift)
{
	//if the game is not on mute mode - play collision sound
	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Gift));
		m_sound.play();
	}

	int increaseSize = rand() % 2;
	if (increaseSize)
		m_sprite.scale({ (PADDLE_SIZE.x + 50) / m_sprite.getGlobalBounds().width, PADDLE_SIZE.y / m_sprite.getGlobalBounds().height });
	else
		m_sprite.scale({ (PADDLE_SIZE.x - 50) / m_sprite.getGlobalBounds().width, PADDLE_SIZE.y / m_sprite.getGlobalBounds().height });

	//cancel previous gifts
	m_changeDir = false;
	m_paddleSpeed = PADDLE_SPEED;
	m_strongBall = false;
}

void Paddle::handleCollision(ChangeDirGift& changeDirGift)
{
	//if the game is not on mute mode - play collision sound
	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Gift));
		m_sound.play();
	}

	m_changeDir = true;

	//cancel previous gifts
	m_strongBall = false;
	m_paddleSpeed = PADDLE_SPEED;
	m_sprite.scale({ PADDLE_SIZE.x / m_sprite.getGlobalBounds().width, PADDLE_SIZE.y / m_sprite.getGlobalBounds().height });
}

void Paddle::handleCollision(FastPaddleGift& fastPaddleGift)
{
	//if the game is not on mute mode - play collision sound
	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Gift));
		m_sound.play();
	}

	m_paddleSpeed = PADDLE_SPEED + 50.f;

	//cancel previous gifts
	m_changeDir = false;
	m_sprite.scale({ PADDLE_SIZE.x / m_sprite.getGlobalBounds().width, PADDLE_SIZE.y / m_sprite.getGlobalBounds().height });
	m_strongBall = false;
}

void Paddle::handleCollision(StrongBallGift& strongBallGift)
{
	//if the game is not on mute mode - play collision sound
	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Gift));
		m_sound.play();
	}

	m_strongBall = true;
	
	//cancel previous gifts
	m_changeDir = false;
	m_paddleSpeed = PADDLE_SPEED;
	m_sprite.scale({ PADDLE_SIZE.x / m_sprite.getGlobalBounds().width, PADDLE_SIZE.y / m_sprite.getGlobalBounds().height });
}

void Paddle::handleCollision(AddScoreGift& addScoreGift)
{
	//if the game is not on mute mode - play collision sound
	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Gift));
		m_sound.play();
	}

	m_addScore = true;

	//cancel previous gifts
	m_strongBall = false;
	m_changeDir = false;
	m_paddleSpeed = PADDLE_SPEED;
	m_sprite.scale({ PADDLE_SIZE.x / m_sprite.getGlobalBounds().width, PADDLE_SIZE.y / m_sprite.getGlobalBounds().height });
}

void Paddle::handleCollision(AddLifeGift& addLifeGift)
{
	//if the game is not on mute mode - play collision sound
	if (Resources::instance().getVolume())
	{
		m_sound.setBuffer(Resources::instance().getSound(SoundType::Gift));
		m_sound.play();
	}

	m_addLife = true;

	//cancel previous gifts
	m_strongBall = false;
	m_changeDir = false;
	m_paddleSpeed = PADDLE_SPEED;
	m_sprite.scale({ PADDLE_SIZE.x / m_sprite.getGlobalBounds().width, PADDLE_SIZE.y / m_sprite.getGlobalBounds().height });
}


void Paddle::setStepSize(const sf::Vector2f& stepSize)
{
	m_stepSize = stepSize;
}

void Paddle::setPosition(sf::Vector2f position)
{
	m_position = position;
}

bool Paddle::addScore() const
{
	return m_addScore;
}

bool Paddle::addLife() const
{
	return m_addLife;
}

bool Paddle::isStrongBall() const
{
	return m_strongBall;
}

void Paddle::setGifts2false()
{
	m_addScore = false;
	m_addLife = false;
}