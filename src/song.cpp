#include "song.h"

Song::Song(QString name, QString auvtor, QString time, QString imgName, QString status)
{
    this->name = name;
    this->auvtor = auvtor;
    this->time = time;
    this->imgName = imgName;
    this->status = status;
}

const QString &Song::getName() const
{
    return name;
}

const QString &Song::getAuvtor() const
{
    return auvtor;
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
