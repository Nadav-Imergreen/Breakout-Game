#pragma once

#include "Macros.h"
#include "Paddle.h"
#include "Ball.h"
#include "Frame.h"
#include "Brick.h"
#include "GiftBrick.h"
#include "Info.h"
#include "Gift.h"
#include "ResizePaddleGift.h"
#include "ChangeDirGift.h"
#include "FastPaddleGift.h"
#include "StrongBallGift.h"
#include "AddScoreGift.h"
#include "AddLifeGift.h"


using LevelMap = std::vector<std::vector<char>>;

class Board {
public:
	Board();
	void draw(sf::RenderWindow& window);
	void setPaddleDirection(sf::Vector2f dir);
	void setBallAngle();
	bool update(const sf::Time& delta);
	void loadLevel(const LevelMap& map, const sf::Vector2i& size);
	void nextLevel();
	const LevelSituation& levelLost();
	void init();
	void restartInfo();
	bool isPause() const;
	void handleClick(sf::RenderWindow& window, sf::Vector2f location);
	void handleMouseMoved(sf::RenderWindow& window, sf::Vector2f location);
	int getScore() const;

private:
	void move(MovingObject& obj, const sf::Time& delta);
	
	std::unique_ptr<Paddle> m_paddle;
	std::unique_ptr<Ball> m_ball;
	std::vector<std::unique_ptr <Frame>> m_frames;
	std::vector<std::unique_ptr <Brick>> m_bricks;
	std::vector<std::unique_ptr <Gift>> m_gifts;
	Info m_info;
};