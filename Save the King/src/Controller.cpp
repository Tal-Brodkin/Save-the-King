#include "Controller.h"
#include "Board.h"





Controller::Controller() : m_player(0), m_current_level(0), m_window(NULL), m_level_won(0), m_current_level_characters(0), m_game_over(0)
{
}



void Controller::run()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    //background music
    Resources::instance().playMusic();

    //creation of the game window and setting the frame rate to be limited to 60FPS
    m_window = new sf::RenderWindow(sf::VideoMode(1600, 1000), "Save the king", sf::Style::Close);
    m_window->setFramerateLimit(60);
    std::string name = "S A V E    T H E    K I N G";

    //the game supports saving levels. So if the game lunches for the first time
    //or if the player finished the game, the game starts from the first level
    //and there will be a regular menu with 3 options (start, info, exit)
    //If the game lunches when for example the player is on the second level
    //or if the player won some level and choose to go back to the menu
    //there will be a menu with 4 option (continue, new game, info, exit)
    int current_level = Resources::instance().getCurentLevel();
    std::vector<std::string> options;

    if (current_level == 0)
    {
        options = Resources::instance().newMenu();
    }
    else
    {
        options = Resources::instance().continueMenu();
        m_current_level = current_level;
    }

    Menu main_menu(m_window, options, name);
    sf::Vector2f location;

    //main loop of the game - the menu
    while (m_window->isOpen()) 
    {
        //this part handling if the player choose to go back after winning a level
        //we dont whant to initialize the main_menu each round of the loop, but only
        //if it got changed from the original main_menu
        auto& text = main_menu.getMenuText();
        if (m_current_level != 0 && text.size() != 4)
        {
            main_menu = Menu(m_window, Resources::instance().continueMenu(), name);
        }
        else if (m_current_level == 0 && text.size() != 3)
        {
            main_menu = Menu(m_window, Resources::instance().newMenu(), name);
        }

        m_window->clear();
        main_menu.drawMenu(m_window); //drawing the menu
        m_window->display();

        //handling mouse events 
        if (auto event = sf::Event{};  m_window->waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: 
                m_window->close();
                break;
            case sf::Event::MouseMoved:
                location = (sf::Vector2f)sf::Mouse::getPosition(*m_window);
                handleMouseHover(location, main_menu);
                break;
            case sf::Event::MouseButtonReleased:
                location = m_window->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    handleMouseClick(location, main_menu);
                    break;
                }
                break;
            }
        }
    }
}


void Controller::startGame()
{   
    //screen fade out animation
    Resources::instance().animation(m_window);
    bool back_to_menu = false;
    int num_of_levels = Resources::instance().getNumberOfLevels();

    float deltaTime;
    sf::Clock clock;

    //as long the game isnt over (the levels isnt over) and the player  
    //didnt choose to go back to the main menu
    while (!m_game_over && !back_to_menu && m_window->isOpen())
    {
        m_player = 0;   //current character
        Board game_board(m_window, m_current_level); //initialization of the board
        game_board.changePlayersVisual(m_player);   //marks the current character

        //the player can cycle between the different characters
        //in each level can be different number of characters
        //so we need to know how many characters there is in every round
        //to know between how many characters can we cycle
        setNumberOfCharacters(game_board);
        clock.restart();

        //each level can have a different duration of time
        //for each level the duration is readed from the level's file
        m_time = sf::seconds(Resources::instance().getlevelDuration());
        m_level_won = false;

        //as long the level wasn't won and the the time wasn't over
        while (!m_level_won && m_time.asSeconds() > 0 && m_window->isOpen())
        {
            m_window->clear(sf::Color::White);
            game_board.draw(*this);
            m_window->display();

            //updating the current time left for the level
            m_time -= clock.getElapsedTime();

            sf::Event event;
            while (m_window->pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    m_window->close();
                    break;
                }
                //change character with P
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
                    changeCharacter(game_board);
            }

            //restarting the clock each round to know how much time passed in each loop interaction
            deltaTime = clock.restart().asSeconds();

            //movment of the character
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                game_board.move(m_player, 0.f, -VELOCITY, *this);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                game_board.move(m_player, 0.f, VELOCITY, *this);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                game_board.move(m_player, VELOCITY, 0.f, *this);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                game_board.move(m_player, -VELOCITY, 0.f, *this);

            //the movment of th dwarfs is automatic - by the clock
            game_board.moveDwarfs(deltaTime, m_player);
        }
        //checks if the level won, if so increase the level number
        nextLevel();

        //if the levels are not over we will go to the intermediate menu
        if (m_current_level == num_of_levels && m_window->isOpen())
        {
            endMenu();
        }
        //if the levels are over we will go to the end game menu
        else if (m_window->isOpen())
        {
            nextLevel(back_to_menu);
        }
    }
}

void Controller::endMenu()
{
    //screen fade out animation
    Resources::instance().animation(m_window);

    //game over is true so will not attempt to load another level
    m_game_over = true;
    //updating the current level to 0 for if the player would choose to start another game
    m_current_level = 0;
    //saving the current level
    Resources::instance().saveCurentLevel(m_current_level);

    std::string title = "YOU WIN";
    std::vector<std::string> options = {"BACK TO MENU", "EXIT"};

    //creating the menu
    Menu end_menu(m_window, options, title);

    sf::Vector2f location;

    bool back = false;

    while (!back && m_window->isOpen())
    {
        m_window->clear();
        end_menu.drawMenu(m_window);
        m_window->display();

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::MouseMoved:
                location = (sf::Vector2f)sf::Mouse::getPosition(*m_window);
                handleMouseHover(location, end_menu);
                break;
            case sf::Event::MouseButtonReleased:
                location = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    auto& text = end_menu.getMenuText();
                    //back to main menu
                    if (text[0].getGlobalBounds().contains(location))
                    {
                        Resources::instance().playSound(menu_click);
                        back = true;
                    }
                    //exit game
                    if (text[1].getGlobalBounds().contains(location))
                    {
                        Resources::instance().playSound(menu_click);
                        m_window->close();
                    }
                    break;
                }
                break;
            }
        }
    }

}

//information about the game
void Controller::infoMenu(Menu& menu) const
{
    bool back = false;

    while (m_window->isOpen() && !back)
    {
        m_window->clear();
        auto go_back = menu.info(m_window);
        m_window->display();

        if (auto event = sf::Event{};  m_window->waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;

            case sf::Event::MouseButtonReleased:
                auto location = m_window->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    //go back to main menu
                    if (go_back.getGlobalBounds().contains(location))
                    {
                        Resources::instance().playSound(menu_click);
                        back = true;
                    }
                    break;
                }
                break;
            }
        }
    }
}

void Controller::nextLevel(bool& back_to_menu)
{
    std::string title;
    std::vector<std::string> options;

    //if the level won, updates the current level number and saves it to file
    if (m_level_won)
    {
        title = "THE KING REACHED THE THRONE";
        options.push_back("NEXT LEVEL");
        Resources::instance().saveCurentLevel(m_current_level);
    }
    //if the time is over, can try again or exit to main menu
    else
    {
        Resources::instance().playSound(time_over);
        title = "TIME OVER, YOU CAN TRY AGAIN";
        options.push_back("TRY AGAIN");
    }

    options.push_back("BACK TO MENU");

    //screen fade out animation
    Resources::instance().animation(m_window);

    //creates the menu
    Menu intermediate_menu(m_window, options, title);

    sf::Vector2f location;

    bool continueGame = false;

    while (!continueGame && m_window->isOpen())
    {
        m_window->clear();
        intermediate_menu.drawMenu(m_window);
        m_window->display();

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::MouseMoved:
                location = (sf::Vector2f)sf::Mouse::getPosition(*m_window);
                handleMouseHover(location, intermediate_menu);
                break;
            case sf::Event::MouseButtonReleased:
                location = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    auto& text = intermediate_menu.getMenuText();
                    //try again/next level
                    if (text[0].getGlobalBounds().contains(location))
                    {
                        Resources::instance().playSound(menu_click);
                        continueGame = true;
                    }
                    //back to menu
                    if (text[1].getGlobalBounds().contains(location))
                    {
                        Resources::instance().playSound(menu_click);
                        back_to_menu = true;
                        continueGame = true;
                    }
                    break;
                }
                break;
            }
        }
    }
}

//handeling the mouse hover over text
void Controller::handleMouseHover(const sf::Vector2f& location, Menu& menu)
{
    auto& text = menu.getMenuText();

    for (auto& object : text)
    {
        if (object.getGlobalBounds().contains(location))
        {
            object.setOutlineThickness(2);
        }
        else
        {
            object.setOutlineThickness(0);
        }
    }
}

//handeling the mouse click of the main menu
void Controller::handleMouseClick(const sf::Vector2f& location, Menu& menu)
{
    auto& text = menu.getMenuText();

    for (int i = 0; i < text.size(); i++)
    {
        if (text[i].getGlobalBounds().contains(location))
        {
            if (text.size() == 3)
                i++;

            switch (i)
            {
            //continue previous game
            case 0:
                Resources::instance().playSound(menu_click);
                startGame();
                break;
            //start new game
            case 1:
                Resources::instance().playSound(menu_click);
                m_current_level = 0;
                m_game_over = false;
                startGame();
                break;
            //information window
            case 2:
                Resources::instance().playSound(menu_click);
                infoMenu(menu);
                break;
            //exit the game
            case 3:
                Resources::instance().playSound(menu_click);
                m_window->close();
                break;
            }                
        }
    }
}

sf::RenderWindow* Controller::getWindow() const
{
    return m_window;
}

sf::Time Controller::getTime() const
{
    return m_time;
}

int Controller::getLevel() const
{
    return m_current_level;
}

//cycling between the characters
void Controller::changeCharacter(Board& game_board)
{
    game_board.changePlayersVisual(m_player);

    m_player++;
    if (m_player >= m_current_level_characters)
        m_player = 0;

    game_board.changePlayersVisual(m_player);
}

void Controller::levelWon()
{
    m_level_won = true;
}

void Controller::setNumberOfCharacters(const Board& game_bord)
{
    m_current_level_characters = game_bord.getNumberOfCharacters();
}

//handeling the gifts of time, increases or decreases time
void Controller::changeTime(const int seconds)
{
    m_time += sf::seconds((float)seconds);
}

void Controller::nextLevel()
{
    if (m_level_won)
        m_current_level++;
}