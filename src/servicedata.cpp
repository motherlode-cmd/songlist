#include "servicedata.h"
#include "song.h"
#include <QFile>
#include <iostream>
#include <filesystem>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantMap>
#include <QPixmap>
#include <QDir>

QList <Song*> ServiceData::readFile() //в текущей директории создается файл, с котором будут храниться текстовые данные о песне
{
    QString val;
    QString filename =  ".//test.json";
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.isOpen()) {
        std::cout<< "Can't open file."<<std::endl;
        return;
     }
     val = file.readAll();
     file.close();
     return parseData(val);
}

void ServiceData::writeFile(QList <Song*> songs) // запись песен в файл
{
    QJsonArray array;
    for(auto tmp : songs)
    {
        QJsonObject item;
        item.insert("name", tmp->getName());
        item.insert("author", tmp->getAuvtor());
        item.insert("time", tmp->getTime());
        item.insert("status", tmp->getStatus());
        item.insert("image", tmp->getImgName());
        array.append(item);
    }
    QJsonDocument doc(array);
    QString filename = ".//test.json";
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QFile::Truncate);
    if (!file.isOpen()) {
        std::cout<< "Can't open file."<<std::endl;
    }
    file.write(doc.toJson());
    file.close();
}

void ServiceData::savePixmap(QPixmap image, Song * song) //сохранение картинки с выбранным названием в папку images
{

    QDir * dir = new QDir;
    bool exist = dir->exists("images");
    if (!exist)
    {
        std::cout<<("Cannot find the example directory")<<std::endl;
        bool ok = dir->mkdir("images");
    }//если еще нет папки, то мы ее создаем
    QFile file(dir->path() + "/images/" + song->getImgName());
    song->setImageName(dir->path() + "/images/" + song->getImgName()); //меняем название картинки на путь к файлу
    file.open(QIODevice::WriteOnly);
    image.save(&file, "PNG");

}

QPixmap ServiceData::drowPixmap(QString imageName)//достаем картинку по названию
{
    QPixmap pix;
    QFile file(imageName);
    file.open(QIODevice::ReadOnly);
    const QPixmap pixmap(imageName);
    return pixmap;
}

QStandardItem * ServiceData::standardItemPixmap(Song * current) //приводим к типу, который можно хранить в модели и возвращаем его
{
    QStandardItem *item = new QStandardItem();
    QPixmap pixmap = drowPixmap(current->getImgName());
    item->setData(pixmap, Qt::DecorationRole);
    return item;
}



QList <Song*> ServiceData::parseData(QString val) //получаем лист песен из файла
{
    QList <Song*> listItems;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonArray array = doc.array();
    for(auto v : array)
    {
        QJsonObject data = v.toObject();
        QString name = data["name"].toString();
        QString author = data["author"].toString();
        QString time = data["time"].toString();
        QString imgName = data["image"].toString();
        QString status = data["status"].toString();
        Song * tmpSong = new Song(name, author, time, imgName, status);
        listItems.append(tmpSong);
    }
    return listItems;
}


