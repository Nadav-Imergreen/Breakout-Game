#pragma once
#include "MovingObject.h"


class Paddle: public MovingObject
{
public:
	Paddle(const sf::Vector2f& position, const sf::Vector2f& size);

	void move(const sf::Time& delta) override;
	void setDirection(const sf::Vector2f& direction);
	void stop();
	void setStepSize(const sf::Vector2f& stepSize);
	void setPosition(sf::Vector2f position);
	bool addScore() const;
	bool addLife() const;
	bool isStrongBall() const;
	void setGifts2false();
	
	virtual void handleCollision(GameObject& otherobj) override;
	virtual void handleCollision(Brick& brick) override { }
	virtual void handleCollision(Paddle& paddle) override { }
	virtual void handleCollision(Ball& ball) override;
	virtual void handleCollision(Frame& frame) override;
	virtual void handleCollision(ResizePaddleGift& resizePaddleGift) override;
	virtual void handleCollision(ChangeDirGift& changeDirGift) override;
	virtual void handleCollision(FastPaddleGift& fastPaddleGift) override;
	virtual void handleCollision(StrongBallGift& strongBallGift) override;
	virtual void handleCollision(AddScoreGift& addScoreGift) override;
	virtual void handleCollision(AddLifeGift& addLifeGift) override;
	

private:
	sf::Vector2f m_direction = STOPED;
	sf::Vector2f m_stepSize;
	sf::Vector2f m_position;
	bool m_changeDir = false;
	bool m_addScore = false;
	bool m_addLife = false;
	bool m_strongBall = false;
	float m_paddleSpeed;
};