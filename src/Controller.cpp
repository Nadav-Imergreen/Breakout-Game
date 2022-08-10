#include "Controller.h"


Controller::Controller()
    : m_window(sf::VideoMode(WIN_W, WIN_H), "Breakout", sf::Style::Titlebar | sf::Style::Close)
{
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(60);

    try
    {
       //open board file 
       m_file.open(FILE_MAP_NAME);

       if (!m_file.is_open())
           throw std::exception();
    }
    catch (const std::exception fail)
    {
        std::cerr << "Uneble to open file because " << fail.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Controller::run()
{
    //read and load highrcordTable
    m_menu.readTableFromFile();
    m_menu.readTableFromVector();

    sf::Sound s;

    while (m_window.isOpen() && m_menu.run(m_window))
    {
        readLevel();     
        m_board.loadLevel(m_map, m_size);

        while (m_window.isOpen())
        {
            if (runLevel())     //win level
            {
                if (readLevel())        //try to read new level
                {
                    if (Resources::instance().getVolume())
                    {
                        s.setBuffer(Resources::instance().getSound(SoundType::WinLevel));
                        s.play();
                    }
                    m_board.loadLevel(m_map, m_size);    //load level
                }     
                else     //no more levels to read
                {
                    endGame(TextureType::Win, SoundType::Win);
                    restart();
                    break;
                }
                    
            }
            else      //lost game
            {
                endGame(TextureType::GameOver, SoundType::GameOver);
                restart();
                break;
            }
        }
    }  
    m_file.close();
}

bool Controller::runLevel()
{
    sf::Sound s;
    sf::Vector2f location;
    sf::Clock clock;

    while (m_window.isOpen())
    {
        m_window.clear();
        m_board.draw(m_window);
        m_window.display();

        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::KeyPressed:
                handleEvent(event.key.code);
                break;
            case sf::Event::KeyReleased:
                m_board.setPaddleDirection(STOPED);
                break;

            case sf::Event::MouseMoved:
                location = (sf::Vector2f)sf::Mouse::getPosition(m_window);
                m_board.handleMouseMoved(m_window, location);
                break;

            case sf::Event::MouseButtonReleased:
                location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                m_board.handleClick(m_window, location);
                break;
            }

        }

        auto delta = clock.restart();

        if (!m_firstServe)             //wait for space keypressed to start movement
            if (!m_board.isPause())
                if (m_board.update(delta))
                    return true;
            

        if (m_board.levelLost() == LevelSituation::LostLife)    //if lost level - initialize level objects again
        {
            if (Resources::instance().getVolume())
            {
                s.setBuffer(Resources::instance().getSound(SoundType::Lose));
                s.play();
            }
            m_board.init();
            m_firstServe = true;
        }

        if (m_board.levelLost() == LevelSituation::LostGame)    //if game lost - end function 
            return false;

    }
    return false;
}

bool Controller::readLevel()
{
    //restart level
    m_board.nextLevel();
    m_firstServe = true;
    m_map.clear();

    m_file >> m_size.x >> m_size.y;
    if (m_file.eof())
        return false;

    m_file.get();  //enter

    for (int r = 0; r < m_size.x; r++)
    {
        std::vector<char> line;
        for (int c = 0; c < m_size.y; c++)
        {
            line.push_back(m_file.get());
        }
        m_map.push_back(line);
        m_file.get();
    }

    return true;
}


void Controller::handleEvent(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        m_board.setPaddleDirection(LEFT);
        break;
    case sf::Keyboard::Right:
        m_board.setPaddleDirection(RIGHT);
        break;
    case sf::Keyboard::Space:
        if (m_firstServe)
        {
            m_board.setBallAngle();
            m_firstServe = false;
        }
        break;
    default:
        break;
    }
}

void Controller::endGame(const TextureType& texture, const SoundType& sound)
{ 
    m_sprite.setTexture(Resources::instance().getTexture(texture));

    int i = 0;  //parameter for name vector<text>
    sf::Text text; // to hold text writing on screen
    std::vector<sf::Text> name;	//vector to hold player name
    std::string nameAsString;

    sf::Sound s;
    s.setBuffer(Resources::instance().getSound(sound));
    s.setVolume(SOUND_VOLUME * 2);
    s.play();

    playreName(text);   //to display text on board

    while (m_window.isOpen())
    {
        m_window.clear();

        m_window.draw(m_sprite);    //draw back-ground photo
        m_window.draw(text);      //draw text
        for (size_t j = 0; j < name.size(); j++)      //draw player name 
             m_window.draw(name[j]);

        m_window.display();

        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::TextEntered:
                name.push_back(m_menu.getPlayerName(event.text.unicode, i++));
                nameAsString.push_back(event.text.unicode);
                break;

            case sf::Event::MouseButtonReleased:
               auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

               if (location.x < 200 && location.y > 600)
               {
                   m_menu.saveScoreInFile(nameAsString, m_board.getScore());   //save winner score and name in the file
                   name.clear();
                   nameAsString.clear();
                   return;
               }
            }
        }
    }
}


void Controller::restart()
{
    //read and load highrcordTable
    m_menu.readTableFromFile();
    m_menu.readTableFromVector();

    // cleer all objects from vectors and go back to beginning of the file
    m_file.clear();
    m_file.seekg(0, std::ios::beg);
    m_board.restartInfo();
   
}

void Controller::playreName(sf::Text& text)
{
    text.setFont(Resources::instance().getFont());
    text.setString("Please enter your name:");
    text.setPosition(50, 100);
    text.setCharacterSize(42);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);
}