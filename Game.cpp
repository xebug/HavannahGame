#include "Game.h"
#include "HexBoard.h"
#include "Button.h"
#include "Player.h"
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include "qlineedit.h"
#include <QSpinBox>
#include <QList>
#include <QGraphicsProxyWidget>
#include "qgraphicsproxywidget.h"
#include <stdlib.h> // srand() and rand()
#include <time.h> // time()
#include <QDebug>


Game::Game(QWidget *parent){
    // initialisation de la fenetre
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);
    // initialisation de la scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);




}

// ***************************************************************************************** //
// ********** GESTION DE LA PARTIE, DEMARRAGE, REDEMARRAGE, ETC... ************************* //
// ***************************************************************************************** //


void Game::start(){ // partie directement contre humain
    //initialiser la partie
    nbplayer=2;
    tabJoueur[0]=new Player("PLAYER"+QString::number(0),"HUMAIN");
    tabJoueur[1]=new Player("PLAYER"+QString::number(1),"HUMAIN");
    nbCoupJouer = 0;

    scene->clear(); // pour clear le menu

    if(TaillePlateau==1){hexBoard = new HexBoard(7,11,8);}
    if(TaillePlateau==2){hexBoard = new HexBoard(9,17,9);}
    if(TaillePlateau==3){hexBoard = new HexBoard(11,23,10);}
    hexBoard->newBoard();
    drawGUI();

}


void Game::start_ia(){ // on commence une partie directement contre L'ia
    //initialiser la partie
    nbplayer=1;
    nbplayerIA=1;
    tabJoueur[0]=new Player("PLAYER"+QString::number(0),"HUMAIN");
    tabJoueur[1]=new Player("IA"+QString::number(0),"IA");
    nbCoupJouer = 0;
    scene->clear();// pour clear le menu

    if(TaillePlateau==1){hexBoard = new HexBoard(7,11,8);}
    if(TaillePlateau==2){hexBoard = new HexBoard(9,17,9);}
    if(TaillePlateau==3){hexBoard = new HexBoard(11,23,10);}
    hexBoard->newBoard();
    drawGUI();

}

void Game::start_perso(){

    // initialiser la partie

    nbCoupJouer = 0;

    for(int i = 0; i<getNbPlayer(); i++)
    {
        tabJoueur[i]=new Player("PLAYER"+QString::number(i),"HUMAIN");

    }

    for(int i = 0; i<getNbPlayerIA(); i++)
    {
      tabJoueur[getNbPlayer()+i]=new Player("IA"+QString::number(i),"IA");

    }

    scene->clear(); // clear le menu

    if(TaillePlateau==1){hexBoard = new HexBoard(7,11,8);}
    if(TaillePlateau==2){hexBoard = new HexBoard(9,17,9);}
    if(TaillePlateau==3){hexBoard = new HexBoard(11,23,10);}

   hexBoard->newBoard();
    drawGUI();

}


void Game::restartGame(){


    hexBoard->getHexes().clear();
    HexVisitFourche.clear();
    HexVisit.clear();
    scene->clear();
    isFinish=false;
    gagnant="";
    start_perso();

}

void Game::regledugateauaccepter()
{
    if(nbCoupJouer>1){return;}

    for (size_t i = 0, n = hexBoard->getHexes().size(); i < n; ++i)
    {
        if (hexBoard->getHexes()[i]->getOwner()==QString("PLAYER0")) // on cherche le premier hexagon du premier joueur, il y en aura forcement que un
        {
            hexBoard->getHexes()[i]->setOwner(tabJoueur[getWhosTurnIndex()+1]->getNameOfPlayer()); // on change son proprietaire avec le prochain joueur
        }

    }

    regledugateau=false;
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(true);
    }

    nbCoupJouer++;

}


void Game::regledugateaurefuser()
{
    if(nbCoupJouer>1){return;}


    regledugateau=false;
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(true);
    }
    nbCoupJouer++;
    nextPlayersTurn();
}


void Game::displayPersoMenu(int a){


    scene->clear();

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Personnaliser la partie"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    QCheckBox * reglegateau = new QCheckBox();
    QGraphicsProxyWidget* regleg = scene->addWidget(reglegateau);
    regleg->setPos(570,500);
    connect(reglegateau,SIGNAL(toggled(bool)),this,SLOT(setRegleGateau(bool)));

    QLabel * reglegato = new QLabel();
    QGraphicsProxyWidget* reglogato = scene->addWidget(reglegato);
    reglogato->setPos(450,500);
    reglegato->setText("Regle du gâteau : ");



    QLabel * nombrejoueur = new QLabel();
    QGraphicsProxyWidget* pproxynbjoueur = scene->addWidget(nombrejoueur);
    pproxynbjoueur->setPos(425,203);
    nombrejoueur->setText("Nombre de joueur : ");

    QLabel * nombreia = new QLabel();
    QGraphicsProxyWidget* pproxynbjoueuria = scene->addWidget(nombreia);
    pproxynbjoueuria->setPos(410,303);
    nombreia->setText("Nombre de joueur IA : ");

    QLabel * tailleplateau = new QLabel();
    QGraphicsProxyWidget* pproxytailleplateau = scene->addWidget(tailleplateau);
    pproxytailleplateau->setPos(435,403);
    tailleplateau->setText("Taille du plateau : ");

    QSpinBox * nbJoueur = new QSpinBox();
    QGraphicsProxyWidget* pproxy = scene->addWidget(nbJoueur);
    pproxy->setPos(550,200);
    nbJoueur->setMinimum(1);
    nbJoueur->setMaximum(4);
    connect(nbJoueur,SIGNAL(valueChanged(int)),this,SLOT(setNbPlayer(int)));

    QSpinBox * nbJoueurIA = new QSpinBox();
    QGraphicsProxyWidget* pproxyIA = scene->addWidget(nbJoueurIA);
    pproxyIA->setPos(550,300);
    nbJoueurIA->setMinimum(0);
    nbJoueurIA->setMaximum(4);
    connect(nbJoueurIA,SIGNAL(valueChanged(int)),this,SLOT(setNbPlayerIA(int)));

    QSpinBox * tailleP = new QSpinBox();
    QGraphicsProxyWidget* pproxyplateau = scene->addWidget(tailleP);
    pproxyplateau->setPos(550,400);
    tailleP->setMinimum(1);
    tailleP->setMaximum(3);
    tailleP->setValue(2);
    connect(tailleP,SIGNAL(valueChanged(int)),this,SLOT(setTaillePlateau(int)));


    Button* playButton = new Button(QString("Valider et jouer"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 540;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start_perso()));
    scene->addItem(playButton);


    Button* quitButton = new Button(QString("Quitter"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 600;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);


}

void Game::displayMainMenu(){

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Havannah"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);


    Button* playButton = new Button(QString("Nouvelle partie contre humain"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 200;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);


    Button* playButton2 = new Button(QString("Nouvelle partie contre IA"));
    int cxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int cyPos = 300;
    playButton2->setPos(cxPos,cyPos);
    connect(playButton2,SIGNAL(clicked()),this,SLOT(start_ia()));
    scene->addItem(playButton2);


    Button* playButton3 = new Button(QString("Nouvelle partie personnalisé"));
    int dxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int dyPos = 400;
    playButton3->setPos(dxPos,dyPos);
    connect(playButton3,SIGNAL(clicked()),this,SLOT(slotdisplayPersoMenu()));
    scene->addItem(playButton3);


    Button* quitButton = new Button(QString("Quitter"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 500;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}


void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}




void Game::drawGUI(){


    // place whosTurnText
    whosTurnText = new QGraphicsTextItem();
    setWhosTurn(tabJoueur[0]->getNameOfPlayer());
    setWhosTurnIndex(0);
    whosTurnText->setPos(490,0);
    scene->addItem(whosTurnText);

}


void Game::displayGameOverWindow(QString textToDisplay){
    // desactiver tous les autres item sur la scene
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    drawPanel(0,0,1024,768,Qt::black,0.65);

    drawPanel(312,184,400,400,Qt::lightGray,0.75);

    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(410,300);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    Button* quit = new Button(QString("Quit"));
    quit->setPos(410,375);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(460,225);
    scene->addItem(overText);


}

void Game::displayGateauWindow(QString textToDisplay){
    // desactiver tous les autres item sur la scene

    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    Button* oui = new Button(QString("Oui"));
    oui->setPos(750,100);
    scene->addItem(oui);
    connect(oui,SIGNAL(clicked()),this,SLOT(regledugateauaccepter()));

    Button* non = new Button(QString("Non"));
    non->setPos(750,150);
    scene->addItem(non);
    connect(non,SIGNAL(clicked()),this,SLOT(regledugateaurefuser()));

    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(750,70);
    scene->addItem(overText);






}

// ***************************************************************************************** //

// ***************************************************************************************** //



// ***************************************************************************************** //
// **************************** GETTER ET SETTER... **************************************** //
// ***************************************************************************************** //

int Game::getNbPlayer()
{
    return nbplayer;
}


int Game::getNbPlayerIA()
{
    return nbplayerIA;
}


void Game::setNbPlayerIA(int nb){
    nbplayerIA=nb;
}

void Game::setTaillePlateau(int a)
{
    TaillePlateau=a;
}

void Game::slotdisplayPersoMenu()
{
    displayPersoMenu(0);
}



void Game::setNbPlayer(int a)
{
    nbplayer=a;
}

void Game::setRegleGateau(bool active)
{
    if(active==true)
    {
        regledugateau=true;
    }
    else
    {
        regledugateau=false;
    }
}



QString Game::getWhosTurn(){
    return whosTurn_;
}

void Game::setWhosTurn(QString player){
    // change the QString
    whosTurn_ = player;

    // change the QGraphicsTextItem
    whosTurnText->setPlainText(QString("C'est au tour de : ") + player);
}

int Game::getWhosTurnIndex()
{
    return whosTurnIndex;
}

void Game::setWhosTurnIndex(int index)
{
    whosTurnIndex=index;
}



QList<Hex *> Game::getHexVisit(){
    return HexVisit;
}

QList<Hex *> Game::getHexVisitFourche(){
    return HexVisitFourche;
}


// ***************************************************************************************** //

// ***************************************************************************************** //



// ***************************************************************************************** //
// **************************** FONCTION DU JEU ... **************************************** //
// ***************************************************************************************** //




void Game::playhit(Hex * hexToReplace){
    // on attribue son nouveau proprietaire
    hexToReplace->setOwner(getWhosTurn());

    nbCoupJouer++;

    if (nbCoupJouer >= hexBoard->getHexes().size()){ // verifier si le plateau n'est pas plein
        displayGameOverWindow(QString(" Match nul !"));
    }
    else
    {

        verificationCoup(hexToReplace); // verifie si le coup est gagnant, si oui met isFinish a true
        if (isFinish)
        {
            displayGameOverWindow(QString(gagnant + "a gagner"));

        }
    }

   nextPlayersTurn(); // tour au prochain joueur
}



void Game::nextPlayersTurn(){

    if(regledugateau==true && nbCoupJouer==1 && tabJoueur[getWhosTurnIndex()+1]->getTypeOfPlayer()==QString("HUMAIN"))//regle du gateau
    {

        displayGateauWindow(QString("Voulez vous utilisez la regle du gateau"));
        return;

    }

    if (getWhosTurnIndex() == (getNbPlayer()+getNbPlayerIA())-1) // Si l'index arrive a la fin du tableau le remettre a 0
    {
        setWhosTurnIndex(0);
        setWhosTurn(tabJoueur[getWhosTurnIndex()]->getNameOfPlayer());
        return;
     }

        setWhosTurnIndex(getWhosTurnIndex()+1);
        setWhosTurn(tabJoueur[getWhosTurnIndex()]->getNameOfPlayer());

     if (tabJoueur[getWhosTurnIndex()]->getTypeOfPlayer()==QString("IA"))// SI CEST A L IA DE JOUER
     {
       DecisionAlphaBeta(); // on lance min max
     }


}


void Game::DecisionAlphaBeta()
{
    coupIA=hexBoard->getHexes()[1]; // initialise le coup simulé pour l'ia
    coupHUMAIN=hexBoard->getHexes()[2]; // initialise le coup simulé pour l'adversaire

    Hex * meilleurcoup=NULL; // Le coup qui sera jouer
    int alpha = -10000000000000;
    int val=0;
    for (size_t i = 0, n = hexBoard->getHexes().size(); i < n; ++i)
    {
        if (hexBoard->getHexes()[i]->getOwner()==QString("NOONE")) // pour tous les hexagon placé libre
        {
        hexBoard->getHexes()[i]->setOwner(tabJoueur[getWhosTurnIndex()]->getNameOfPlayer()); // simuler le coup pour l'ia actuelle
        val= AlphaBeta(alpha,100000,2, false);
        hexBoard->getHexes()[i]->setOwner(QString("NOONE")); // simuler le coup pour l'ia actuelle
        if(val>alpha || ( (val == alpha) && (rand()%10 == 5) ) ) // rand pour ne pas que le joueur joue toujours au premiere case
            {
            qDebug()<<"Nouveau meilleur coup a une valeur de "<<val;
            qDebug()<<hexBoard->getHexes()[i]->toolTip();

                meilleurcoup = hexBoard->getHexes()[i];
                alpha=val;
            }
        }
    }
 if(meilleurcoup==NULL)
 {
     return;
 }
playhit(meilleurcoup);
}

int Game::AlphaBeta(int alpha, int beta, int profondeur, bool etatmax)
{
    if(profondeur<=0 || partiefini()==true) // si on arrive a 0 ou que un coup simulé est gagnant
    {
        return evaluation();
    }
    if (etatmax==true) // Si on maximise
    {

        for (size_t i = 0, n = hexBoard->getHexes().size(); i < n; ++i)
        {
            if (hexBoard->getHexes()[i]->getOwner()==QString("NOONE")) // pour tous les hexagon placé libre
            {
                int val = -100000;
                hexBoard->getHexes()[i]->setOwner(QString("IA0")); // simuler le coup pour l'ia
                coupIA=hexBoard->getHexes()[i];
                val = std::max(val,AlphaBeta(alpha,beta,profondeur-1,false));
                hexBoard->getHexes()[i]->setOwner(QString("NOONE")); // retirer le coup pour l'ia
                if(val>beta)
                {
                  return val;
                }
                alpha=std::max(alpha,val);

            }

         }
       return alpha;
    }
    else // Si on minimise
    {

        for (size_t i = 0, n = hexBoard->getHexes().size(); i < n; ++i)
        {
            if (hexBoard->getHexes()[i]->getOwner()==QString("NOONE")) // pour tous les hexagon placé libre
            {

                int val = 100000;
                hexBoard->getHexes()[i]->setOwner(QString("PLAYER0")); // simuler le coup pour l'adversaire
                coupHUMAIN=hexBoard->getHexes()[i];
                val = std::min(val,AlphaBeta(alpha,beta,profondeur-1,true));
                hexBoard->getHexes()[i]->setOwner(QString("NOONE")); // retirer le coup pour l'adversaire
                if(alpha>val)
                {
                    return val;
                }
                beta=std::min(beta,val);

            }

         }
       return beta;
    }

}



bool Game::partiefini()
{

    if(coupIA->getOwner()!=QString("NOONE"))
    {
        verificationCoup(coupIA); // On lance une vefication pour le coup simulé ia
              if(isFinish) // si c'est un coup gagnant
              {
                  isFinishVirtual=true; // on met que un coup virtuel est gagnant
                  isFinish=false; // on remet a faux sinon ça arretera la partie avant qu'il soit jouer
                  gagnant=coupIA->getOwner(); // on met le gagnant

                  return true;
              }
              else
              {
                return false;
            }

        }

    if(coupHUMAIN->getOwner()!=QString("NOONE"))
    {
        verificationCoup(coupHUMAIN); // On lance une vefication pour le coup simulé adversaire
              if(isFinish) // si c'est un coup gagnant
              {
                  isFinishVirtual=true; // on met que un coup virtuel est gagnant
                  isFinish=false; // on remet a faux sinon ça arretera la partie avant qu'il soit jouer
                  gagnant=coupHUMAIN->getOwner();  // on met le gagnant
                  return true;
              }
              else
              {
                return false;
            }

        }
    return false;

   return false;
}




int Game::score(Hex * hexdepart)
{
    int score=0;

    int xVoisin1,xVoisin2,xVoisin3,xVoisin4,xVoisin5,xVoisin6,yVoisin1,yVoisin2,yVoisin3,yVoisin4,yVoisin5,yVoisin6=0; //position de ces 6 voisins
    QString position = hexdepart->toolTip(); // on recupere sa position
    QString proprietaire = hexdepart->getOwner(); // son proprietaire
    int  a = position.split(";")[0].toInt(); // converti en int car sa position recuperer est en QString
    int b = position.split(";")[1].toInt(); // converti en int car sa position recuperer est en QString



    // voisin 1 :
    xVoisin1 = a;
    yVoisin1 = b+2;
    Hex * voisin1 = hexBoard->tableauhex[xVoisin1][yVoisin1];

    // voisin 2 :
    xVoisin2 = a;
    yVoisin2 = b-2;
    Hex * voisin2 = hexBoard->tableauhex[xVoisin2][yVoisin2];


    // voisin 3 :
    xVoisin3 = a+1;
    yVoisin3 = b+1;
    Hex * voisin3 = hexBoard->tableauhex[xVoisin3][yVoisin3];


    // voisin 4 :
    xVoisin4 = a+1;
    yVoisin4 = b-1;
    Hex * voisin4 = hexBoard->tableauhex[xVoisin4][yVoisin4];

    // voisin 5 :
    xVoisin5 = a-1;
    yVoisin5 = b-1;
    Hex * voisin5 = hexBoard->tableauhex[xVoisin5][yVoisin5];


    // voisin 6 :
    xVoisin6 = a-1;
    yVoisin6 = b+1;
    Hex * voisin6 = hexBoard->tableauhex[xVoisin6][yVoisin6];




    if(aQuiAppartientCetHexV2(xVoisin1,yVoisin1)==proprietaire)
    {
        score=score+20;
    }


    if(aQuiAppartientCetHexV2(xVoisin2,yVoisin2)==proprietaire)
    {
        score=score+20;
    }


    if(aQuiAppartientCetHexV2(xVoisin3,yVoisin3)==proprietaire)
    {
        score=score+10;
    }


    if(aQuiAppartientCetHexV2(xVoisin4,yVoisin4)==proprietaire)
    {
        score=score+10;
    }


    if(aQuiAppartientCetHexV2(xVoisin5,yVoisin5)==proprietaire)
    {
        score=score+10;
    }


    if(aQuiAppartientCetHexV2(xVoisin6,yVoisin6)==proprietaire)
    {
        score=score+10;
    }

    int nbQuiToucheEnnemi=0;

    if(aQuiAppartientCetHexV2(xVoisin1,yVoisin1)==QString("PLAYER0"))
    {

            nbQuiToucheEnnemi++;
   }

    if(aQuiAppartientCetHexV2(xVoisin2,yVoisin2)==QString("PLAYER0"))
    {

            nbQuiToucheEnnemi++;
   }

    if(aQuiAppartientCetHexV2(xVoisin3,yVoisin3)==QString("PLAYER0"))
    {

            nbQuiToucheEnnemi++;
   }

    if(aQuiAppartientCetHexV2(xVoisin4,yVoisin4)==QString("PLAYER0"))
    {

            nbQuiToucheEnnemi++;
   }

    if(aQuiAppartientCetHexV2(xVoisin5,yVoisin5)==QString("PLAYER0"))
    {

            nbQuiToucheEnnemi++;
   }

    if(aQuiAppartientCetHexV2(xVoisin6,yVoisin6)==QString("PLAYER0"))
    {

            nbQuiToucheEnnemi++;
   }
    if(nbQuiToucheEnnemi>0){ score=score+10; }
    if(nbQuiToucheEnnemi>=3){score=score-500;}


    int nbami=0;

    if(aQuiAppartientCetHexV2(xVoisin1,yVoisin1)==QString("IA0"))
    {

            nbami++;
   }

    if(aQuiAppartientCetHexV2(xVoisin2,yVoisin2)==QString("IA0"))
    {

            nbami++;
   }

    if(aQuiAppartientCetHexV2(xVoisin3,yVoisin3)==QString("IA0"))
    {

            nbami++;
   }

    if(aQuiAppartientCetHexV2(xVoisin4,yVoisin4)==QString("IA0"))
    {

            nbami++;
   }

    if(aQuiAppartientCetHexV2(xVoisin5,yVoisin5)==QString("IA0"))
    {

            nbami++;
   }

    if(aQuiAppartientCetHexV2(xVoisin6,yVoisin6)==QString("IA0"))
    {

            nbami++;
   }
    if(nbami==1){ score=score+50; }
    if(nbami==2){ score=score+40; }

    if(nbami>=3){score=score-50;}



    // COLLER A DEUX ADVERSAIRE =  POINT EN PLUS
    // COLLER A TROIS = POINT EN MOINS CAR AU MILIEU BOUCLE
    //Parei pour lui même, si il se met au milieu de sa propre boucle = point en moins


    //Pour qu'il soit encore meilleur : donner encore plus de point si les deux qu'il touche son d'un coté opposé
    // exemple : un du coté droit et un du coté gauche : favorise les pont etc

   return score;
}


int Game::evaluation()
{
   if(isFinishVirtual==true)
   {   qDebug()<<"fini";

       if(gagnant==QString("IA0"))
       {
           isFinishVirtual=false;
           gagnant="";
            return 100000000;
       }
       else if(gagnant==QString("PLAYER0"))
       {
           isFinishVirtual=false;
           gagnant="";
            return -100000000;
       }


   }

//Calcul le score pour le l'ia et l'adversaire, fais la soustraction des deux
if(coupHUMAIN->getOwner()==QString("PLAYER0") && coupIA->getOwner()==QString("IA0"))
{
int scoreHUMAIN=0;
int scoreIA=0;
scoreHUMAIN=score(coupHUMAIN);
scoreIA=score(coupIA);
return scoreIA-scoreHUMAIN;
}

}



bool Game::verificationCoup(Hex * hexdepart)
{



    int xVoisin1,xVoisin2,xVoisin3,xVoisin4,xVoisin5,xVoisin6,yVoisin1,yVoisin2,yVoisin3,yVoisin4,yVoisin5,yVoisin6=0; // ces 6 voisins
    QString position = hexdepart->toolTip(); // on recupere sa position
    QString proprietaire = hexdepart->getOwner(); // son proprietaire
    int  a = position.split(";")[0].toInt(); // converti en int car sa position est en Qstring
    int b = position.split(";")[1].toInt();

    HexVisit.clear(); // BESOIN DE DEUX LISTE A CAUSE DU REMOVE DE HEXVISIT
    HexVisitFourche.clear();


    HexVisit.append(hexdepart); // on ajoute au deux liste des visiter cet hexagon
    HexVisitFourche.append(hexdepart);

    // calcul de ses voisins :

    // voisin 1 :
    xVoisin1 = a;
    yVoisin1 = b+2;
    Hex * voisin1 = hexBoard->tableauhex[xVoisin1][yVoisin1];

    // voisin 2 :
    xVoisin2 = a;
    yVoisin2 = b-2;
    Hex * voisin2 = hexBoard->tableauhex[xVoisin2][yVoisin2];


    // voisin 3 :
    xVoisin3 = a+1;
    yVoisin3 = b+1;
    Hex * voisin3 = hexBoard->tableauhex[xVoisin3][yVoisin3];


    // voisin 4 :
    xVoisin4 = a+1;
    yVoisin4 = b-1;
    Hex * voisin4 = hexBoard->tableauhex[xVoisin4][yVoisin4];

    // voisin 5 :
    xVoisin5 = a-1;
    yVoisin5 = b-1;
    Hex * voisin5 = hexBoard->tableauhex[xVoisin5][yVoisin5];


    // voisin 6 :
    xVoisin6 = a-1;
    yVoisin6 = b+1;
    Hex * voisin6 = hexBoard->tableauhex[xVoisin6][yVoisin6];


// maintenant qu'on a les position de ses voisins on va voir lesquel son du même propriétaire

    if(aQuiAppartientCetHexV2(xVoisin1,yVoisin1)==proprietaire)
    {
        if (verificationCoupGagnant(a,b,xVoisin1,yVoisin1, a, b ,proprietaire, voisin1)) {return true;};
    }

    if(aQuiAppartientCetHexV2(xVoisin2,yVoisin2)==proprietaire)
    {
        if(verificationCoupGagnant(a,b,xVoisin2,yVoisin2, a, b ,proprietaire, voisin2)) {return true;} ;
    }

    if(aQuiAppartientCetHexV2(xVoisin3,yVoisin3)==proprietaire)
    {
        if(verificationCoupGagnant(a,b,xVoisin3,yVoisin3, a, b ,proprietaire, voisin3)) {return true;};
    }

    if(aQuiAppartientCetHexV2(xVoisin4,yVoisin4)==proprietaire)
    {
        if(verificationCoupGagnant(a,b,xVoisin4,yVoisin4, a, b ,proprietaire, voisin4)) {return true;};
    }

    if(aQuiAppartientCetHexV2(xVoisin5,yVoisin5)==proprietaire)
    {
        if(verificationCoupGagnant(a,b,xVoisin5,yVoisin5, a, b ,proprietaire, voisin5)){return true;};
    }

    if(aQuiAppartientCetHexV2(xVoisin6,yVoisin6)==proprietaire)
    {
        if(verificationCoupGagnant(a,b,xVoisin6,yVoisin6, a, b ,proprietaire, voisin6)){return true;};
    }



 }


bool Game::verificationCoupGagnant(int xbase, int ybase, int a, int b, int xprecedent, int yprecedent, QString proprietaire, Hex * hexcourant)
{
    int xVoisin1,xVoisin2,xVoisin3,xVoisin4,xVoisin5,xVoisin6,yVoisin1,yVoisin2,yVoisin3,yVoisin4,yVoisin5,yVoisin6=0;




    if (xbase==a && ybase==b) // verifie la boucle si on reviens sur le premier hexagon de depart
    {

        //VERIFIER BIEN BOUCLE
        if(verifBoucle(xbase,ybase))
        {

            qDebug() << "boucle prouver";
            gagnant=proprietaire;
            isFinish=true;
            return true;
        }
        else
         {

            return false;
        }

    }





    if (HexVisit.contains(hexcourant) || HexVisitFourche.contains(hexcourant)) // si l'hexagon est déjà la dans liste, faire return sinon boucle infini entre voisin
    {

       return false;
    }

    HexVisitFourche.append(hexcourant);
    HexVisit.append(hexcourant);



    if (verifPont())
    {
        qDebug() << "pont prouver";
        gagnant=proprietaire;
        isFinish=true;
        return true;
    }

    if (verifFourche())
    {
        qDebug() << "fourche prouver";
        gagnant=proprietaire;
        isFinish=true;
        return true;
    }

    // calcul de ses voisins :

    // voisin 1 :
    xVoisin1 = a;
    yVoisin1 = b+2;
    Hex * voisin1 = hexBoard->tableauhex[xVoisin1][yVoisin1];

    // voisin 2 :
    xVoisin2 = a;
    yVoisin2 = b-2;
    Hex * voisin2 = hexBoard->tableauhex[xVoisin2][yVoisin2];


    // voisin 3 :
    xVoisin3 = a+1;
    yVoisin3 = b+1;
    Hex * voisin3 = hexBoard->tableauhex[xVoisin3][yVoisin3];


    // voisin 4 :
    xVoisin4 = a+1;
    yVoisin4 = b-1;
    Hex * voisin4 = hexBoard->tableauhex[xVoisin4][yVoisin4];

    // voisin 5 :
    xVoisin5 = a-1;
    yVoisin5 = b-1;
    Hex * voisin5 = hexBoard->tableauhex[xVoisin5][yVoisin5];


    // voisin 6 :
    xVoisin6 = a-1;
    yVoisin6 = b+1;
    Hex * voisin6 = hexBoard->tableauhex[xVoisin6][yVoisin6];

// maintenant on rappele la fonction avec ces voisin du meme proprietaire
// jusqu'a peut etre revenir au point de depart , preuve de boucle

    if((aQuiAppartientCetHexV2(xVoisin1,yVoisin1)==proprietaire) && (xVoisin1 != xprecedent || yVoisin1 != yprecedent) && ( xVoisin1 >= 0 && yVoisin1 >= 0))
    {
        verificationCoupGagnant(xbase,ybase,xVoisin1,yVoisin1, a, b, proprietaire, voisin1);
    }

    if(aQuiAppartientCetHexV2(xVoisin2,yVoisin2)==proprietaire && (xVoisin2 != xprecedent || yVoisin2 != yprecedent)&& ( xVoisin2 >= 0 && yVoisin2 >= 0))
    {
        verificationCoupGagnant(xbase,ybase,xVoisin2,yVoisin2, a, b, proprietaire, voisin2);
    }

    if(aQuiAppartientCetHexV2(xVoisin3,yVoisin3)==proprietaire && (xVoisin3 != xprecedent || yVoisin3 != yprecedent)&& ( xVoisin3 >= 0 && yVoisin3 >= 0))
    {
        verificationCoupGagnant(xbase,ybase,xVoisin3,yVoisin3, a, b, proprietaire, voisin3);
    }

    if(aQuiAppartientCetHexV2(xVoisin4,yVoisin4)==proprietaire && (xVoisin4 != xprecedent || yVoisin4 != yprecedent)&& ( xVoisin4 >= 0 && yVoisin4 >= 0))
    {
        verificationCoupGagnant(xbase,ybase,xVoisin4,yVoisin4, a, b ,proprietaire, voisin4);
    }

    if(aQuiAppartientCetHexV2(xVoisin5,yVoisin5)==proprietaire && (xVoisin5 != xprecedent || yVoisin5 != yprecedent)&& ( xVoisin5 >= 0 && yVoisin5 >= 0))
    {
        verificationCoupGagnant(xbase,ybase,xVoisin5,yVoisin5, a, b ,proprietaire, voisin5);
    }

    if(aQuiAppartientCetHexV2(xVoisin6,yVoisin6)==proprietaire && (xVoisin6 != xprecedent || yVoisin6 != yprecedent)&& ( xVoisin6 >= 0 && yVoisin6 >= 0))
    {
        verificationCoupGagnant(xbase,ybase,xVoisin6,yVoisin6, a, b ,proprietaire, voisin6);
    }


  HexVisit.removeOne(hexcourant); // cet hex ne fera pas partie de la boucle

   return false;

}



bool Game::AppartientListeVisit(int a, int b) //
{
    for (size_t i = 0; i < getHexVisit().size() ; i++)
    { // fouille tout les hexagon visite
     if (!getHexVisit()[i])
         continue;

        if(getHexVisit()[i]->toolTip() == (QString::number(a) + ";" + QString::number(b))) // il a ete visite
        {
            return true;
         }

        }
    return false;
}

QString Game::aQuiAppartientCetHexV2(int a, int b)
{
    if (a<0 || b<0 || a>hexBoard->ligne-1 || b>hexBoard->colonne-1)
    {
        return QString("NOTONBOARD") ;
    }
    return hexBoard->tableauhex[a][b]->getOwner();
}



bool Game::verifBoucle(int a, int b)
{
    QString proprietaire = aQuiAppartientCetHexV2(a,b);
    int xVoisinGauche,yVoisinGauche,xVoisinDroit,yVoisinDroit,xVoisinHautGauche,yVoisinHautGauche,xVoisinHautDroit,yVoisinHautDroit,xVoisinBasGauche,yVoisinBasGauche,xVoisinBasDroit,yVoisinBasDroit=0;
    // pour les 6 cote de l'hexagon, il faut verifier que au moins un coter peut verifier la condition suivante:
    // il a voisin dont il nest pas proprietaire suivi peut etre d'autres encore puis retombe sur un hex de la boucle

    // voisin gauche :
    xVoisinGauche=a;
    yVoisinGauche=b-2;
    if (aQuiAppartientCetHexV2(xVoisinGauche,yVoisinGauche)!=proprietaire)
    {
        for (int i = yVoisinGauche; i > 0; i= i-2) // on va de gauche a gauche
        {
            if(AppartientListeVisit(xVoisinGauche,i)) // si on trouve qu'il appartient a la liste c'est bon
               {
               return true;
                }
        }
    }

    // voisin droit

    xVoisinDroit=a;
    yVoisinDroit=b+2;
    if (aQuiAppartientCetHexV2(xVoisinDroit,yVoisinDroit)!=proprietaire)
    {
        for (int i = yVoisinDroit; i <= hexBoard->colonne-1; i= i+2) // on va de droite en droite
        {
            if(AppartientListeVisit(xVoisinDroit,i)) // si on trouve qu'il appartient a la liste c'est bon
               {
                return true;
                }
        }
    }

    // voisin haut gauche

    xVoisinHautGauche=a-1;
    yVoisinHautGauche=b-1;
    if (aQuiAppartientCetHexV2(xVoisinHautGauche,yVoisinHautGauche)!=proprietaire)
    {
        for (int i = xVoisinHautGauche, y = yVoisinHautGauche ;   i >= 0  && y >= 0  ;    i--,y--) // toujours vers le coter haut gauche de l'hexagon
        {
            if(AppartientListeVisit(i,y)) // si on trouve qu'il appartient a la liste c'est bon
               {
                return true;
               }
        }
    }

    // voisin haut droit
    xVoisinHautDroit=a-1;
    yVoisinHautDroit=b+1;
    if (aQuiAppartientCetHexV2(xVoisinHautDroit,yVoisinHautDroit)!=proprietaire)
    {
        for (int i = xVoisinHautDroit, y = yVoisinHautDroit ;   i >= 0  && y <= hexBoard->colonne-1  ;    i--,y++) // toujours vers le coter haut droit de l'hexagon
        {
            if(AppartientListeVisit(i,y)) // si on trouve qu'il appartient a la liste c'est bon
               {
                return true;
               }
        }
    }

    // voisin bas gauche
    xVoisinBasGauche=a+1;
    yVoisinBasGauche=b-1;
    if (aQuiAppartientCetHexV2(xVoisinBasGauche,yVoisinBasGauche)!=proprietaire)
    {
        for (int i = xVoisinBasGauche, y = yVoisinBasGauche ;   i <= hexBoard->ligne-1  && y >= 0  ;    i++,y--) // toujours vers le coter bas gauche de l'hexagon
        {
            if(AppartientListeVisit(i,y)) // si on trouve qu'il appartient a la liste c'est bon
               {
                return true;
               }
        }
    }


    // voisin bas droit
    xVoisinBasDroit=a+1;
    yVoisinBasDroit=b+1;

    if (aQuiAppartientCetHexV2(xVoisinBasDroit,yVoisinBasDroit)!=proprietaire)
    {
        for (int i = xVoisinBasDroit, y = yVoisinBasDroit ;   i <= hexBoard->ligne-1  && y <= hexBoard->colonne-1  ;    i++,y++) // toujours vers le coter bas droit de l'hexagon
        {
            if(AppartientListeVisit(i,y)) // si on trouve qu'il appartient a la liste c'est bon
               {
                return true;
               }
        }
    }



return false; // on a pas la preuve d'une boucle


}


bool Game::verifPont()
{
    int nbpont=0; //nb pont = 2 verifie que le joueur a bien un pont
    for (size_t i = 0; i < getHexVisitFourche().size() ; i++)
    { // fouille tout les hexagon visite
     if (!getHexVisitFourche()[i])
         continue;

        if(getHexVisitFourche()[i]->getTypePos()==QString("COIN"))
        {
            nbpont++;
         }

    }

    if(nbpont>1)
    {
        return true;
    }
    else{
       return false;
    }

}


bool Game::verifFourche()
{
    int nbfourche=0;
    int nbcote[7]={0};

    for (size_t i = 0; i < getHexVisitFourche().size() ; i++)
    { // fouille tout les hexagon visite
     if (!getHexVisitFourche()[i])
         continue;

        if(getHexVisitFourche()[i]->getTypePos()==QString("BORD"))
        {
            nbcote[getHexVisitFourche()[i]->getNbBord()]=1;
         }

    }

    for (int i=0 ; i < 7 ; i++ )
    {
        nbfourche = nbfourche + nbcote[i]; // au final si le resultat est 3 c'est bien que la fourche touche 3 cotes differents
    }

    if (nbfourche>2)
    {
        return true;
    }
    else
    {
        return false;
    }

}
