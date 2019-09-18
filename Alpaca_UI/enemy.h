#ifndef ENEMY_H
#define ENEMY_H
#include "Characters.h"

class enemy : public Characters
{
private:
    int damage;
public:
    enemy(QString description, int damage);
};

#endif // ENEMY_H
