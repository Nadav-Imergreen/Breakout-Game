# Breakout-Game
Written by Moshe Namdar & Nadav Imergreen. 
Run this game using Visual Studio and SFML graphics library. 

in the program we implemented The game "Breakout". 
On the main screen, the "menu" will open in which the following 4 options will be displayed:

Start - the game will start in level 1. 
Help - the game presents the instructions for how to play and the rolls. 
High Score – the table of records.
Exit - exit from the game.

The course of the game: 
the game will have 4 stages where the goal of each stage is to break all the bricks using the ball.
Meeting the conditions of the stage will result in moving to the next stage, while failure will result in loss of life.
The end of the game: after winning all the stages of the game, or when all the lives of the player are lost.

List of files:
Menu - A department that controls the management of the main menu in the game. 
       Holds an image in which the text of the menu will be displayed,
       when the "Start" button is pressed, the game will begin.
      
Controller - The department that controls the management of the game.
              Runs the game, moves the paddle using the keyboard arrows. 
              The controller class will additionally manage the reading of the stages from the input file, the transition between the stages, 
              the initialization of a stage in case of failure and the end of the game in case of success.
              end game happened when the program can no longer read from the input file.
          
board - This class will hold 3 vectors in which we will store the bricks, gifts and walls of the game board. In addition, to 2 objects of the paddle           and ball type. We will load the game board, and spread the objects on the game window respectively. At each step we will call the current step         according to the board size defined in the input file. 

Info - the department responsible for the game. Contains vector style text and sprite type with which we will present the information at the top of the        screen about the game.

Resources - a "singleton" style class that manages all resources in the game - textures, tunes and fonts. This class can be accessed from anywhere in               the program using the static access function "instance"

HighScore – another class on the game's highscore table. Holds a Pair type vector in which we store ordered pairs of string & int type.

data structures:
A vector of type Frame in which we will store the frames of the board in each step.
Vector of type Brick in which we will store the bricks of each step.
A vector of type Gift in which we will store the gifts in each step.
Vector D 2 of type char in which we store and from which we load the game board at each stage.
Vector of type Texture in which we will store all the textures displayed during the game.
2 Text type vectors in which we will store the texts displayed in the start menu and the information line during the game.
Vector of SoundBuffer type in which we will store all the tunes played during the game.
Vector of type Pair in which we will store ordered pairs of type string & int for the highs table of the game.

Conflict management: double dispatch

ENJOY
      
      



