#pragma once
#include "Macros.h"
#include "Resources.h"


class Paddle;
class Ball;
class Frame;
class Brick;
class ResizePaddleGift;
class ChangeDirGift;
class FastPaddleGift;
class StrongBallGift;
class AddScoreGift;
class AddLifeGift;



class GameObject 
{
public:
	GameObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture);
	GameObject(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~GameObject() = default;

	void drawSprite(sf::RenderWindow& window) const;
	void drawRect(sf::RenderWindow& window) const;
	void setPosition(sf::Vector2f position);
	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getGlobalBoundsRect() const;
	bool collideWith(const GameObject& otherobj) const;
	bool collideWithRect(const GameObject& otherobj) const;
	sf::Vector2f getPosition() const;

	virtual void handleCollision(GameObject& otherobj) = 0;
	virtual void handleCollision(Brick& otherobj) = 0;
	virtual void handleCollision(Paddle& otherobj) = 0;
	virtual void handleCollision(Ball& otherobj) = 0;
	virtual void handleCollision(Frame& otherobj) = 0;
	virtual void handleCollision(ResizePaddleGift& otherobj) = 0;
	virtual void handleCollision(ChangeDirGift& otherobj) = 0;
	virtual void handleCollision(FastPaddleGift& otherobj) = 0;
	virtual void handleCollision(StrongBallGift& otherobj) = 0;
	virtual void handleCollision(AddScoreGift& otherobj) = 0;
	virtual void handleCollision(AddLifeGift& otherobj) = 0;


protected:
	sf::Sprite m_sprite;		//for all the objects in the game

private:
	sf::RectangleShape m_rect;		//for frames of the board
	
};