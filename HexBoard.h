#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <QList>
#include "Hex.h"

class HexBoard{
public:
    //**  CONSTRUCTEUR **//
    HexBoard(int ligne, int colonne, int milieu);
    //****************************//

    void newBoard();

    //** GESTION DES HEXAGONS **//
    QList<Hex*> getHexes(); // retourne la liste des hexagon placé
    Hex* tableauhex[50][50]; // tableau qui contient les hexagons de la liste des hexagons placés
    int ligne;
    int colonne;
    int milieu;
    //****************************//




private:

    void assignBord(int mid_long, int mid_larg, int longueur, int largeur, Hex * hexcourant); // lui assigne son numero du bord
    void assignType(); // lui assigne un type (coin, bord..)
    QList<Hex*> hexes; // liste qui contient les hexagons placé



};

#endif // HEXBOARD_H

