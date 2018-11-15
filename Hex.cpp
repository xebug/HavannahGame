#include "Hex.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QBrush>
#include "Game.h"

extern Game* game;

#include <QDebug>


Hex::Hex(QGraphicsItem *parent){

    // point pour faire un hexagon: (1,0), (2,0), (3,1), (2,2), (1,2), (0,1)
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
              << QPointF(1,2) << QPointF(0,1);

    int SCALE_BY = 40;
    for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
        hexPoints[i] = hexPoints[i] * SCALE_BY;
    }

    // creer un polygon avec les point
    QPolygonF hexagon(hexPoints);

    setPolygon(hexagon);

    isPlaced = false;
}


bool Hex::getIsPlaced(){
    return isPlaced;
}

QString Hex::getOwner(){
    return owner;
}
QString Hex::getTypePos()
{
    return type;
}

int Hex::getNbBord()
{
    return nbbord;
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event){

                   if (this->getOwner()!=QString("NOONE")) // NE PAS JOUER SI IL A DEJA ETE JOUER
                   {
                       return;
                   }

                   game->playhit(this);

}



void Hex::setTypePos(QString typehex){
    // on dis si c'est un coin, un bord ou un normal(milieu)
    type = typehex;
}

void Hex::setNbBord(int nb)
{
    nbbord=nb;
}

void Hex::setOwner(QString player){

    owner = player;

    // couleur des joueurs
    if (player == QString("NOONE")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }

    if (player == QString("PLAYER0")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::green);
        setBrush(brush);
    }

    if (player == QString("PLAYER1")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }

    if (player == QString("PLAYER2")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::yellow);
        setBrush(brush);
    }

    if (player == QString("PLAYER3")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    }

    if (player == QString("IA0")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::black);
        setBrush(brush);
    }
    if (player == QString("IA1")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::magenta);
        setBrush(brush);
    }
    if (player == QString("IA2")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::cyan);
        setBrush(brush);
    }
    if (player == QString("IA3")){
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::white);
        setBrush(brush);
    }

}

void Hex::setIsPlaced(bool b){
    isPlaced = b;
}


