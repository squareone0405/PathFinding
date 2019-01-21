#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1060, 720);
    this->setWindowTitle("PathFinding");
    this->setStyleSheet("QMainWindow{border-image: url(:/icon/icon/gray.jpg)}");
    initComponent();
}

void MainWindow::initComponent()
{
    btnEditMap = new QRadioButton(tr("设置障碍"), this);
    btnEditOrigin = new QRadioButton(tr("设置起点"), this);
    btnEditDestination = new QRadioButton(tr("设置终点"), this);
    btnGroupEdit = new QButtonGroup(this);
    btnGroupEdit->addButton(btnEditMap, editMap);
    btnGroupEdit->addButton(btnEditOrigin, editOrigin);
    btnGroupEdit->addButton(btnEditDestination, editDestination);
    btnEditMap->move(200, 10);
    btnEditOrigin->move(300, 10);
    btnEditDestination->move(400, 10);
    btnEditMap->setChecked(true);

    btnSaveMap = new QPushButton(tr("保存地图"), this);
    btnLoadMap = new QPushButton(tr("加载地图"), this);
    btnResetMap = new QPushButton(tr("重置地图"), this);
    btnSetSize = new QPushButton(tr("设置尺寸"), this);
    btnShowCost = new QPushButton(tr("显示路径代价"), this);

    QGridLayout* mapLayout = new QGridLayout();
    mapLayout->addWidget(btnSaveMap, 0, 0);
    mapLayout->addWidget(btnLoadMap, 0, 1);
    mapLayout->addWidget(btnResetMap, 0, 2);
    mapLayout->addWidget(btnSetSize, 1, 0);
    mapLayout->addWidget(btnShowCost, 1, 1);
    groupBoxMap = new QGroupBox(tr("地图"), this);
    groupBoxMap->setGeometry(700, 150, 350, 120);
    groupBoxMap->setLayout(mapLayout);

    comboSearchOptions = new QComboBox(this);
    QStringList strSearchMethod = {QString(tr("宽度优先搜索")), QString(tr("深度优先搜索")),
                                   QString(tr("双向搜索")), QString(tr("迭代加深搜索")),
                                   QString(tr("贪婪搜索")), QString(tr("一致代价搜索")),
                                   QString(tr("A*搜索")), QString(tr("动态加权A*搜索"))};
    comboSearchOptions->addItems(strSearchMethod);
    comboHuristic = new QComboBox(this);
    QStringList strHuristic = {QString(tr("曼哈顿距离")), QString(tr("对角距离")),
                               QString(tr("欧氏距离"))};
    comboHuristic->addItems(strHuristic);
    comboExpandMethod = new QComboBox(this);
    QStringList strExpand = {QString(tr("4方向扩展")), QString(tr("8方向扩展"))};
    comboExpandMethod->addItems(strExpand);
    btnFindPath = new QPushButton(tr("开始寻径"), this);
    btnFindPath->setFixedWidth(80);
    QGridLayout* pathLayout = new QGridLayout();
    pathLayout->addWidget(btnFindPath, 0, 0);
    pathLayout->addWidget(comboSearchOptions, 0, 1);
    pathLayout->addWidget(comboHuristic, 1, 0);
    pathLayout->addWidget(comboExpandMethod, 1, 1);
    groupBoxSearch = new QGroupBox(tr("寻径"), this);
    groupBoxSearch->setGeometry(700, 290, 280, 120);
    groupBoxSearch->setLayout(pathLayout);

    lblCost = new QLabel(tr("路径代价：00"), this);
    lblTime = new QLabel(tr("计算时间：00ms"), this);
    QHBoxLayout* resultLayout = new QHBoxLayout();
    resultLayout->addWidget(lblCost);
    resultLayout->addWidget(lblTime);
    groupBoxResult = new QGroupBox(tr("结果"), this);
    groupBoxResult->setGeometry(700, 430, 300, 80);
    groupBoxResult->setLayout(resultLayout);

    areaCells = new QScrollArea(this);
    areaCells->setGeometry(10, 40, 670, 670);

    connect(btnGroupEdit, SIGNAL(buttonClicked(int)), this, SLOT(btnGroupEditClicked(int)));
    connect(btnSaveMap, SIGNAL(clicked()), this, SLOT(saveMapAsCSV()));
    connect(btnLoadMap, SIGNAL(clicked()), this, SLOT(loadMapFromCSV()));
    connect(btnShowCost, SIGNAL(clicked()), this, SLOT(showCellCost()));
    connect(btnResetMap, SIGNAL(clicked()), this, SLOT(clearMap()));
    connect(btnSetSize, SIGNAL(clicked()), this, SLOT(showSizeDialog()));
    connect(btnFindPath, SIGNAL(clicked()), this, SLOT(findPath()));

    setMapSize(std::make_pair<int, int>(20, 20));
    editStatus = editMap;
    isCellHiden = true;
}

void MainWindow::saveMapAsCSV(){
    std::string path = QFileDialog::getSaveFileName(this, "", "../map/", "*.csv").toStdString();
    if(path == "")
        return;
    std::ofstream output(path , std::ios::out);
    for(size_t i = 0; i < map.size(); ++i){
        for(size_t j = 0; j < map[i].size(); ++j){
            output<<map[i][j]<<",";
        }
        output<<std::endl;
    }
    output.close();
}

void MainWindow::loadMapFromCSV(){
    std::string path = QFileDialog::getOpenFileName(this, "", "../map/", "*.csv").toStdString();
    if(path == "")
        return;
    Map newMap = std::vector<std::vector<int>>();
    newMap.clear();
    std::ifstream input(path, std::ios::in);
    std::string lineStr;
    while(getline(input, lineStr)){
        std::stringstream ss(lineStr);
        std::string cellStr;
        std::vector<int> rowArray;
        while(getline(ss, cellStr, ',')){
            int cellValue;
            try{
                cellValue = std::stoi(cellStr, nullptr, 10);
                if(cellValue < 0){
                    QMessageBox::warning(this, "WARNING", tr("地图数据需为正整数"), QMessageBox::Yes);
                    return;
                }
            }
            catch(std::exception){
                QMessageBox::warning(this, "WARNING", tr("地图文件格式有误"), QMessageBox::Yes);
                return;
            }
            rowArray.push_back(cellValue);
        }
        newMap.push_back(rowArray);
    }
    if(newMap.size() == 0){
        QMessageBox::warning(this, "WARNING", tr("地图为空"), QMessageBox::Yes);
        return;
    }
    if(newMap.size() > 99){
        QMessageBox::warning(this, "WARNING", tr("地图过大"), QMessageBox::Yes);
        return;
    }
    int rowSize = newMap[0].size();
    for(auto iter = newMap.begin(); iter != newMap.end(); ++iter){
        if(iter->size() > 99){
            QMessageBox::warning(this, "WARNING", tr("地图过大"), QMessageBox::Yes);
            return;
        }
        if(iter->size() != rowSize){
            QMessageBox::warning(this, "WARNING", tr("地图各行尺寸不一致"), QMessageBox::Yes);
            return;
        } 
    }
    map = newMap;
    resetCellsWithMap();
    origin = std::make_pair<int, int>(-1, -1);
    destination = std::make_pair<int, int>(-1, -1);
}

void MainWindow::btnGroupEditClicked(int status){
    if(editStatus == notEditing)
        clearPath();
    editStatus = (EditStatus)status;
}

void MainWindow::cellClicked(Index pos){
    if(editStatus != notEditing){
        if(pos == origin){
            origin = std::make_pair<int, int>(-1, -1);
        }
        if(pos == destination){
            destination = std::make_pair<int, int>(-1, -1);
        }
    }
    switch (editStatus) {
    case editMap:
        if(map[pos.first][pos.second] == 1){
            map[pos.first][pos.second] = 0;
            cells[pos.first][pos.second]->setAsObstacle();
        }
        else if(map[pos.first][pos.second] == 0){
            map[pos.first][pos.second] = 1;
            cells[pos.first][pos.second]->setAsBlank();
        }
        break;
    case editOrigin:
        map[pos.first][pos.second] = 1;
        if(origin.first != -1){
            map[origin.first][origin.second] = 1;
            cells[origin.first][origin.second]->setAsBlank();
        }
        cells[pos.first][pos.second]->setAsOrigin();
        origin = pos;
        break;
    case editDestination:
        map[pos.first][pos.second] = 1;
        cells[pos.first][pos.second]->setAsBlank();
        if(destination.first != -1){
            map[destination.first][destination.second] = 1;
            cells[destination.first][destination.second]->setAsBlank();
        }
        cells[pos.first][pos.second]->setAsDestination();
        destination = pos;
        break;
    case notEditing:
        break;
    default:
        break;
    }
}

void MainWindow::findPath(){
    if(origin.first == -1 || destination.first == -1){
        QMessageBox::warning(this, "WARNING", tr("请先设置起点与终点"), QMessageBox::Yes);
        return;
    }
    clearPath();
    EditStatus temp = editStatus;
    editStatus = notEditing;
    SearchProblem* p;

    switch (comboSearchOptions->currentIndex()) {
    case 0:
        p = new BreadthFirstSearch(map, origin, destination);
        break;
    case 1:
        p = new DepthFirstSearch(map, origin, destination);
        break;
    case 2:
        p = new BidirectionalSearch(map, origin, destination);
        break;
    case 3:
        p = new IterativeDeepenSearch(map, origin, destination);
        break;
    case 4:
        p = new GreedyBestFirstSearch(map, origin, destination);
        break;
    case 5:
        p = new UniformCostSearch(map, origin, destination);
        break;
    case 6:
        p = new AStarSearch(map, origin, destination);
        break;
    case 7:
        p = new DWAStarSearch(map, origin, destination);
        break;
    default:
        break;
    }
    switch (comboExpandMethod->currentIndex()) {
    case 0:
        p->setExpandNum(4);
        break;
    case 1:
        p->setExpandNum(8);
        break;
    default:
        break;
    }
    switch (comboHuristic->currentIndex()) {
    case 0:
        p->setHuristic(Manhatten);
        break;
    case 1:
        p->setHuristic(Diagonal);
        break;
    case 2:
        p->setHuristic(Euclidean);
        break;
    default:
        break;
    }
    QElapsedTimer timer;
    timer.start();
    if(p->findPath()){
        lblTime->setText(QString(tr("计算时间：") +
                                 QString::number(timer.nsecsElapsed()/1000000.0, 'g', 4) + "ms"));
        std::vector<std::vector<bool>> visited = p->getVisited();
        timer.restart();
        for(size_t i = 0; i < visited.size(); ++i){
            for(size_t j = 0; j < visited[i].size(); ++j){
                if(visited[i][j] == true)
                    cells[i][j]->setAsVisited();
            }
        }
        qDebug()<<(QString::number(timer.nsecsElapsed()/1000000.0, 'g', 4) + "ms");
        std::vector<Index> path = p->getPath();
        int cost = 0;
        for(auto iter = path.begin(); iter != path.end(); ++iter){
            cells[iter->first][iter->second]->setAsPath();
            cost += map[iter->first][iter->second];
        }
        cells[origin.first][origin.second]->setAsOrigin();
        cells[destination.first][destination.second]->setAsDestination();
        lblCost->setText(QString(tr("路径代价：") + QString::number(cost)));
    }
    else{
        lblCost->setText(QString(tr("路径代价：00")));
        lblTime->setText(QString(tr("计算时间：") +
                                 QString::number(timer.nsecsElapsed()/1000000.0, 'g', 3) + "ms"));
        QMessageBox::information(this, "INFO", tr("未找到路径"), QMessageBox::Yes);
    }
    editStatus = temp;
    delete p;
}

void MainWindow::clearPath(){
    for(int i = 0; i < map.size(); ++i){
        for(int j = 0; j < map[i].size(); ++j){
            if(map[i][j] != 0
                    && (origin.first!=i||origin.second != j)
                    && (destination.first!=i||destination.second != j))
                cells[i][j]->setAsBlank();
        }
    }
}

void MainWindow::clearMap(){
    for(auto i = cells.begin(); i != cells.end(); ++i)
        for(auto j = i->begin(); j != i->end(); ++j)
            (*j)->setAsBlank();
    for(auto i = map.begin(); i != map.end(); ++i)
        for(auto j = i->begin(); j != i->end(); ++j)
            *j = 1;
    origin = std::make_pair<int, int>(-1, -1);
    destination = std::make_pair<int, int>(-1, -1);
}

void MainWindow::showSizeDialog(){
    if(editStatus == notEditing)
        return;
    DialogSetMapSize* dlg = new DialogSetMapSize(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}

void MainWindow::setMapSize(std::pair<int, int> size){
    map.clear();
    map.resize(size.first);
    for(int i = 0; i < size.first; ++i){
        map[i].clear();
        map[i] = std::vector<int>(size.second, 1);
    }
    origin = std::make_pair<int, int>(-1, -1);
    destination = std::make_pair<int, int>(-1, -1);
    resetCellsWithMap();
}

void MainWindow::resetCellsWithMap(){
    for(auto i = cells.begin(); i != cells.end(); ++i)
        for(auto j = i->begin(); j != i->end(); ++j)
            if((*j) != nullptr)
                delete (*j);
    int h = map.size();
    int w = map[0].size();

    QWidget* widget = areaCells->widget();
    if (widget){
        delete widget;
    }
    widget = new QWidget(areaCells);
    QSize widgetSize = QSize((cellSize + 3) * w, (cellSize + 3) * h);
    widget->setMinimumSize(widgetSize);
    widget->setMaximumSize(widgetSize);
    widget->resize(widgetSize);
    widget->move(200, 200);

    QGridLayout *gridLayout = new QGridLayout(widget);

    cells.resize(h);
    std::pair<int, int> pair;
    for(int i = 0; i < h; ++i){
        cells[i].resize(h);
        for(int j = 0; j < w; ++j){
            pair.first = i;
            pair.second = j;
            cells[i][j] = new Cell(pair, this);
            cells[i][j]->setFixedSize(cellSize, cellSize);
            gridLayout->addWidget(cells[i][j], i, j, Qt::AlignCenter | Qt::AlignCenter);
            if(map[i][j] == 1)
                cells[i][j]->setAsBlank();
            else
                cells[i][j]->setAsObstacle();
            cells[i][j]->show();
        }
    }

    widget->setLayout(gridLayout);
    areaCells->setWidget(widget);
    areaCells->setWidgetResizable(true);
}

void MainWindow::editCellCost(Index pos){
    DialogSetCost* dlg = new DialogSetCost(map[pos.first][pos.second], cells[pos.first][pos.second]);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->exec();
}

void MainWindow::setCellCost(Index pos, int cost){
    map[pos.first][pos.second] = cost;
}

void MainWindow::showCellCost(){
    if(isCellHiden == false){
        hideCellCost();
        return;
    }
    for(int i = 0; i < map.size(); ++i){
        for(int j = 0; j < map[i].size(); ++j){
            if(map[i][j] != 0)
                cells[i][j]->setText(QString::number(map[i][j]));
        }
    }
    btnShowCost->setText("隐藏路径代价");
    isCellHiden = false;
}

void MainWindow::hideCellCost(){
    for(auto i = cells.begin(); i != cells.end(); ++i){
        for(auto j = i->begin(); j != i->end(); ++j){
            (*j)->setText("");
        }
    }
    btnShowCost->setText("显示路径代价");
    isCellHiden = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}
