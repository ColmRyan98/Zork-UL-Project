#include "item.h"

Item::Item (QString inDescription, int inWeightGrams, float inValue, QString inInDesc) {
    description = inDescription;
    setWeight(inWeightGrams);
    value = inValue;
    inventDescription = inInDesc;

}

Item::Item (QString inDescription, int inWeightGrams, float inValue) {
	description = inDescription;
	setWeight(inWeightGrams);
	value = inValue;
    inventDescription = inDescription;
}

Item::Item(QString inDescription) {
	description = inDescription;
}

void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
	   weightGrams = inWeightGrams;
}

QString Item::getInventDesc(){return inventDescription;}

int Item::getWeight(){return this->weightGrams;}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "value invalid, must be 0<value<9999" ;
    else
	   value = inValue;
}

float Item::getValue(){return this->value;}


/**void Item::setWeaponCheck(int isWeapon)
{
    if(isWeapon > 0 || isWeapon < 0)
        cout << "Item not a weapon" ;
    else
        cout << "Item is a weapon" ;
}*/

QString Item::getShortDescription(bool showOrig)
{
    if(showOrig == true)
    {
        return (inventDescription + " (" + description + ")");
    }
    else
    {
        return inventDescription;
    }
}

QString Item::getShortDescription(void)
{
	return description;
}

QString Item::getLongDescription()
{
	return " item(s), " + description + ".\n";
}


