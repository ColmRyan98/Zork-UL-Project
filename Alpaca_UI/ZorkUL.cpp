#include <iostream>
#include <time.h>
using namespace std;
#include "ZorkUL.h"

int main(int argc, char argv[]) {
    int random = 0;
    srand(time(NULL));
	ZorkUL temp;
	temp.play();
	return 0;
}

ZorkUL::ZorkUL() {
	createRooms();
}

void ZorkUL::createRooms()  {

    a1 = new Room("Bedroom");
    a = new Room("Farmer's House");
        a->addItem(new Item("Apple", 1, 11));
        a->addItem(new Item("Tiny Turtle Statue", 2, 22));
    b = new Room("Tool Shed");
        b->addItem(new Item("Brush", 3, 33));
        b->addItem(new Item("Poking Stick", 4, 44));
    c = new Room("Alpaca Pen");
    d = new Room("Llama Pen");
    e = new Room("Petting Zoo");
    f = new Room("Shearing Pen");
    g = new Room("Behind Shearing Pen");
    h = new Room("Fleece Mill");
    i = new Room("Sheep Pen");
    j = new Room ("Dead End");
        j->addItem(new Item("Pit Warning Sign", 5, 55));
    j1 = new Room ("Inescapable Pit");

//             (N, E, S, W, Down, Up)
    a1->setExits(NULL, NULL, NULL, NULL, a, NULL);
    a->setExits(f, b, d, c, NULL, a1);
    b->setExits(NULL, NULL, NULL, a, NULL, NULL);
    c->setExits(NULL, a, NULL, NULL, NULL, NULL);
    d->setExits(a, e, NULL, i, NULL, NULL);
    e->setExits(NULL, NULL, NULL, d, NULL, NULL);
    f->setExits(NULL, g, a, h, NULL, NULL);
    g->setExits(NULL, j, NULL, f, NULL, NULL);
    h->setExits(NULL, f, NULL, NULL, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL, NULL, NULL);
    j ->setExits(NULL, NULL, NULL, g, j1, NULL);
    j1 ->setExits(NULL,NULL,NULL,NULL,NULL,NULL);

        currentRoom = a1;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
	cout << endl;
	cout << "end" << endl;
}

void ZorkUL::printWelcome() {
	cout << "start"<< endl;
	cout << "info for help"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
             if (command.hasSecondWord()) {
                 cout << "overdefined input"<< endl;
             }
             else {
                 map();
             }
		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());

        if (location  < 0 )
            cout << "item is not in room" << endl;
        else {
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("teleport") == 0)
    {
        if (command.hasSecondWord()) {
            cout << "overdefined input"<< endl;
        }
        else {
            teleport();
        }
    }

    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void ZorkUL::map(){
    //First Row
    if (currentRoom == h)
        cout << "[*]--[f]--[g]--[i]--[j]" << endl;
    else if (currentRoom == g)
        cout << "[h]--[f]--[*]--[i]--[j]" << endl;
    else if (currentRoom == f)
        cout << "[h]--[*]--[g]--[i]--[j]" << endl;
    else if (currentRoom == i)
        cout << "[h]--[f]--[g]--[*]--[j]" << endl;
    else if (currentRoom == j)
        cout << "[h]--[f]--[g]--[i]--[*]" << endl;
    else if (currentRoom == j1)
        cout << "[h]--[f]--[g]--[i]--[j+]" << endl;
    else
        cout << "[h]--[f]--[g]--[i]--[j]" << endl;
    //Connector
    cout << "      |" << endl;
    //Second Row
    if (currentRoom == c)
        cout << "[*]--[a]--[b]" << endl;
    else if (currentRoom == a)
        cout << "[c]--[*]--[b]" << endl;
    else if (currentRoom == a1)
        cout << "[c]--[a+]--[b]" << endl;
    else if (currentRoom == b)
        cout << "[c]--[a]--[*]" << endl;
    else
        cout << "[c]--[a]--[b]" << endl;
    //Connector
    cout << "      |" << endl;
    //Third Row
    if (currentRoom == i)
        cout << "[*]--[d]--[e]" << endl;
    else if (currentRoom == d)
        cout << "[i]--[*]--[e]" << endl;
    else if (currentRoom == e)
        cout << "[i]--[d]--[*]" << endl;
    else
        cout << "[i]--[d]--[e]" << endl;
    //Legend
    cout << "(* = Player Location | + = Player on different floor)" << endl;
}

void ZorkUL::teleport() {
    int random = rand();
    switch(random%11){
        case 0 :
            currentRoom = a;
            cout << currentRoom->longDescription() << endl;
        break;
        case 1 :
            currentRoom = b;
            cout << currentRoom->longDescription() << endl;
        break;
        case 2 :
            currentRoom = c;
            cout << currentRoom->longDescription() << endl;
        break;
    case 3 :
        currentRoom = d;
        cout << currentRoom->longDescription() << endl;
    break;
    case 4 :
        currentRoom = e;
        cout << currentRoom->longDescription() << endl;
    break;
    case 5 :
        currentRoom = f;
        cout << currentRoom->longDescription() << endl;
    break;
    case 6 :
        currentRoom = g;
        cout << currentRoom->longDescription() << endl;
    break;
    case 7 :
        currentRoom = h;
        cout << currentRoom->longDescription() << endl;
    break;
    case 8 :
        currentRoom = i;
        cout << currentRoom->longDescription() << endl;
    break;
    case 9 :
        currentRoom = j;
        cout << currentRoom->longDescription() << endl;
    break;
    case 10 :
        currentRoom = a1;
        cout << currentRoom->longDescription() << endl;
    break;
    default :
        cout << "Teleport failed" << endl;
    }
}

void ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
		cout << "underdefined input"<< endl;
	else {
		currentRoom = nextRoom;
		cout << currentRoom->longDescription() << endl;
	}
}

string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}
