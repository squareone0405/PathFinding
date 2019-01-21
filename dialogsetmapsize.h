#ifndef DIALOGSETMAPSIZE_H
#define DIALOGSETMAPSIZE_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class DialogSetMapSize : public QDialog
{
    Q_OBJECT

public:
    DialogSetMapSize(QWidget *parent = 0);

private:
    QSpinBox* spinBoxRow;
    QSpinBox* spinBoxColumn;
    QPushButton* btnConfirm;
    QLabel* lblRow;
    QLabel* lblColumn;
signals:
    void sendSize(std::pair<int, int>);
private slots:
    void confirm();
};

#endif // DIALOGSETMAPSIZE_H
