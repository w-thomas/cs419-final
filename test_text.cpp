/*Author: Jennifer Mendoza
* Description: testing program
* Group: Fandango
* Last Modified: 10/30/2016
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "rooms.hpp"
#include "player.hpp"
#include "item.hpp"
#include "feature.hpp"

using namespace std;



void moveRoom(Rooms *arrayGrid[][3], int &x,int &y, string dir);


int main () {

	Rooms *roomGrid[5][3];
	Player player1;
	string direction;
	string end;
	string item;
	string choose;
	string feature;
	int goodFeature;
	
	//keeps track of the player's current position
	player1.setStartLocation();

	//creates array of objects
	createRoomObjects(roomGrid);
	
/*	//test get features in a room
	cout<<roomGrid[0][0]->getFeatureDesc("door", player1.backpack)<<endl;
	player1.pickUpItem("gun",roomGrid[player1.currentX][player1.currentY]->roomItem);
	cout<<roomGrid[0][0]->getFeatureDesc("door", player1.backpack)<<endl;
	cout<<roomGrid[0][0]->getFeatureDesc("walker", player1.backpack)<<endl;
	cout<<roomGrid[1][0]->getFeatureDesc("blood", player1.backpack)<<endl;
	
	//test display items in room
	roomGrid[0][0]->getItem();

	//test pick up item
	player1.pickUpItem(end, roomGrid[0][0]->roomItem);

	//test if room deleted item
	roomGrid[0][0]->getItem();
	
	//test display backpack contents
	player1.getBackpackContents();
	
	//test drop item
	player1.dropItem(end, roomGrid[0][0]->roomItem);
	
	//test display backpack contents
	player1.getBackpackContents();
	
	//test display items in room
	roomGrid[0][0]->getItem();
	
	//test program for player movement, hasVisited boolean, and item interaction
*/	while(end.compare("y") != 0)
	{	
		
		cout<<"You are in: "<<roomGrid[player1.currentX][player1.currentY]->getName()<<endl;
		if (roomGrid[player1.currentX][player1.currentY]->gethasVisited()==false)
		{
			cout<<roomGrid[player1.currentX][player1.currentY]->getLdesc()<<endl;
		}
		else
		{
			cout<<roomGrid[player1.currentX][player1.currentY]->getSdesc()<<endl;
		}
		roomGrid[player1.currentX][player1.currentY]->hasVisited=true;
		
		//feature test
		roomGrid[player1.currentX][player1.currentY]->getFeatures();
		cout<<"Would you like to interact with a feature(y/n)?"<<endl;
		cin>>choose;
		
		if (choose=="y")
		{
			cout<<"which feature?"<<endl;
			cin>>feature;
			goodFeature=roomGrid[player1.currentX][player1.currentY]->checkFeature(feature);
			cout<<"gF: "<<goodFeature<<endl;
			if (goodFeature==1)
			{
				cout<<roomGrid[player1.currentX][player1.currentY]->getFeatureDesc(feature, player1.backpack)<<endl;
			}
			else
			{
				cout<<"You cannot interact with that in here."<<endl;
			}
		}
		
		//item test
		roomGrid[player1.currentX][player1.currentY]->getItem();
		cout<<"Would you like to pick or drop an item (type pick or drop)?"<<endl;
		cin>>choose;
		if (choose.compare("pick")==0)
		{
			cout<<"which item do you want to pickup?"<<endl;
			cin>>item;
			player1.pickUpItem(item, roomGrid[player1.currentX][player1.currentY]->roomItem);
		}
		if (choose.compare("drop")==0)
		{
			cout<<"which item do you want to drop?"<<endl;
			cin>>item;
			player1.dropItem(item, roomGrid[player1.currentX][player1.currentY]->roomItem);
		}
		
		cout<<"Which direction?"<<endl;
		cin>>direction;
		moveRoom(roomGrid, player1.currentX, player1.currentY, direction);
		
		cout<<"End test?"<<endl;
		cin>>end;
		cout<<endl;
		cout<<endl;
	}
	return 0;
}

//checks direction and if valid, updates player's current position
//set up to be a 5x3 grid
void moveRoom(Rooms *arrayGrid[][3], int &x,int &y, string dir)
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
		cout<<"There is no door in that direction."<<endl;
	}

	
	
}
