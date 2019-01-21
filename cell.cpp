#include "cell.h"

Cell::Cell(Index pos, QWidget *parent = 0) : QPushButton(parent){
    position = pos;
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(btnRightClicked()));
    connect(this, SIGNAL(sendIndex(Index)), parent, SLOT(cellClicked(Index)));
    connect(this, SIGNAL(sendIndex4Cost(Index)), parent, SLOT(editCellCost(Index)));
    connect(this, SIGNAL(sendIndexWithCost(Index,int)), parent, SLOT(setCellCost(Index,int)));
}

void Cell::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton)
        emit rightClicked();
    else if(e->button() == Qt::LeftButton)
        emit clicked();
}

void Cell::btnRightClicked(){
    emit sendIndex4Cost(position);
}

void Cell::getCost(int cost){
    emit sendIndexWithCost(position, cost);
}

void Cell::btnClicked(){
    emit sendIndex(position);
}

void Cell::setAsBlank(){
    this->setStyleSheet("background-color: #dddddd");
    this->setIcon(QIcon());
}

void Cell::setAsObstacle(){
    this->setStyleSheet("background-color: gray");
    QIcon IconObstacle = QIcon(":/icon/icon/obstacle.png");
    this->setIcon(IconObstacle);
}

void Cell::setAsOrigin(){
    this->setStyleSheet("background-color: white");
    QIcon IconOrigin = QIcon(":/icon/icon/rabbit.png");
    this->setIcon(IconOrigin);
}

void Cell::setAsDestination(){
    this->setStyleSheet("background-color: white");
    QIcon IconDestination = QIcon(":/icon/icon/carrot.png");
    this->setIcon(IconDestination);
}

void Cell::setAsPath(){
    this->setStyleSheet("background-color: white");
    QIcon IconPath = QIcon(":/icon/icon/foot.png");
    this->setIcon(IconPath);
}

void Cell::setAsVisited(){
    this->setStyleSheet("background-color: #bbbbbb");
    this->setIcon(QIcon());
}

