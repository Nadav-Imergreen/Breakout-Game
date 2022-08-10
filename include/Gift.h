#pragma once
#include "StaticObject.h"


class Gift : public StaticObject
{
public:
	Gift(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture);

	void fall(sf::Time delta);
	void setGiftBrickHit();
	bool isBrickBroke() const;

	virtual void handleCollision(Frame& frame) override { }
	virtual void handleCollision(GameObject& otherobj) override { }
	virtual void handleCollision(Ball& ball) override { }
	virtual void handleCollision(Brick& brick) override { }
	virtual void handleCollision(ResizePaddleGift& resizePaddleGift) override { }
	virtual void handleCollision(ChangeDirGift& changeDirGift) override { }
	virtual void handleCollision(FastPaddleGift& fastPaddleGift) override { }
	virtual void handleCollision(StrongBallGift& strongBallGift) override { }
	virtual void handleCollision(AddScoreGift& addScoreGift) override { }
	virtual void handleCollision(AddLifeGift& addLifeGift) override { }


private:
	bool m_giftBrickHit = false;		//to know if the ball hits the brick of a gift
};