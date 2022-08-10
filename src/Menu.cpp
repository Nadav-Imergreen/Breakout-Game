#include "Menu.h"

Menu::Menu()
{

	m_sprite.setTexture(Resources::instance().getTexture(TextureType::Menu));

	//push the menu strings to the vector <text>
	for (int i = 0; i < NUM_OF_TEXTS; i++)
	{
		m_texts.push_back(sf::Text(MENU_TEXTS[i], Resources::instance().getFont()));
		m_texts[i].setOrigin(m_texts[i].getGlobalBounds().width / 2, m_texts[i].getGlobalBounds().height / 2);
		m_texts[i].setPosition({ WIN_W / 2, float(WIN_H / (NUM_OF_TEXTS + 1) * (i + 1.5)) });
	}
}

bool Menu::run(sf::RenderWindow& window)
{
	sf::Vector2f location;
	sf::Sound s;

	s.setBuffer(Resources::instance().getSound(SoundType::Menu));
	s.setVolume(SOUND_VOLUME);
	s.play();
	s.setLoop(true);

	while (window.isOpen())
	{
		window.clear();
		window.draw(m_sprite);						//draw menu back-graund and text
		for (int i = 0; i < NUM_OF_TEXTS; i++)
			window.draw(m_texts[i]);
		window.display();

		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				location = (sf::Vector2f)sf::Mouse::getPosition(window);
				for (int i = 0; i < NUM_OF_TEXTS; i++)
				{
					if (m_texts[i].getGlobalBounds().contains(location))
						m_texts[i].setFillColor(sf::Color::Red);
					else
						m_texts[i].setFillColor(sf::Color::Yellow);
				}
				break;

			case sf::Event::MouseButtonReleased:
				location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y});
				if (handleClick(window, location))
					return true;
			}
		}
	}
	return false;
}

void Menu::readTableFromFile()
{
	m_highScoreTable.readTableFromFile();
}

void Menu::readTableFromVector()
{
	m_highScoreTable.readTableFromVector();
}

void Menu::saveScoreInFile(std::string name, int score)
{
	m_highScoreTable.saveScoreInFile(name, score);
}

bool Menu::handleClick(sf::RenderWindow& window, const sf::Vector2f& location)
{
	for (int i = 0; i < NUM_OF_TEXTS; i++)
	{
		if (m_texts[i].getGlobalBounds().contains(location))
		{
			switch (i)
			{
			case START:
				return true;

			case HELP:
				help(window);
				m_sprite.setTexture(Resources::instance().getTexture(TextureType::Menu));
				window.clear();
				window.draw(m_sprite);
				window.display();
				break;

			case HIGH_SCORE:
				m_highScoreTable.displayHighScore(window);
				m_sprite.setTexture(Resources::instance().getTexture(TextureType::Menu));
				window.clear();
				window.draw(m_sprite);
				window.display();
				break;

			case EXIT:
				window.close();
				break;

			default:
				break;
			}
		}
	}
	return false;
}


void Menu::help(sf::RenderWindow& window)
{
	//display help back-ground and handle mouse clicks

	m_sprite.setTexture(Resources::instance().getTexture(TextureType::Help));

	window.clear();
	window.draw(m_sprite);
	window.display();

	while (window.isOpen())
	{
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonReleased:
				auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (location.x < 200 && location.y > 600)
					return;
			}
		}
	}
}

sf::Text Menu::getPlayerName(char letter, int gap)
{
	sf::Text name;

	name.setFont(Resources::instance().getFont());
	name.setString(letter);
	name.setPosition(495 + gap * 20, 100);
	name.setCharacterSize(42);
	name.setFillColor(sf::Color::Green);
	name.setStyle(sf::Text::Bold);

	return name;
}
