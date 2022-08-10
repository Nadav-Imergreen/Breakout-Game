#pragma once
#include "HighScore.h"

HighScore::HighScore()
{
}

void HighScore::readTableFromFile()
{
    std::fstream highrcordInput;		//for high-score table

    //open for read
    highrcordInput.open(FILE_TABLE_NAME, std::ios::in);

    if (!highrcordInput.is_open())
    {
        std::cout << "cannot open file" << std::endl;
        exit(EXIT_FAILURE);
    }

    //read high-records data from file to vector <pair>

    m_table.clear();
    highrcordInput.seekg(0, std::ios::beg);

    std::pair<std::string, int> p;

    for (auto line = std::string(); std::getline(highrcordInput, line);)
    {
        p.first = line;
        std::getline(highrcordInput, line);
        p.second = std::stoi(line);

        m_table.push_back(p);
    }

    // sort the vector by second element (score), using lambda function 
    std::sort(m_table.begin(), m_table.end(), [](auto& left, auto& right) {return left.second > right.second; });
    highrcordInput.close();
}

void HighScore::saveScoreInFile(std::string name, int score)
{
    std::fstream highrcordOutput;

    // check if have any room avalable in the high-score table 
    if (m_table.size() < NUM_OF_RECORDS)
    {
        highrcordOutput.open(FILE_TABLE_NAME, std::ios::out | std::ios::app);

        if (!highrcordOutput.is_open())
        {
            std::cout << "cannot open file" << std::endl;
            exit(EXIT_FAILURE);
        }

        //write name and score on file

        highrcordOutput << name << std::endl;
        highrcordOutput << score << std::endl;

    }
    // if the  high-score table is full - check if current record is bigger then last record.
    // if so, replace beteen them
    else if (score > m_table.back().second)
    {
        highrcordOutput.open(FILE_TABLE_NAME, std::ios::out | std::ios::trunc);

        if (!highrcordOutput.is_open())
        {
            std::cout << "cannot open file" << std::endl;
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < m_table.size() - 1; i++)
        {
            highrcordOutput << m_table[i].first << std::endl;
            highrcordOutput << m_table[i].second << std::endl;
        }

        //write name and score on file
        highrcordOutput << name << std::endl;
        highrcordOutput << score << std::endl;
    }

    highrcordOutput.close();
}

void HighScore::readTableFromVector()
{
    m_names.clear();
    m_highRecords.clear();

    //push the names text to vector <text>

    for (int i = 0; i < m_table.size(); i++)
    {
        m_names.push_back(sf::Text(m_table[i].first, Resources::instance().getFont()));
        m_names[i].setPosition({ (WIN_W / 3) - 25, float(WIN_H / (m_table.size() + 1) * (i + 1.5)) });
        m_names[i].setColor(sf::Color::Yellow);
    }

    //push the high-rcord numbers to vector <text>

    for (int i = 0; i < m_table.size(); i++)
    {
        m_highRecords.push_back(sf::Text((std::to_string(m_table[i].second)), Resources::instance().getFont()));
        m_highRecords[i].setPosition({ ((WIN_W / 3) * 2) - 25, float(WIN_H / (m_table.size() + 1) * (i + 1.5)) });
        m_highRecords[i].setColor(sf::Color::Yellow);
    }
}

void HighScore::displayHighScore(sf::RenderWindow& window)
{
    m_sprite.setTexture(Resources::instance().getTexture(TextureType::HighRecordTable));

    window.clear();

    //draw high_score back-graund

    window.draw(m_sprite);

    //draw text(names and score)

    for (int i = 0; i < m_highRecords.size(); i++)
        window.draw(m_highRecords[i]);

    for (int i = 0; i < m_names.size(); i++)
        window.draw(m_names[i]);

    window.display();

    //read mouse events - close window or return

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