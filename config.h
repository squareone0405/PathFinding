#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <utility>
#include <QDebug>
#include <QPixmap>

typedef std::pair<int, int> Index;
typedef std::vector<std::vector<int>> Map;

enum EditStatus{
    editMap, editOrigin, editDestination, notEditing
};

enum HuristicFunction{
    Manhatten, Diagonal, Euclidean
};

#endif // CONFIG_H
