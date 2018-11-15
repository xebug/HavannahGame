#include "Player.h"

Player::Player()
{

}



Player::Player(QString name, QString typ)
{
    nom=name;
    type=typ;
}


QString Player::getNameOfPlayer()
{
    return nom;
}

QString Player::getTypeOfPlayer()
{
    return type;
}

void Player::setName(QString nomm)
{
    nom=nomm;
}
