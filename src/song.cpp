#include "song.h"

Song::Song(const QString &name,const QString &author,const QString &time,const QString &imgName,const QString &status)
{
    this->name = name;
    this->author = author;
    this->time = time;
    this->imgName = imgName;
    this->status = status;
}

QString &Song::getName()
{
    return name;
}

QString &Song::getAuthor()
{
    return author;
}

void Song::setImageName(QString &name)
{
    this->imgName = name;
}

QString &Song::getTime()
{
    return time;
}

QString &Song::getStatus()
{
    return status;
}

QString &Song::getImgName()
{
    return imgName;
}
