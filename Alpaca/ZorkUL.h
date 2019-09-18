#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class ZorkUL {
private:
	Parser parser;
	Room *currentRoom;
    Room *a1, *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *j1;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
	void goRoom(Command command);
    void teleport();
    void createItems();
    void displayItems();
    void map();

public:
	ZorkUL();
	void play();
	string go(string direction);
};

#endif /*ZORKUL_H_*/
