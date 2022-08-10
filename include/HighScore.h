#pragma once
#include "Macros.h"
#include "Resources.h"
#include <fstream>


class HighScore
{
public:
	HighScore();

	void readTableFromFile();
	void readTableFromVector();
	void displayHighScore(sf::RenderWindow& window);
	void saveScoreInFile(std::string name, int score);

private:
	HighscoreVector m_table;	//vector of pairs <string, int> to hold high-score table
	std::vector <sf::Text> m_names;		//for names in high-score table
	std::vector <sf::Text> m_highRecords;	//for score in high-score table
	sf::Sprite m_sprite;

};