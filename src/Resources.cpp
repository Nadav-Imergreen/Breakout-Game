#include "Resources.h"

Resources& Resources::instance()
{
	static Resources r;
	return r;
}

Resources::Resources()
{
	try
	{
		buildTextures();
		buildSounds();
		m_font.loadFromFile(FONT_PATH);
	}
	catch (const std::exception ex)
	{
		std::cerr << "Uneble to loadFromFile because " << ex.what() << std::endl;
		
	}
}

sf::Texture& Resources::getTexture(TextureType type)
{
	return m_textures[int(type)];
}

sf::Font& Resources::getFont()
{
	return m_font;
}

sf::SoundBuffer& Resources::getSound(SoundType type)
{
	return m_sounds[int(type)];
}

bool Resources::getVolume() const
{
	return m_volume;
}

void Resources::setVolume(bool volume)
{
	m_volume = volume;
}

void Resources::buildTextures()
{
	for (int i = 0; i < NUM_OF_TEXTURES; i++)
	{
		sf::Texture t;
		t.loadFromFile(TEXTURES[i]);
		m_textures.push_back(t);
	}
}

void Resources::buildSounds()
{
	for (int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		sf::SoundBuffer s;
		s.loadFromFile(SOUNDS[i]);
		m_sounds.push_back(s);
	}
}
