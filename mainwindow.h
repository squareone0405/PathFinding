#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QIcon>
#include <QMessageBox>
#include <QComboBox>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLayout>
#include <QFileDialog>
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
#include <QElapsedTimer>
#include <fstream>
#include <sstream>
#include "cell.h"
#include "breadthfirstsearch.h"
#include "depthfirstsearch.h"
#include "bidirectionalsearch.h"
#include "iterativedeepensearch.h"
#include "greedybestfirstsearch.h"
#include "uniformcostsearch.h"
#include "astarsearch.h"
#include "dwastarsearch.h"
#include "searchproblem.h"
#include "config.h"
#include "dialogsetmapsize.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initComponent();
    void clearPath();
    void resetCellsWithMap();

private:
    Ui::MainWindow *ui;
    QRadioButton* btnEditMap;
    QRadioButton* btnEditOrigin;
    QRadioButton* btnEditDestination;
    QButtonGroup* btnGroupEdit;
    QPushButton* btnSaveMap;
    QPushButton* btnLoadMap;
    QPushButton* btnResetMap;
    QPushButton* btnSetSize;
    QPushButton* btnShowCost;
    QGroupBox* groupBoxMap;
    QPushButton* btnFindPath;
    QLabel* lblCost;
    QLabel* lblTime;
    QGroupBox* groupBoxResult;
    QComboBox* comboSearchOptions;
    QComboBox* comboHuristic;
    QComboBox* comboExpandMethod;
    QGroupBox* groupBoxSearch;
    QScrollArea* areaCells;

    std::vector<std::vector<Cell*>> cells;
    Map map;
    Index origin;
    Index destination;
    EditStatus editStatus;

    const int cellSize = 30;
    bool isCellHiden;

private slots:
    void btnGroupEditClicked(int status);
    void saveMapAsCSV();
    void loadMapFromCSV();
    void cellClicked(Index pos);
    void findPath();
    void clearMap();
    void showSizeDialog();
    void setMapSize(std::pair<int, int> size);
    void editCellCost(Index pos);
    void setCellCost(Index pos, int cost);
    void showCellCost();
    void hideCellCost();
};

#endif // MAINWINDOW_H
