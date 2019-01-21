#include "dialogsetcost.h"

DialogSetCost::DialogSetCost(int initCost, QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(300, 200);
    lblCost = new QLabel(tr("代价："), this);
    lblCost->setGeometry(60, 50, 50, 30);
    spinBoxCost = new QSpinBox(this);
    spinBoxCost->setGeometry(120, 50, 100, 30);
    spinBoxCost->setMinimum(1);
    spinBoxCost->setMaximum(9);
    spinBoxCost->setValue(initCost);
    btnConfirm = new QPushButton(tr("确认"), this);
    btnConfirm->move(100, 150);
    connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
    connect(this, SIGNAL(sendCost(int)), parent, SLOT(getCost(int)));
}

void DialogSetCost::confirm(){
    emit sendCost(spinBoxCost->value());
    this->close();
}
