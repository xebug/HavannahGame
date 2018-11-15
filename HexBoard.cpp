#include "HexBoard.h"
#include "Game.h"
#include <qmath.h>
#include <QDebug>


extern Game* game;

HexBoard::HexBoard(int ligne, int colonne, int milieu){
    this->ligne=ligne;
    this->colonne=colonne;
    this->milieu=milieu;

}



QList<Hex *> HexBoard::getHexes(){
    return hexes;
}




void HexBoard::newBoard()
{
    QPolygonF polygon;
    qreal side = 30;
    qreal dx = qSqrt(3)/2 * side;
    polygon
            << QPointF(dx, -side/2)
            << QPointF(0, -side)
            << QPointF(-dx, -side/2)
            << QPointF(-dx, side/2)
            << QPointF(0, side)
            << QPointF(dx, side/2);




    int h = this->ligne;
    int w = this->colonne;
    int mid_h = h/2;
    int mid_w = w/2;

    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(qAbs(mid_h - r) + qAbs(mid_w - c) > this->milieu
                    || (r % 2 != c % 2))
            {
                // l'hexagon ne sera pas afficher, creer quand meme et ajouter au tableau pour eviter des crash lors de comparaison
                Hex * hexagon = new Hex(0);
                hexagon->setOwner(QString("NOTONBOARD"));
                hexagon->setIsPlaced(true);
                hexagon->setToolTip(QString::number(r) + ";" + QString::number(c));
                tableauhex[r][c]=hexagon;
            }
            else
            {

                Hex * hexagon = new Hex(0);// Creer un hexagon
                hexagon->setPolygon(polygon);
                game->scene->addItem(hexagon); //l'ajoute a la scene
                hexagon->setPos(dx * c+300, side * 1.5 * r+150); // le place a la bonne position
                hexes.append(hexagon); // l'ajoute a la liste des hexagons placés
                hexagon->setOwner(QString("NOONE")); // initialise son proprietaire
                hexagon->setIsPlaced(true); // le met placé
                hexagon->setToolTip(QString::number(r) + ";" + QString::number(c)); // ajoute sa position
                tableauhex[r][c]=hexagon; // l'ajoute au tableau

                assignBord(mid_h,mid_w,r,c,hexagon); // initialise son bord

            }

        }

    }
    assignType(); // initialise son type
}

void HexBoard::assignBord(int mid_long, int mid_larg, int longueur, int largeur, Hex * hexCourant)
{

    if (longueur==mid_long*2)
    {
        hexCourant->setNbBord(4);

    }

    if (longueur==0)
    {
        hexCourant->setNbBord(1);
    }


    if (longueur > 0 && longueur < mid_long && largeur < mid_larg)
    {
        hexCourant->setNbBord(2);
    }

    if (longueur < (mid_long*2) && longueur > mid_long && largeur < mid_larg)
    {
        hexCourant->setNbBord(3);
    }

    if (longueur > 0 && longueur < mid_long && largeur > mid_larg)
    {
        hexCourant->setNbBord(6);
    }

    if (longueur < (mid_long*2) && longueur > mid_long && largeur > mid_larg)
    {
        hexCourant->setNbBord(5);
    }

}



void HexBoard::assignType()
{
    int xVoisin1,xVoisin2,xVoisin3,xVoisin4,xVoisin5,xVoisin6,yVoisin1,yVoisin2,yVoisin3,yVoisin4,yVoisin5,yVoisin6=0;

    //Si il a deux deuxv voisin "NOTONBOARD" c'est un bord
    // Si il en a trois, c'est un coin
    // sinon normal
    for (size_t i = 0, n = getHexes().size(); i < n; ++i){
            if (getHexes()[i]->getOwner() != QString("NOTONBOARD")) // HEXAGON JOUABLE
            {

                int typedecoin=0;
                QString position = getHexes()[i]->toolTip(); // on recupere sa position
                    int  a = position.split(";")[0].toInt(); // converti en int
                    int b = position.split(";")[1].toInt();

                    // calcul de ses voisins :

                    // voisin 1 :
                    xVoisin1 = a;
                    yVoisin1 = b+2;

                    // voisin 2 :
                    xVoisin2 = a;
                    yVoisin2 = b-2;


                    // voisin 3 :
                    xVoisin3 = a+1;
                    yVoisin3 = b+1;


                    // voisin 4 :
                    xVoisin4 = a+1;
                    yVoisin4 = b-1;

                    // voisin 5 :
                    xVoisin5 = a-1;
                    yVoisin5 = b-1;


                    // voisin 6 :
                    xVoisin6 = a-1;
                    yVoisin6 = b+1;

                    if(game->aQuiAppartientCetHexV2(xVoisin1,yVoisin1)==QString("NOTONBOARD"))
                    {
                        typedecoin++;
                    }


                    if(game->aQuiAppartientCetHexV2(xVoisin2,yVoisin2)==QString("NOTONBOARD"))
                    {
                        typedecoin++;
                    }

                    if(game->aQuiAppartientCetHexV2(xVoisin3,yVoisin3)==QString("NOTONBOARD"))
                    {
                        typedecoin++;
                    }

                    if(game->aQuiAppartientCetHexV2(xVoisin4,yVoisin4)==QString("NOTONBOARD"))
                    {
                        typedecoin++;

                    }

                    if(game->aQuiAppartientCetHexV2(xVoisin5,yVoisin5)==QString("NOTONBOARD"))
                    {
                        typedecoin++;

                    }

                    if(game->aQuiAppartientCetHexV2(xVoisin6,yVoisin6)==QString("NOTONBOARD"))
                    {
                        typedecoin++;
                    }

                    // on attribue maintenant le type de coin a cet hexagon
                    if (typedecoin<1)
                    {
                        getHexes()[i]->setTypePos(QString("NORMAL"));

                    }

                    if (typedecoin==2)
                       {

                        getHexes()[i]->setTypePos(QString("BORD"));

                    }
                    if (typedecoin==3)
                       {
                        getHexes()[i]->setTypePos(QString("COIN"));

                    }

            }

        }
}



