#pragma once
#include "StaticObject.h"



class Frame :public StaticObject
{
public:
	Frame(const sf::Vector2f& position, const sf::Vector2f& size, const FRAME_P& place);

	const FRAME_P& getPlace() const;

	virtual void handleCollision(GameObject& otherobj) override;
	virtual void handleCollision(Paddle& paddle) override;
	virtual void handleCollision(Ball& ball) override;
	virtual void handleCollision(Brick& brick) override { }
	virtual void handleCollision(ResizePaddleGift& resizePaddleGift) override { }
	virtual void handleCollision(ChangeDirGift& changeDirGift) override { }
	virtual void handleCollision(FastPaddleGift& fstPaddleGift) override { }
	virtual void handleCollision(StrongBallGift& strongBallGift) override { }
	virtual void handleCollision(AddScoreGift& addScoreGift) override { }
	virtual void handleCollision(AddLifeGift& addLifeGift) override { }


private:
	FRAME_P m_place;
};