#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#define NUM_FRAMES 150

#include <ncurses.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <curses.h>
#include <math.h>
#include <stdlib.h>


/**
* initializes ncurses and hides the terminal
**/
void start_interface();

/**
* Ends the curses mode. Must be called at end of program to avoid errors
**/
void end_interface();

//TODO: Documentation
void createDialogueWin();

void createDetailsWin();

void createLastCommandwin();

void print_feedback(std::string feedback);

void clearFeedback();

/**
* printString(string) - accepts a std::string variable and prints it to the screen
* handles all conversion to c-string and refreshes the ncurses display.
* PARAM: std::string
* RETURN: nothing
**/
void printString(std::string message);

void printItems(std::string item);

void printLastGoodCommand(std::string message);

/**
* Creates an ncurses window at specified location and size
* PARAM: int values represent number of lines and columns in terminal
* RETURN: pointer to new ncurses window
**/
WINDOW *create_newwin(int height, int width, int starty, int startx, bool border);

//TODO: Documentation
void destroy_win(WINDOW *local_win);

/**
* Uses ncurses API to accept input from user. Will accept all text until 
* user presses enter / return. Input location is at bottom left corner of display
* PARAM: nothing
* RETURN: std::string value
**/
std::string getInput();

//TODO: Documentation
void printHelp();

void titleAnimation();

void fireAnimation();

void explosion();

#endif

