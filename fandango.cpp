/*
 * fandango.cpp -- base engine for Fandango Group's project (CMD1)
 * Last Modified -- 11/02/2016
 * Last Modified By -- Josh Gonzalez
 * Known Issues  --
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "rooms.hpp"
#include "player.hpp"
#include "interface.hpp"

#define MAX_X 5
#define MAX_Y 3

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::istringstream;
using std::vector;

int checkRoomItems(Rooms *arrayGrid[][MAX_Y], Player *player, string item) {
    int result = arrayGrid[player->currentX][player->currentY]->checkItems(item);
    return result;
}

int checkPlayerPack(Player *player, string item) {
    int result = player->checkPack(item);
    return result;
}

//checks direction and if valid, updates player's current position
void moveRoom(Rooms *arrayGrid[][MAX_Y], Player *player, int &x,int &y, string dir)
{
    if ((dir.compare("n") == 0)&&(arrayGrid[x][y]->getNorth()==true))
    {
        y--;
    }
    else if ((dir.compare("s") == 0)&&(arrayGrid[x][y]->getSouth()==true))
    {
        y++;
    }
    else if ((dir.compare("e") == 0)&&(arrayGrid[x][y]->getEast()==true))
    {
        x++;
    }
    else if ((dir.compare("w") == 0)&&(arrayGrid[x][y]->getWest()==true))
    {
        x--;
    }
    else
    {
        print_feedback("There is no door in that direction.");
        return;
    }
    //if hasVisited give short description else give long and set hasVisited true
    if(arrayGrid[player->currentX][player->currentY]->gethasVisited()) {
        printString(arrayGrid[player->currentX][player->currentY]->getSdesc());
    } 
    else {
        //set hasVisited to true and print long form desc
        arrayGrid[player->currentX][player->currentY]->hasVisited = true;
        printString(arrayGrid[player->currentX][player->currentY]->getLdesc());
    }

    //print features in the room
    //I'm moving this message to inside the getFeatures function - Will T.
    //cout << "The following features are in the room: " << endl;
    arrayGrid[player->currentX][player->currentY]->getFeatures();

    //print items in the room
    arrayGrid[player->currentX][player->currentY]->getItem();
}

void printIntro() {
    printString("We are in the midst of a worldwide zombie apocalypse.  I have managed to survive for almost one year.  I've lost many friends and family but have also gained a new family.  I trust them all with my life and they trust me with theirs.  I will need each one of them to help me continue on and make a life for ourselves in this new world.  We have managed to take over a state prison. It has all we need for survival: strong gates, access to a well, and a large yard for raising livestock and growing crops.  We now have a new enemy.  It is not the hoards of zombies.  It is a living man.  He wants to take what is ours but we have worked too hard for too long to let him take it from us.");
}

//takes the game board instance, player instance, and valid (parsed) command
//executes dynamic commands using class functions, static commands hard-coded using local functions
//library of commmands are static in some cases and dynamic in others
void executeCmd(Rooms *arrayGrid[MAX_X][MAX_Y], Player *player, string cmd) {
    
    //strip first word for dynamic commands
    istringstream iss(cmd);
    string word;
    iss >> word;
    
    //static commands
    if(cmd.compare("go n") == 0) {
        moveRoom(arrayGrid, player, player->currentX, player->currentY, "n");
    }
    else if(cmd.compare("go s") == 0) {
        moveRoom(arrayGrid, player, player->currentX, player->currentY, "s");
    }
    else if(cmd.compare("go e") == 0) {
        moveRoom(arrayGrid, player, player->currentX, player->currentY, "e");
    }
    else if(cmd.compare("go w") == 0) {
        moveRoom(arrayGrid, player, player->currentX, player->currentY, "w");
    }
    else if(cmd.compare("look") == 0) {
        printString(arrayGrid[player->currentX][player->currentY]->getLdesc());
    }
    else if(cmd.compare("show pack") == 0) {
        player->getBackpackContents();
    }
    
    //dynamic commands
    else if(word.compare("grab") == 0) {
        //get next word
        iss >> word;
        player->pickUpItem(word, arrayGrid[player->currentX][player->currentY]->roomItem); 
    }
    else if(word.compare("drop") == 0) {
        //get next word
        iss >> word;
        player->dropItem(word, arrayGrid[player->currentX][player->currentY]->roomItem); 
    }
    else if(word.compare("look") == 0) {
        //get next word
        iss >> word;
        if(word.compare("at") == 0) {
            //get next word
            iss >> word;
            string str = arrayGrid[player->currentX][player->currentY]->getFeatureDesc(word, arrayGrid[player->currentX][player->currentY]->roomItem);
            // cout << str << endl;
            print_feedback(str);
        }
    }
    else {

        print_feedback("debug: command not found in command library, parsed but not executed!!");

        //cout << "debug: command not found in command library, parsed but not executed!!" << endl; //should never get here once done adding all exe's

        return;
    }
}

//takes the game board instance, player instance, level in the command tree, current word and parent word
//checks arrays for each level and acceptable parents to those words 
//checks class object vectors to see if items, features are in the room or possesion of the player
//returns int to parseCmd().  Returns 0 if word at level is allowed, else returns 1
//prints message to user if items, features are not in the room or in possesion of the player
int checkWord(Rooms *arrayGrid[MAX_X][MAX_Y], Player *player, int level, string word, string parentWord) {
    int result = 0;
    int i;
    const string l1[] = {"look", "go", "show", "grab", "drop"}; 
    const string l10[] = {"at"}; 
    const string l11[] = {"n", "s", "e", "w"}; 
    const string l12[] = {"pack"}; 
    int s1 = sizeof(l1) / sizeof(string);
    int s10 = sizeof(l10) / sizeof(string);
    int s11 = sizeof(l11) / sizeof(string);
    int s12 = sizeof(l12) / sizeof(string);
    switch(level) {
        case 1:
            for(i = 0; i < s1; ++i) {
                if(l1[i].compare(word) == 0) {
                    result = 1;
                }
            }
            break;
        case 2:
            if(parentWord.compare("look") == 0) {
                for(i = 0; i < s10; ++i) {
                    if(l10[i].compare(word) == 0) {
                        result = 1;
                    }
                }
            }
            if(parentWord.compare("go") == 0) {
                for(i = 0; i < s11; ++i) {
                    if(l11[i].compare(word) == 0) {
                        result = 1;
                    }
                }
            }
            if(parentWord.compare("show") == 0) {
                for(i = 0; i < s12; ++i) {
                    if(l12[i].compare(word) == 0) {
                        result = 1;
                    }
                }
            }
            if(parentWord.compare("grab") == 0) {
                result = checkRoomItems(arrayGrid, player, word);
                if(result != 1) {
                    print_feedback(word + " is not in the room");
                    //cout << word << " is not in the room... ";
                }
            }
            if(parentWord.compare("drop") == 0) {
                result = checkPlayerPack(player, word);
                if(result != 1) {
                    print_feedback(word + " is not in the backpack...");
                    // cout << word << " is not in the backpack... ";
                }
            }
            break;
        case 3:
            if(parentWord.compare("at") == 0) {
                result = arrayGrid[player->currentX][player->currentY]->checkFeature(word);
                if(result != 1) {
                    print_feedback(word + " is not a feature here... ");
                    // cout << word << " is not a feature here... ";
                }
            }
            break;
    }
    return result;
}

//takes the game board instance, player instance, and command string from user
//strips off words and sends them to checkWord
//returns int to main().  Returns 0 if any word fails checkWord, else returns 1
//prints to console a message if the command is invalid
//continues until the entire command string has been parsed or a word is invalid
int parseCmd(Rooms *arrayGrid[MAX_X][MAX_Y], Player *player, string cmd) {
    int level = 1;
    //check if this is an allowed single word command
    bool singleOK  = true;
    if(cmd.compare("go") == 0) {
        singleOK = false;
    }
    istringstream iss(cmd); 
    string word;
    string parentWord ;
    while(iss >> word) {
        int result = checkWord(arrayGrid, player, level, word, parentWord);
        if(result == 0) {
            print_feedback("Invalid command: " + cmd);
            return 0;
        }
        ++level;
        parentWord = word;
    }
    //single word command was not allowed
    if(level != 1 && singleOK == false) {
        print_feedback("Invalid command: " + cmd);
        return 0;
    }
    return 1; 
}

int main(int argc, char** argv) {
    //instantiate game state
    Rooms *board[MAX_X][MAX_Y]; //create a playing surface
    createRoomObjects(board);   //setup the board
    Player *rick = new Player();//put a player on the board
    rick->setStartLocation();   //maybe we should call a constructor for this

    start_interface();

    //start game
    printIntro();
    print_feedback("Press any key to continue.");
    noecho();
    getch();
    echo();
    clearFeedback();
    //print out long from desc of starting room
    printString(board[rick->currentX][rick->currentY]->getLdesc());

    //print features in the starting room
    //cout << "The following features are in the room: " << endl;
    board[rick->currentX][rick->currentY]->getFeatures();
    //print items in the starting room
    board[rick->currentX][rick->currentY]->getItem();
    //set starting room to hasVisited
    board[rick->currentX][rick->currentY]->hasVisited = true;
    int result;                 //return value of parse (is entire cmd valid?)
    string cmd;                 //entire command that the user supplies 
    do {
        cmd = getInput();
        print_feedback("                                                                      ");
        if(cmd == "quit" || cmd == "q") { continue; }
        if(cmd == "help" || cmd == "h") { printHelp(); } 
        else {
            result = parseCmd(board, rick, cmd);
            if(result == 1) { executeCmd(board, rick, cmd); }
        }
    }
    while((cmd != "q") && (cmd != "quit"));

    end_interface();

    return 0;
}
