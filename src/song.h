#ifndef SONG_H
#define SONG_H
#include <QString>

class Song //класс для хранения информации о песни, используемый исключительно для работы с хранением информации
{
public:
    explicit Song(const QString &name, const QString &author, const QString &time, const QString &imgName, const QString &status);
    QString &getName() ;
    QString &getAuthor() ;
    void setImageName(QString &name);
    QString &getTime() ;

    QString &getStatus() ;

    QString &getImgName();

private:
    QString name; //значения соответствующих ячеек таблицы
    QString author;
    QString time;
    QString imgName;//путь к файлу с картинкой
    QString status;//значение слайдера
};

#endif // SONG_H
