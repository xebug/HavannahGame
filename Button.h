#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    //*******CONSTRUCTEUR********//
    Button(QString name, QGraphicsItem* parent=NULL);
    //****************************//

    //*******GESTION DE LA SOURIS********//
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // fonction appélé quand on click sur le bouton
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event); // quand on passe la souris dessus
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event); // quand la souris ne passe plus dessus le bouton
    //****************************//

signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
