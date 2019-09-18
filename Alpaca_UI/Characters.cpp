#include "Characters.h"

template<class T>
void SetExtraStat(T a, T b)
{return a=b;}

Characters::Characters(QString description) {
    this->description = description;
    stamina = 100;
}

QString Characters::shortDescription(){
    return this->description;
}

void Characters::addToInvent(Item newItem){
    transferItem = new Item(newItem.getShortDescription(),newItem.getWeight(),newItem.getValue(),newItem.getInventDesc());
    inventory.push_back(*transferItem);
}

void Characters::setStamina(int amount)
{
    stamina = amount;
}

void SetExtraStat(int stamina, int amount); //Pointless alternative to set Stamina;

int Characters::getStamina(){
    return stamina;
}

QString Characters::longDescription(){
    QString temp = "";
    W = 0;
    for(unsigned int i = 0; i < inventory.size() ; i++)
    {
        temp.append(inventory[i].getShortDescription(false));
        W += inventory[i].getWeight();
        temp.append("\n");
    }
    return temp;
}

bool Characters::inventoryCheck(){
    for(unsigned int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i].getShortDescription() == "Alpaca" || inventory[i].getShortDescription() == "Brush")
        {
            for(unsigned int j = i+1; j < inventory.size(); j++)
            {
                if (inventory[j].getShortDescription() == "Alpaca" || inventory[j].getShortDescription() == "Brush")
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Characters::staminaCheck(){ //To check if out of stamina
    if (stamina <= 0)
    {
        stamina = 0;
        return true;
    }
    else{
        return false;
    }
}
