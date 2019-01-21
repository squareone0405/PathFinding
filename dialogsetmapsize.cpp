#include "dialogsetmapsize.h"

DialogSetMapSize::DialogSetMapSize(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(300, 250);
    lblRow = new QLabel(tr("行数："), this);
    lblRow->setGeometry(60, 50, 50, 30);
    spinBoxRow = new QSpinBox(this);
    spinBoxRow->setGeometry(120, 50, 100, 30);
    spinBoxRow->setMinimum(3);
    spinBoxRow->setValue(20);
    lblColumn = new QLabel(tr("列数："), this);
    lblColumn->setGeometry(60, 120, 50, 30);
    spinBoxColumn = new QSpinBox(this);
    spinBoxColumn->setGeometry(120, 120, 100, 30);
    spinBoxColumn->setMinimum(3);
    spinBoxColumn->setValue(20);
    btnConfirm = new QPushButton(tr("确认"), this);
    btnConfirm->move(100, 200);
    connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
    connect(this, SIGNAL(sendSize(std::pair<int,int>)), parent, SLOT(setMapSize(std::pair<int,int>)));
}

void DialogSetMapSize::confirm(){
    if(spinBoxRow->value() == 0 || spinBoxColumn->value() == 0){
        QMessageBox::warning(this, "WARNING", tr("地图尺寸不可为0"), QMessageBox::Yes);
        return;
    }
    emit sendSize(std::make_pair<int, int>(spinBoxRow->value(), spinBoxColumn->value()));
    this->close();
}
