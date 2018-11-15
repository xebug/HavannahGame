#ifndef HEX_H
#define HEX_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class Hex: public QGraphicsPolygonItem{
public:
    //**  CONSTRUCTEUR **//
    Hex(QGraphicsItem* parent=NULL);
    //****************************//


    //** GETTERS **//
    bool getIsPlaced(); // retourne si l'hexagon a bien été placé
    QString getOwner(); //retourne le proprietaire de l'hexagon
    QString getTypePos(); //retourne le type de position, si c'est un coin, un bord..
    int getNbBord(); // retourne le numero du bord ou se situe l'hexagon
    //****************************//

    //** GESTION SOURIS **//
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    //****************************//


    //** SETTERS **//
    void setOwner(QString player); //met le proprietaire a cet hexagon
    void setIsPlaced(bool b); //met si il a été placé
    void setTypePos(QString typehex); // met son type de position (coin, bord, normal)
    void setNbBord(int nb); // met son numéro de bord (1,2,3,4,5,6)
    //****************************//


private:
    bool isPlaced; // placé ou non
    QString owner; // proprietaire de l'hexagon initialisé a NOONE
    QString type; // type de l'hexagon (bord, coin ..)
    int nbbord; // numero du bord ou se trouve l'hexagon

};

#endif // HEX_H

