#pragma once
#include <QTime>
#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>
#include "song.h"
class ServiceData
{
public:
    ServiceData();

    QList <Song*> readFile();
    void writeFile(QList <Song*> song);
    void savePixmap(QPixmap image, Song * song);
    QStandardItem * standardItemPixmap(Song * current);

private:
    QPixmap drowPixmap(QString imageName);
    QList <Song*> parseData(QString val);
};

