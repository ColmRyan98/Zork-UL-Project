#include "CommandWords.h"

vector<QString> CommandWords::validCommands;

/**
 * Constructor - initialise the command words.
 */
CommandWords::CommandWords() {

	// Populate the vector if we haven't already.
	if (validCommands.empty()) {
		validCommands.push_back("go");
		validCommands.push_back("quit");
		validCommands.push_back("info");
		validCommands.push_back("map");
		validCommands.push_back("take");
		validCommands.push_back("put");
        validCommands.push_back("teleport");
	}
}

/**
 * Check whether a given QString is a valid command word.
 * Return true if it is, false if it isn't.
 **/
bool CommandWords::isCommand(QString aString) {
	for (unsigned int i = 0; i < validCommands.size(); i++)
	{
		if (validCommands[i].compare(aString) == 0)
			return true;
	}
    // if we get here, the QString was not found in the commands
	return false;
}

/*
 * Print all valid commands to System.out.
 */
void CommandWords::showAll() {
	//Loops through validCommands and prints each to the screen.
	for (unsigned int i = 0; i < validCommands.size(); i++)
	{
       // ui->textEdit->append(validCommands[i]);
        //ui->textEdit->append(" ");
	}
   // ui->textEdit->append("\n");
}
