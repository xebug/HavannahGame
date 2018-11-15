#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "HexBoard.h"
#include <QMouseEvent>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    //** CONSTRUCTEUR **//
    Game(QWidget* parent=NULL);

    //****************************//


    //** MENU **//
    void displayMainMenu(); // Menu principal
    void displayPersoMenu(int a); // Menu personnalise
    //****************************//

    //** TOUR DES JOUEURS **//
    QString getWhosTurn(); // retourne le nom du joueur a qui est le tour en QString
    void setWhosTurn(QString player); // met le nom du joueur a qui est le tour en QString
    int getWhosTurnIndex(); // retourne l'entier qui represente l'index du joueur a qui est le tour
    void setWhosTurnIndex(int index); //met l'entier qui represente l'index du joueur a qui est le tour
    void nextPlayersTurn(); // Fonction qui passe au tour suivant
    int getNbPlayer(); // retourne le nombre de joueur humain
    int getNbPlayerIA(); // retourne le nombre de joueur IA
    //****************************//




    //** Fonction du jeu **//

    void playhit(Hex * hexToReplace); // Fonction appelé pour placé jouer un coup
    bool verifBoucle(int a, int b); // Fonction qui verifie si une boucle a ete effectué
    bool verifPont(); // Fonction qui verifie si un pont a été effectué
    bool verifFourche(); // Fonction qui verifie si une fourche a été effectué
    bool AppartientListeVisit(int a, int b); // Fonction qui regarde si la position (a;b) passer en parametre est dans la liste des visité
    QString aQuiAppartientCetHexV2(int a, int b); // Fonctin qui retourne qui est le proprietaire de l'hexagon a la position (a;b)
    bool partiefini(); // Fonction qui verifie si les coups simulé par alpha beta mettent fin a la partie
    bool verificationCoup(Hex * hexdepart); //Fonction qui verifie si le dernier coup jouer est gagnant
    bool verificationCoupGagnant(int xbase, int ybase, int a, int b, int xprecedent, int yprecedent, QString proprietaire, Hex * hexcourant); //Va faire une boucle pour ajouter les voisin recursivement dans HexVisit et HexVisitFourche
    int evaluation(); //Fonction qui va attribué une valeurs au coup simulé par alpha beta
    int score(Hex * hexdepart); // Fonction appelé par evaluation pour calculer un score a attribué au coup simulé selon des critères
    void DecisionAlphaBeta(); // Fonction principale alphabeta qui va jouer le meilleur coup a jouer selon les valeurs retourner par Decision Alpha Beta
    int AlphaBeta(int alpha, int beta, int profondeur, bool etatmax); // Fonction qui va retourné simulé chaque coup possible et leurs attribué une valeur

    //****************************//



    //** FIN DE PARTIE **//
    void displayGameOverWindow(QString textToDisplay); // affichage pour fin de la partie
    //****************************//


    void displayGateauWindow(QString text);




    // attribues

    QString gagnant; // le gagnant de la partie
    bool isFinish=false; //utilisé pour voir si la partie est fini
    bool isFinishVirtual=false; //utilisé pour voir si la partie est fini grace a un coup simulé
    QGraphicsScene* scene; // scene de qt
    HexBoard* hexBoard; // le plateau
    Hex* coupIA; // dernier coup simulé par l'ia
    Hex* coupHUMAIN; // dernier coup simulé par l'ia pour son adversaire humain
    int nbCoupJouer; // nombre de coup jouer dans la partie en cours
    class Player * tabJoueur[10]; // tableau des joueurs dans la partie (utilisé pour avoir jusqu'a 8 joueur dans la même partie)
    int TaillePlateau=2; // taille du plateau modifié par un slot dans le menu personnalisé (valeur possible 1,2,3) qu'on se servira pour creer le plateau
    bool regledugateau=false; // si on utilise la regle du gateau ou non



public slots: // slot qt (appelé par un signal)
    void start(); // demarrer une partie 1vs1 humain
    void start_ia(); // demarrer une partie vs ia
    void setNbPlayer(int a); // change le nombre de player humain (connecté au signal de la spin box du menuperso)
    void start_perso(); // permet d'appliquer les changement effectué dans le menu perso
    void restartGame(); //recommencer la partie
    void setTaillePlateau(int a); // meme principe que pour setNbplayer , pour la taille du plateau
    void slotdisplayPersoMenu(); //affiche le menu perso
    void setNbPlayerIA(int nb); //meme principe que pour setnbplayer, pour le nombre de joueur ia
    void setRegleGateau(bool active); //mettre la regle du gateau a true ou a false (connecté a une check box)
    void regledugateauaccepter(); // quand le joueur accepte la regle du gateau
    void regledugateaurefuser(); // quand le joueur refuser la regle du gateau

private:


    // méthodes
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity); //utilise pour l'affichage de zone comme pour la fin de partie
    void drawGUI(); // utilisé pour afficher des informations pendant la partie
    QList<Hex*> getHexVisit(); // retourne liste qui contient tous les voisin visité pour une boucle
    QList<Hex*> getHexVisitFourche(); // retourne liste qui contient tous les voisins visité pour fourche et pont



    // attribues

    int nbplayer=1; // nb de joueur humain
    int nbplayerIA=0; // nb de joueur ia
    int whosTurnIndex; // index pour le tableau de joueur
    QString whosTurn_; // retourne le nom du joueur qui doit jouer
    QGraphicsTextItem* whosTurnText; // pour l'afficher pendant la partie
    QList<Hex*> HexVisit; // liste qui contient tous les voisin visité pour une boucle
    QList<Hex*> HexVisitFourche; // liste qui contient tous les voisins visité pour fourche et pont



};

#endif // GAME_H
