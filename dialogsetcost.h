#ifndef DIALOGSETCOST_H
#define DIALOGSETCOST_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class DialogSetCost : public QDialog
{
    Q_OBJECT

public:
    DialogSetCost(int initCost,QWidget *parent = 0);

private:
    QSpinBox* spinBoxCost;
    QPushButton* btnConfirm;
    QLabel* lblCost;
signals:
    void sendCost(int);
private slots:
    void confirm();
};

#endif // DIALOGSETCOST_H
