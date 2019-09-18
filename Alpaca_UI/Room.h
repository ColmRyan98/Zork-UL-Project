#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include <QString>
using namespace std;
using std::vector;

class Room {

private:
    friend class MainWindow;
    vector <Item> itemsInRoom;
    QString description;
    map<QString, Room*> exits;
    QString exitString();
    Item *invalid;

public:
    int numberOfItems();
    Room(QString description);
    void setExits(Room *North, Room *East, Room *South, Room *West, Room *Down, Room *Up);
    QString shortDescription();
    QString longDescription();
    Room* nextRoom(QString direction);
    void addItem(Item *inItem);
    QString displayItem();
    int isItemInRoom(QString inString);
    void removeItemFromRoom(QString removeIt);
    Item getItem(QString search, QString other, unsigned int a);
};

#endif
