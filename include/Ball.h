#pragma once
#include "MovingObject.h"
 
 
class Ball : public MovingObject
{
public:
	Ball(const sf::Vector2f& position, const sf::Vector2f& size);

	void move(const sf::Time& delta) override;
	void setAngle(const FRAME_P& place);
	void setAngle();
	void setDirection(const sf::Vector2f& dir);
	void setStrongBall(const bool& strongBall);
	

	virtual void handleCollision(GameObject& otherobj) override;
	virtual void handleCollision(Paddle& paddle) override;
	virtual void handleCollision(Ball& ball) { }
	virtual void handleCollision(Frame& frame) override;
	virtual void handleCollision(Brick& brick) override;
	virtual void handleCollision(ResizePaddleGift& resizePaddleGift) override { }
	virtual void handleCollision(ChangeDirGift& changeDirGift) override { }
	virtual void handleCollision(FastPaddleGift& fastPaddleGift) override { }
	virtual void handleCollision(StrongBallGift& strongBallGift) override { }
	virtual void handleCollision(AddScoreGift& addScoreGift) override { }
	virtual void handleCollision(AddLifeGift& addLifeGift) override { }

private:
	bool isBlocked();
	void setBlock(bool block);

	sf::Vector2f m_dir;
	float m_angle;
	float m_ballSpeed;
	bool m_strongBall = false;
	sf::Clock m_clock;
	bool m_blocked = true;
};