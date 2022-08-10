#pragma once
#include "Macros.h"
#include "Resources.h"
#include "HighScore.h"

class Menu {
public:
	Menu();

	bool run(sf::RenderWindow& window);

	void readTableFromFile();
	void readTableFromVector();
	void saveScoreInFile(std::string name, int score);
	sf::Text getPlayerName(char, int);

private:
	
	bool handleClick(sf::RenderWindow& window, const sf::Vector2f& location);
	void help(sf::RenderWindow& window);

	std::vector <sf::Text> m_texts;		//for text lines in menu
	HighScore m_highScoreTable;
	sf::Sprite m_sprite;

};