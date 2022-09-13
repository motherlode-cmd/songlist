#pragma once
#include <QDialog>
#include <QStandardItemModel>
#include <QObject>
#include <QAbstractItemView>
#include <QModelIndex>
#include "song.h"
namespace Ui
{
class SongListDialog;
}


class SongListDialog : public QDialog
{
Q_OBJECT

public:
    SongListDialog(QWidget *parent = nullptr);
    ~SongListDialog();

public slots:

private slots:
    void on_btnCreate_clicked();
    void on_pushButton_sort_clicked();
    void redOrDeleteSong(const QModelIndex &index);
    void on_pushButton_save_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_red_clicked();

signals:
    void clicked(int row);

private:
    void setRowTools(int row);
    void setTableTools();
    void disableButtons(bool state);
    void fillRow(Song * current, int& currentRowNumber);
    void fillTable();
    Ui::SongListDialog* m_ui = nullptr;
    QStandardItemModel* model = nullptr;
    int num = 0;
    bool isSorting = false;
    int rowForRedOrDelete = 0;
};
