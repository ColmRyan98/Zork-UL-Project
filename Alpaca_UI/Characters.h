#ifndef Characters_H_
#define Characters_H_
#include "ZorkUL.h"
#include "item.h"

#include "QString"
#include <vector>
using std::vector;
using namespace std;



class Characters {
private:
    QString description;
    vector<Item> inventory;
    int stamina;
    Item *transferItem;

public:
    Characters(QString description);
    QString shortDescription();
    QString longDescription();
    void addToInvent(Item newItem);
    void setStamina(int amount);
    int getStamina();
    bool staminaCheck();
    bool inventoryCheck();
    int W;
};



#endif /*Characters_H_*/
