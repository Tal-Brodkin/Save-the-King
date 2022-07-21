#include "Menu.h"





Menu::Menu(sf::RenderWindow* window, const std::vector<std::string>& options, const std::string& string)
{
    initializeBackground(window);
    initializeTitle(window, string);
    initializeText(window, options);
}

void Menu::initializeBackground(sf::RenderWindow* window)
{
    m_background = sf::Sprite(Resources::instance().getTexture(13));

    m_background_shape = sf::RectangleShape(sf::Vector2f(800.f, 600.f));
    m_background_shape.setOrigin(m_background_shape.getSize() / 2.f);
    m_background_shape.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f));
    m_background_shape.setFillColor(sf::Color(225, 225, 225, 180));
    m_background_shape.setOutlineColor(sf::Color::Black);
    m_background_shape.setOutlineThickness(1);
}

void Menu::initializeTitle(sf::RenderWindow* window, const std::string& string)
{
    m_title.setString(string);
    m_title.setFont(Resources::instance().getFont(1));
    m_title.setFillColor(sf::Color::White);
    m_title.setOutlineColor(sf::Color::Black);
    m_title.setOutlineThickness(2);
    m_title.setCharacterSize(36);
    m_title.setOrigin(m_title.getGlobalBounds().width / 2.f, m_title.getGlobalBounds().height / 2.f);
    m_title.setPosition(window->getSize().x / 2.f, m_background_shape.getGlobalBounds().top + 100);
}

void Menu::initializeText(sf::RenderWindow* window, const std::vector<std::string>& options)
{
    for (int i = 0; i < options.size(); i++)
    {
        sf::Text text;

        text.setString(options[i]);
        text.setFont(Resources::instance().getFont(0));
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color(0, 171, 255, 255));
        text.setCharacterSize(30);
        text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
        text.setPosition(window->getSize().x / 2.0f, m_background_shape.getGlobalBounds().top + 200 + i * 100);

        m_texts.push_back(text);
    }
}

void Menu::drawMenu(sf::RenderWindow* window) const
{

    window->draw(m_background);
    window->draw(m_background_shape);
    window->draw(m_title);
    for (int i = 0; i < m_texts.size(); i++)
        window->draw(m_texts[i]);
}

std::vector<sf::Text>& Menu::getMenuText()
{
    return m_texts;
}

sf::Sprite Menu::info(sf::RenderWindow* window)
{
    initializeBackground(window);

    auto font = Resources::instance().getFont(1);

    sf::Text intro;
    intro.setFont(font);
    intro.setString("The goal of the game is to bring the king to the throne while overcoming\n"
                      "obstacles and meeting a time limit. At each level there are different\n"
                      "obstacles, as well as gifts that can add or detract from the time you have\n"
                      "or remove all the dwarfs from the current level. Navigate your character\n"
                      "via the arrow keys and change between characters with the Space key.");

    intro.setFillColor(sf::Color::Black);
    intro.setStyle(sf::Text::Bold);
    intro.setCharacterSize(18);
    intro.setPosition(m_background_shape.getGlobalBounds().left + 10.f, m_background_shape.getGlobalBounds().top + 10.f);

    sf::Sprite king_sprite(Resources::instance().getTexture(king));
    king_sprite.setPosition(m_background_shape.getGlobalBounds().left + 10.f, m_background_shape.getGlobalBounds().top + 150.f);

    sf::Sprite mage_sprite(Resources::instance().getTexture(mage));
    mage_sprite.setPosition(m_background_shape.getGlobalBounds().left + 10.f, m_background_shape.getGlobalBounds().top + 250.f);

    sf::Sprite warrior_sprite(Resources::instance().getTexture(warrior));
    warrior_sprite.setPosition(m_background_shape.getGlobalBounds().left + 10.f, m_background_shape.getGlobalBounds().top + 350.f);

    sf::Sprite thief_sprite(Resources::instance().getTexture(thief));
    thief_sprite.setPosition(m_background_shape.getGlobalBounds().left + 10.f, m_background_shape.getGlobalBounds().top + 450.f);

    sf::Text king_text;
    king_text.setFont(font);
    king_text.setString("The KING: Can pass through the teleport and\n"
        "the only one who can reach the throne.");
    king_text.setCharacterSize(20);
    king_text.setFillColor(sf::Color::Black);
    king_text.setPosition(m_background_shape.getGlobalBounds().left + 80.f, m_background_shape.getGlobalBounds().top + 160.f);

    sf::Text mage_text;
    mage_text.setFont(font);
    mage_text.setString("The MAGE: Can put out the fire and go through the teleport.\n");
    mage_text.setCharacterSize(20);
    mage_text.setFillColor(sf::Color::Black);
    mage_text.setPosition(m_background_shape.getGlobalBounds().left + 80.f, m_background_shape.getGlobalBounds().top + 260.f);

    sf::Text warrior_text;
    warrior_text.setFont(font);
    warrior_text.setString("The WARRIOR: Can kill the orc and go through teleport,\n"
        "when the orc is killed he drops a key.");
    warrior_text.setCharacterSize(20);
    warrior_text.setFillColor(sf::Color::Black);
    warrior_text.setPosition(m_background_shape.getGlobalBounds().left + 80.f, m_background_shape.getGlobalBounds().top + 360.f);

    sf::Text thief_text;
    thief_text.setFont(font);
    thief_text.setString("The THIEF: Can pick up the key and open the door with it,\n"
        "can only hold one key at a time, cant pass through teleport.");
    thief_text.setCharacterSize(20);
    thief_text.setFillColor(sf::Color::Black);
    thief_text.setPosition(m_background_shape.getGlobalBounds().left + 80.f, m_background_shape.getGlobalBounds().top + 460.f);

    sf::Text credits;
    credits.setFont(font);
    credits.setString("Created by: Tal Brodkin\n");
    credits.setCharacterSize(20);
    credits.setFillColor(sf::Color::Red);
    credits.setPosition(m_background_shape.getGlobalBounds().left + 10.f, m_background_shape.getGlobalBounds().top + 560.f);

    sf::Sprite go_back(Resources::instance().getTexture(back));
    go_back.setPosition(m_background_shape.getGlobalBounds().left + m_background_shape.getGlobalBounds().width - go_back.getGlobalBounds().width - 10,
                        m_background_shape.getGlobalBounds().top + m_background_shape.getGlobalBounds().height - go_back.getGlobalBounds().height - 10);

    window->draw(m_background);
    window->draw(m_background_shape);
    window->draw(intro);
    window->draw(king_sprite);
    window->draw(mage_sprite);
    window->draw(warrior_sprite);
    window->draw(thief_sprite);
    window->draw(king_text);
    window->draw(mage_text);
    window->draw(warrior_text);
    window->draw(thief_text);
    window->draw(credits);
    window->draw(go_back);

    return go_back;
}
