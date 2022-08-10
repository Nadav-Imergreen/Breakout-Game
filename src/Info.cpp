#include "Info.h"

Info::Info()
{
	//create and init text for game-info
	for (int i = 0; i < NUM_OF_INFO; i++)
	{
		sf::Text text(INFO_TEXTS[i], Resources::instance().getFont());
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition({ FIRST_INFO_TEXT_X + i * INFO_TEXT_W, INFO_TEXT_Y });
		m_texts.push_back(text);
	}
	//creat pause texture 
		sf::Sprite pause;
		pause.setTexture(Resources::instance().getTexture(TextureType::Pause));
		m_sprites.push_back(pause);

	//create volium texture
		sf::Sprite volume;
		volume.setTexture(Resources::instance().getTexture(TextureType::Volume));
		m_sprites.push_back(volume);

	//init pause and volium texturs
		for (int i = 0; i < NUM_OF_OPTIONS; i++)
		{
			m_sprites[i].setPosition({ float(WIN_W / 1.5) + 30 + ((WIN_W / 3) / NUM_OF_OPTIONS) * i , (INFO_H / 2) + 5 });
			m_sprites[i].setOrigin({ m_sprites[i].getGlobalBounds().width / 2 , m_sprites[i].getGlobalBounds().height / 2 });
			m_sprites[i].scale({ 75 / m_sprites[i].getGlobalBounds().width, 35 / m_sprites[i].getGlobalBounds().height });
		}

}

void Info::draw(sf::RenderWindow& window)
{
	updateTexts();	//update level num, score and life

	for (auto& text : m_texts)
		window.draw(text);

	for (auto& sprite : m_sprites)
		window.draw(sprite);
}


void Info::nextLevel()
{
	m_level++;
}

void Info::updateScore()
{
	m_score += 10;
}

int Info::getLives() const
{
	return m_lives;
}

void Info::updateLives()
{
	m_lives--;
}

void Info::restart()
{
	m_lives = 3;
	m_score = 0;
	m_level = 0;
}

void Info::handleClick(sf::RenderWindow& window, sf::Vector2f location)
{
	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		if (m_sprites[i].getGlobalBounds().contains(location))
		{
			switch (i)
			{
			case PAUSE:

				// use of animation
				if (m_pause)
				{
					m_sprites[i].setTexture(Resources::instance().getTexture(TextureType::Pause));
					m_pause = false;
				}
				else
				{
					m_sprites[i].setTexture(Resources::instance().getTexture(TextureType::Play));
					m_pause = true;
				}
				break;

			case VOLUME:

				// use of animation
				if (Resources::instance().getVolume())
				{
					m_sprites[i].setTexture(Resources::instance().getTexture(TextureType::Mute));
					Resources::instance().setVolume(false);
				}
				else
				{
					m_sprites[i].setTexture(Resources::instance().getTexture(TextureType::Volume));
					Resources::instance().setVolume(true);
				}
				break;

			default:
				break;
			}
		}
	}
}

void Info::handleMouseMoved(sf::RenderWindow& window, sf::Vector2f location)
{
	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		if (m_sprites[i].getGlobalBounds().contains(location))
			m_sprites[i].setColor(sf::Color::Yellow);

		else
			m_sprites[i].setColor(sf::Color::White);
	}
}

bool Info::isPause() const
{
	return m_pause;
}

void Info::addScore()
{
	m_score += 100;
}

void Info::addLife()
{
	m_lives += 1;
}

int Info::getScore() const
{
	return m_score;
}

void Info::updateTexts()
{
	//update level num, score and life

	m_texts[int(Information::Level)].setString(INFO_TEXTS[int(Information::Level)] + std::to_string(m_level));
	m_texts[int(Information::Score)].setString(INFO_TEXTS[int(Information::Score)] + std::to_string(m_score));
	m_texts[int(Information::Life)].setString(INFO_TEXTS[int(Information::Life)] + std::to_string(m_lives));
}
