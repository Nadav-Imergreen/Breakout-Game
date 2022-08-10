#pragma once
#include "StaticObject.h"


class Brick : public StaticObject
{
public:
	Brick(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, int maxCounter = 1);

	virtual void handleCollision(GameObject& otherobj) override;
	virtual void handleCollision(Brick& brick) override { }
	virtual void handleCollision(Paddle& paddle) override { }
	virtual void handleCollision(Ball& ball) override;
	virtual void handleCollision(Frame& frame) override { }
	virtual void handleCollision(ResizePaddleGift& resizePaddleGift) override { }
	virtual void handleCollision(ChangeDirGift& changeDirGift) override { }
	virtual void handleCollision(FastPaddleGift& fastPaddleGift) override { }
	virtual void handleCollision(StrongBallGift& strongBallGift) override { }
	virtual void handleCollision(AddScoreGift& addScoreGift) override { }
	virtual void handleCollision(AddLifeGift& addLifeGift) override { }

	
	bool isDamaged() const;

private:
	bool isMaxHits() const;

	int m_hitCounter = 1;
	int m_maxHitCounter;
	bool m_damaged = false;

};