# Breakout-Game
in the program I implemented The game "Breakout". 
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
          
board - This class will hold 3 vectors in which we will store the bricks, gifts and walls of the game board. In addition, to 2 objects of the paddle and ball type. We will load the game board, and spread the objects on the game window respectively. At each step we will call the current step according to the board size defined in the input file.          
      
      



