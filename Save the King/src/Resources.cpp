#include "Resources.h"




Resources::Resources()
{
    m_levels = makeNamesVector("Levels.txt");
    std::vector<std::string> texturesNames = makeNamesVector("textures_types.txt");
    std::vector<std::string> soundsNames = makeNamesVector("sounds_types.txt");

    m_textures = makeTexturesVector(texturesNames);
    m_buffer = makeBufferVector(soundsNames); 
    m_sounds = makeSoundsVector(m_buffer);

    sf::Font font;
    font.loadFromFile("sansation.ttf");
    m_font.push_back(font);
    font.loadFromFile("Raleway.ttf");
    m_font.push_back(font);
}

Resources& Resources::instance()
{
	static Resources instance;
	return instance;
}

const std::vector<sf::Texture>& Resources::getTextures() const
{
    return m_textures;
}

const sf::Texture& Resources::getTexture(const int index) const
{
    return m_textures[index];
}

const sf::Font& Resources::getFont(const int index) const
{
    return m_font[index];
}

const std::string& Resources::getLevel(const int index) const
{
    return m_levels[index];
}

const std::vector<std::string>& Resources::getMenuOptions() const
{
    return m_menu_options;
}

void Resources::playSound(const int index) 
{
    if (m_sounds[index].getStatus() == sf::Sound::Status::Stopped)
        m_sounds[index].play();
}

void Resources::playMusic()
{
    m_sounds[music].setLoop(true);
    m_sounds[music].setVolume(8);
    m_sounds[music].play();
}

int Resources::getNumberOfLevels() const
{
    return (int)m_levels.size();
}

float Resources::getlevelDuration() const
{
    return m_level_duration > 0 ? m_level_duration : 60;
}

void Resources::animation(sf::RenderWindow* window)
{
    auto background = sf::Sprite(Resources::instance().getTexture(13));

    for (int i = 0; i < 255; i++)
    {
        background.setColor(sf::Color(255, 255, 255, (sf::Uint8)i));
        window->draw(background);
        window->display();
    }
}

int Resources::getCurentLevel() const
{
    std::ifstream file;
    char level;

    //opens the file
    file.open("log.txt");
    if (!file.is_open()) {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    file.get(level);
    file.close();

    return level - '0';
}

void Resources::saveCurentLevel(const int num)
{
    std::ofstream file;

    //opens the file
    file.open("..\\..\\..\\resources\\files\\log.txt");
    if (!file.is_open()) {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    file << num;
    file.close();
}

std::vector<std::string> Resources::newMenu() const
{
    return { "START", "INFO", "EXIT" };
}

std::vector<std::string> Resources::continueMenu() const
{
    return { "CONTINUE", "NEW GAME", "INFO", "EXIT" };
}

//vector of image names
std::vector<std::string> Resources::makeNamesVector(const char file_name[]) const
{
    std::ifstream file;
    std::vector<std::string> names;

    //opens the file
    file.open(file_name);
    if (!file.is_open()) {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    //reads the image's name
    for (auto line = std::string(); std::getline(file, line);)
    {
        names.push_back(line);
    }

    file.close();

    return names;
}

//vector of textures function
std::vector<sf::Texture> Resources::makeTexturesVector(const std::vector<std::string>& names) const
{
    std::vector<sf::Texture> textures(names.size());

    for (int i = 0; i < names.size(); i++)
        textures[i].loadFromFile(names[i]);

    return textures;
}

std::vector<sf::SoundBuffer> Resources::makeBufferVector(const std::vector<std::string>& names) const
{
    std::vector<sf::SoundBuffer> buffer(names.size());

    for (int i = 0; i < names.size(); i++)
        buffer[i].loadFromFile(names[i]);

    return buffer;
}

std::vector<sf::Sound> Resources::makeSoundsVector(const std::vector<sf::SoundBuffer>& buffer) const
{
    std::vector<sf::Sound> sounds(buffer.size());

    for (int i = 0; i < buffer.size(); i++)
        sounds[i].setBuffer(buffer[i]);

    return sounds;
}

std::vector<std::string> Resources::buildMap(const int level)
{
    std::ifstream file;
    std::vector<std::string> map;
    auto time = std::string();

    //opens the file
    file.open(getLevel(level));
    if (!file.is_open()) {
        std::cerr << level << " file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::getline(file, time);
    m_level_duration = (float)std::stoi(time);

    //reads the map/level
    for (auto line = std::string(); std::getline(file, line);)
    {
        map.push_back(line);
    }

    file.close();

    return map;
}