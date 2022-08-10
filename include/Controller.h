#pragma once

#include <fstream>
#include <exception>
#include "Macros.h"
#include "Board.h"
#include "Menu.h"


class Controller {

public:
	Controller();

	void run();
	
private:
	bool runLevel();
	bool readLevel();
	void handleEvent(sf::Keyboard::Key key);
	void endGame(const TextureType &texture, const SoundType &sound);
	void restart();
	void playreName(sf::Text&);

	std::ifstream m_file;	//for board map
	sf::RenderWindow m_window;
	Menu m_menu;
	Board m_board;
	std::vector<std::vector<char>> m_map;	//vector to hold board map
	sf::Vector2i m_size;
	sf::Sprite m_sprite;
	bool m_firstServe = true;		//bool to recegnise first serve in game

};