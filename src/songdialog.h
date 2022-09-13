#pragma once
#include "qabstractbutton.h"
#include <QDialog>
#include <QStandardItemModel>
namespace Ui
{
class SongDialog;
}

class SongDialog : public QDialog
{
    Q_OBJECT
private:
    void choosePreview();
    QString copiedPreview(const QString& filePath) const;
    void showPreview(const QString& relativePath) const;
    QString fullImagePath(const QString& relativePath) const;

    Ui::SongDialog* m_ui = nullptr;
    const QString m_imageDir = "../../images";
    QStandardItemModel * model;
    int * num = nullptr;//номер текущей строки, если была вызвана кнопка создания, то в последующем она увеличится
    bool check = false;//переменная для контроля рисования текущей картинки
    int isName = 0; //переменные для хранения информации о песнях, чтобы пользователь не мог ввести пустую строку
    int isAuvtor = 0;
    int isTime = 0;
    int isPixmap = 0;
    bool cancelButtonClicked = false;
    bool isSongCreated = true;
    QString strTool = "ВВедите недостающие данные";
public:
    void setToolStr(const QString strTool_);

    void setCreatedParam(bool setting)
    {
        isSongCreated = setting;
    }

    bool isChanged()
    {
        return !cancelButtonClicked;
    }
    void setNum(int * num_)
    {
        num = num_;
    }
    void change_model(QStandardItemModel * model_)
    {
        model = model_;
    }

    void preview_draw(int numb);
    void write_albom_info(int numb);
    void set_info(int numb);
    void unblock_ok();
    SongDialog(QWidget* parent = nullptr);
    ~SongDialog();
signals:
    void signalAll();

private slots:
    void statusSetValue(int value)
    {
        emit signalAll();
    }
    void statusGetValue()
    {
        emit signalAll();
    }
    void on_buttonBox_OK_clicked(QAbstractButton *button);
    void unlock_buttomBoxOK();

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_lineEdit_auvtor_textChanged(const QString &arg1);

    void on_lineEdit_time_textChanged(const QString &arg1);

};

