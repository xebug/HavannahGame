#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

class Player
{

public:
    //**  CONSTRUCTEUR **//

    Player();
    Player(QString nom, QString typ);

    //****************************//


    //**  GETTER ET SETTER **//
    void setName(QString nomm);
    QString getNameOfPlayer();
    QString getTypeOfPlayer();
    //****************************//

private:
    QString nom;
    QString type; // HUMAIN OU IA
};

#endif // PLAYER_H
