#include "song.h"

Song::Song(QString name, QString author, QString time, QString imgName, QString status)
{
    this->name = name;
    this->author = author;
    this->time = time;
    this->imgName = imgName;
    this->status = status;
}

const QString &Song::getName() const
{
    return name;
}

const QString &Song::getAuthor() const
{
    return author;
}

void Song::setImageName(QString name)
{
    this->imgName = name;
}

const QString &Song::getTime() const
{
    return time;
}

const QString &Song::getStatus() const
{
    return status;
}

const QString &Song::getImgName() const
{
    return imgName;
}
