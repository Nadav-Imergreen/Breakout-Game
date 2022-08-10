#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

const float WIN_W = 750;
const float WIN_H = 850;
const float LEFT_BOUNDRY = 0;

const std::string FONT_PATH = "aAnggota.ttf";
const std::string FILE_MAP_NAME = "Board.txt";
const std::string FILE_TABLE_NAME = "HighRecordTable.txt";

const float PI = 3.14159f;

const float PADDLE_SPEED = 185.f;

const float BALL_SPEED = 18.0;

const float GIFT_SPEED = 80.0;

const float BALL_RADIUS = 10.f;


const sf::Vector2f RIGHT_FRAME_POSITION = { WIN_W - 5, 100 };
const sf::Vector2f RIGHT_FRAME_SIZE = { 5.f, WIN_H - 100 };
const sf::Vector2f LEFT_FRAME_POSITION = { 0, 100 };
const sf::Vector2f LEFT_FRAME_SIZE = { 5.f, WIN_H - 100 };
const sf::Vector2f TOP_FRAME_POSITION = { 0, 100 };
const sf::Vector2f TOP_FRAME_SIZE = { WIN_W, 5 };

enum class FRAME_P
{
    RIGHT_P,
    LEFT_P,
    UP_P,
    PADDALE_P
};

const int DOUBLE_HIT = 2;
const int SINGLE_HIT = 1;

const sf::Vector2f PADDLE_SIZE = { 100.f, 25.f };
const sf::Vector2f PADDLE_POSITION = {WIN_W/2, WIN_H - 20};

const sf::Vector2f BALL_SIZE = { 15.f, 15.f };
const sf::Vector2f BALL_POSITION = { WIN_W / 2, WIN_H - (20 + 20.f) };

const sf::Vector2f STOPED = { 0.f, 0.f };
const sf::Vector2f LEFT = { -1.f, 0.f };
const sf::Vector2f RIGHT = { 1.f, 0.f };

const int NUM_OF_TEXTURES = 25;
const std::string TEXTURES[] = { "paddle.png", "menu.png", "help.png", "ball.png", "orange.png",
                                 "strongbrick.png", "blue.png", "yellow.png", "green.png", "purple.png", "red.png",
                                 "damagebrick.png", "gameover.png", "win.png", "pause.png", "play.png", "direction.png",
                                 "fast.png", "increasepaddle.png", "strongball.png", "morepoints.png", "heart.png", 
                                 "mute.png", "unmute.png", "highscore.png"};
                                 
enum class TextureType {
    Paddle,
    Menu,
    Help,
    Ball,
    Orange,
    StrongBrick,
    GiftBrick,
    Yellow,
    Green,
    Purple,
    Red,
    DamageBrick,
    GameOver,
    Win,
    Pause,
    Play,
    ChangeDir,
    FastPaddle,
    IncreasePaddle,
    StrongBall,
    AddScore,
    AddLife,
    Mute,
    Volume,
    HighRecordTable,
};

const int NUM_OF_SOUNDS = 9;
const std::string SOUNDS[] = { "menu.ogg", "win.ogg", "lost.ogg", "brick.wav", "gift.wav", "paddle.wav", "wall.wav",
                               "lose.wav", "winlevel.wav"};

enum class SoundType {
    Menu,
    Win,
    GameOver,
    Brick,
    Gift,
    Paddle,
    Wall,
    Lose,
    WinLevel
};
const float SOUND_VOLUME = 20.f;

const int NUM_OF_TEXTS = 4;
const std::string MENU_TEXTS[] = { "start", "help", "high score", "exit" };

enum class MenuOpt {
    Start,
    Help,
    HighScore,
    Exit,
};

const int START = 0;
const int HELP = 1;
const int HIGH_SCORE = 2;
const int EXIT = 3;


const char STRONG_BRICK = 'S';
const char GIFT_BRICK = '$';
const char ORANGE = 'O';
const char RED = 'R';
const char PURPLE = 'P';
const char YELLOW = 'Y';
const char GREEN = 'G';



const int INFO_H = 100;
const std::string INFO_TEXTS[] = { "Level: ", "Score: ", "Life: "};

enum class Information {
    Level,
    Score,
    Life,
};


const int NUM_OF_OPTIONS = 2;
const int PAUSE = 0;
const int VOLUME = 1;

const int NUM_OF_INFO = 3;
const int NUM_OF_RECORDS = 7;
const float INFO_TEXT_W = WIN_W / 1.5 / NUM_OF_INFO;
const float INFO_TEXT_Y = INFO_H / 2;
const float FIRST_INFO_TEXT_X = INFO_TEXT_W / 2;


enum class LevelSituation {
    LostGame,
    LostLife,
};

const int NUM_OF_GIFTS = 6;
const int RESIZE_PADDLE = 0;
const int CHANGE_DIR = 1;
const int FAST_PADDLE = 2;
const int STRONG_BALL = 3;
const int ADD_SCORE = 4;
const int ADD_LIFE = 5;

typedef	std::vector<std::pair<std::string, int>> HighscoreVector;
