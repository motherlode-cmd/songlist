#ifndef SONG_H
#define SONG_H
#include <QString>

class Song //класс для хранения информации о песни, используемый исключительно для работы с хранением информации
{
public:
    Song(QString name, QString auvtor, QString time, QString imgName, QString status);
    const QString &getName() const;
    const QString &getAuvtor() const;
    void setImageName(QString name);
    const QString &getTime() const;

    const QString &getStatus() const;

    const QString &getImgName() const;

private:
    QString name; //значения соответствующих ячеек таблицы
    QString auvtor;
    QString time;
    QString imgName;//путь к файлу с картинкой
    QString status;//значение слайдера
};

#endif // SONG_H
