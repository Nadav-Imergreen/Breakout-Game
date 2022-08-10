#pragma once
#include "Resources.h"

class Info {
public:
	Info();

	void draw(sf::RenderWindow& window);
	void nextLevel();
	void updateScore();
	int getLives() const;
	void updateLives();
	void restart();
	void handleClick(sf::RenderWindow& window, sf::Vector2f location);
	void handleMouseMoved(sf::RenderWindow& window, sf::Vector2f location);
	bool isPause() const;
	void addScore();
	void addLife();
	int getScore() const;


private:
	void updateTexts();

	int m_lives = 3;
	int m_level = 0;
	int m_score = 0;
	std::vector<sf::Text> m_texts;
	std::vector<sf::Sprite> m_sprites;
	bool m_pause = false;
};