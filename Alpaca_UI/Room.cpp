#include "Room.h"
#include "Command.h"
#include <iostream>


Room::Room(QString description) {
	this->description = description;
    invalid = new Item("Invalid Item", 0, 0);
}

void Room::setExits(Room *North, Room *East, Room *South, Room *West, Room *Down, Room *Up) {
    if (North != NULL)
        exits["North"] = North;
    if (East != NULL)
        exits["East"] = East;
    if (South != NULL)
        exits["South"] = South;
    if (West != NULL)
        exits["West"] = West;
    if (Down != NULL)
        exits["Down"] = Down;
    if(Up != NULL)
        exits["Up"] = Up;
}

QString Room::shortDescription() {
	return description;
}

QString Room::longDescription() {
	return "room = " + description + ".\n" + displayItem() + exitString();
}

QString Room::exitString() {
    QString returnString = "\nexits =";
    for (map<QString, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
		// Loop through map
		returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
	return returnString;
}

Room* Room::nextRoom(QString direction) {
    map<QString, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    //cout <<endl;
    //cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(*inItem);
}

Item Room::getItem(QString search, QString other, unsigned int a){


        if (other.toLower() == search.toLower())
        {
            return itemsInRoom[a];
        }

    return *invalid;
}

QString Room::displayItem() {
    QString tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(QString inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            inString = inString.toLower();
            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription().toLower());
            if (tempFlag == 0) {

                return x;
            }
            x++;
            }
        }
    return -1;
}

void Room::removeItemFromRoom(QString removeIt){
    for (unsigned int b = 0; b < itemsInRoom.size(); b++)
    {
        if (itemsInRoom[b].getShortDescription().toLower()==removeIt.toLower())
        {
            itemsInRoom.erase(itemsInRoom.begin()+b);
        }
    }
}

