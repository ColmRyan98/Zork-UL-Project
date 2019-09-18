#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <QString>

using namespace std;

class Command {
private:
    QString commandWord;
    QString secondWord;

public:
    Command(QString firstWord, QString secondWord);
    QString getCommandWord();
    QString getSecondWord();
	bool isUnknown();
	bool hasSecondWord();
};

#endif /*COMMAND_H_*/
