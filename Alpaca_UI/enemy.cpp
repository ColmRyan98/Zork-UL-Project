#include "enemy.h"

enemy::enemy(QString description, int inDamage) :
    Characters (description)
{
    this->damage = inDamage;
}
