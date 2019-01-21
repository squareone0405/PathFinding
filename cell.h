#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include <QMouseEvent>
#include <QIcon>
#include "config.h"
#include "dialogsetcost.h"

class Cell: public QPushButton
{
    Q_OBJECT
public:
    Cell(Index pos, QWidget *parent);
    void setAsBlank();
    void setAsObstacle();
    void setAsOrigin();
    void setAsDestination();
    void setAsPath();
    void setAsVisited();

private:
    Index position;

signals:
    void sendIndex(Index pos);
    void sendIndex4Cost(Index pos);
    void sendIndexWithCost(Index pos, int cost);
    void rightClicked();

private slots:
    void getCost(int cost);
    void btnClicked();
    void btnRightClicked();
    void mousePressEvent(QMouseEvent *e);
};

#endif // CELL_H
