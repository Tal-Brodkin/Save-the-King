#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "io.h"

//-------------------------------------------------------------
// Resources class - a singlton class holding the textures,
// sounds, file, menu options... etc
//-------------------------------------------------------------


class Resources
{
private:

	std::vector<std::string> m_levels;		//vector of all the levels
	std::vector<sf::Texture> m_textures;	//vector of textures
	std::vector<sf::SoundBuffer> m_buffer;	//vector of soundbuffer
	std::vector<sf::Sound> m_sounds;		//vector of sounds
	std::vector<sf::Font> m_font;			//vector of fonts

	std::vector<std::string> m_menu_options;

	float m_level_duration;

	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	std::vector<std::string> makeNamesVector(const char[]) const;
	std::vector<sf::Texture> makeTexturesVector(const std::vector<std::string>&) const;
	std::vector<sf::SoundBuffer> makeBufferVector(const std::vector<std::string>&) const;
	std::vector<sf::Sound> makeSoundsVector(const std::vector<sf::SoundBuffer>&) const;

public:

	static Resources& instance();
	~Resources() = default;

	const std::vector<sf::Texture>& getTextures() const;
	const sf::Texture& getTexture(const int) const;
	const sf::Font& getFont(const int) const;
	const std::string& getLevel(const int) const;
	const std::vector<std::string>& getMenuOptions() const;

	void animation(sf::RenderWindow*);
	void playSound(const int);
	void playMusic();
	void saveCurentLevel(const int);

	int getCurentLevel() const;
	int getNumberOfLevels() const;
	float getlevelDuration() const;

	std::vector<std::string> buildMap(const int);
	std::vector<std::string> newMenu() const;
	std::vector<std::string> continueMenu() const;
};