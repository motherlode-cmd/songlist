#include "songlistdialog.h"
#include "songdialog.h"
#include "servicedata.h"
#include "song.h"
#include "ui_songlistdialog.h"
#include <QString>
#include <QSortFilterProxyModel>
#include <QList>
#include <QDir>
#include <QModelIndex>
SongListDialog::SongListDialog(QWidget *parent): QDialog(parent)
{
    m_ui = new Ui::SongListDialog();
    m_ui->setupUi(this);
    model = new QStandardItemModel();
    QStringList titles = {"preview","name","author","time","stat"};
    model->setHorizontalHeaderLabels(titles);
    m_ui->tableView->setModel(model);
    fillTable(); // Заполненение таблицы данными
    connect(m_ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(redOrDeleteSong(const QModelIndex &)));//При нажатии на строку таблицы, появляется возмжность редактировать ее
    m_ui->pushButton_save->setEnabled(false);//Запрет на повторное сохранение неизменённых данных
    m_ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//Запрет на редактирование таблицы пользователем без использования кнопок
    m_ui->tableView->hideColumn(4); // Скрытие столбца с оценками
}

SongListDialog::~SongListDialog()
{
    delete m_ui;
}

void SongListDialog::fillRow(Song *current, int &currentRowNumber) //функция заполнени строки таблицы данными из файла
{
    model->setItem(currentRowNumber, 0, ServiceData().standardItemPixmap(current));
    model->setItem(currentRowNumber, 1,  new QStandardItem(current->getName()));
    model->setItem(currentRowNumber, 2, new QStandardItem(current->getAuthor()));
    model->setItem(currentRowNumber, 3,  new QStandardItem(current->getTime()));
    model->setItem(currentRowNumber, 4, new QStandardItem(current->getStatus()));
}

void SongListDialog::fillTable()//считывание файла и заполнение построчечно таблицы данными
{
    ServiceData sd;
    auto data = sd.readFile(); //получаем список песен из файла QList <Song*>
    int rowCount = 0;
    for(auto& current : data)
    {
        fillRow(current, rowCount);
        rowCount++;
    }
    num = rowCount;
    setTableTools();//присваиваем подсказки каждой ячейке
}

void SongListDialog::setTableTools()//выбор подсказок с оценками каждой песни
{
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            QStandardItem * changedItem = model->item(i,j);
            changedItem->setToolTip("Оценка: " + model->item(i, 4)->text());
        }
    }
}
void SongListDialog::on_btnCreate_clicked() //нажата кнопка создать
{
    SongDialog dlg;
    dlg.change_model(model);
    dlg.setNum(&num);
    dlg.setCreatedParam(true);
    dlg.setToolStr("Введите недостающие данные"); //выбор подскази пользователю, если у того будет заблокирована кнопка ОК для нажания
    dlg.exec();
    if(dlg.isChanged()) { //true если данные внесены в таблицу, false - в противном случае
        m_ui->pushButton_save->setEnabled(true);
        m_ui->pushButton_sort->setEnabled(true);
        setRowTools(num - 1);//после изменений необходимо проверить состояние таблицы
    }
}

void SongListDialog::on_pushButton_sort_clicked()//кнопка сортировки таблицы
{
    (m_ui->tableView)->sortByColumn(4, Qt::DescendingOrder);
     m_ui->pushButton_save->setEnabled(true);//появились изменения, можно сохранять
     m_ui->pushButton_sort->setEnabled(false);//запрет на бессмысленную сортировку 2 раза подряд
}


void SongListDialog::redOrDeleteSong(const QModelIndex &index)//сигнал для редактирования таблицы
{
    if(!m_ui->pushButton_red->isEnabled()){//если выбрана песня, но кнопка редактирования недоступна, то нужно сделать ее доступной
        rowForRedOrDelete = index.row();//запоминаем номер выбранной строки
        m_ui->pushButton_red->setEnabled(true);
        m_ui->pushButton_delete->setEnabled(true);
        disableButtons(false);
    } else {//если два раза выбрать строку, то это будет трактоваться как отмена изменений
        m_ui->pushButton_red->setEnabled(false);
        m_ui->pushButton_delete->setEnabled(false);
        disableButtons(true);//даем доступ к нажатию остальнрых кнопок
    }
}

void SongListDialog::on_pushButton_delete_clicked()
{
    num--;
    model->removeRows(rowForRedOrDelete,1);//удаляем строку
    disableButtons(true);
    m_ui->btnCreate->setEnabled(true);//запрещаем повторно удалять, редактировать и сортировать, разрешено лишь сохранение и добавление
    m_ui->pushButton_delete->setEnabled(false);
    m_ui->pushButton_red->setEnabled(false);
    m_ui->pushButton_sort->setEnabled(false);
}
void SongListDialog::on_pushButton_red_clicked()
{
    disableButtons(false);
    SongDialog dlg;
    dlg.change_model(model);
    dlg.setCreatedParam(false);//сообщаем, что в данном окне будет создаваться новая запись, а не редактирование старой
    int number = rowForRedOrDelete; // доп переменная, чтобы не портить значение полей
    dlg.setNum(&number);//передаем номер обрабатываемой песни
    dlg.set_info(number);//заполяем данными из строки диалоговое окно
    dlg.setToolStr("Внесите изменения, либо отмените действие");
    dlg.exec();
    if(dlg.isChanged()) {
        setRowTools(rowForRedOrDelete);//после редактирования обновляем информацию о песне
        m_ui->pushButton_save->setEnabled(true);
    }
    m_ui->pushButton_sort->setEnabled(true && !m_ui->pushButton_sort->isEnabled());
    m_ui->btnCreate->setEnabled(true);
    m_ui->pushButton_delete->setEnabled(false);
    m_ui->pushButton_red->setEnabled(false);
}

void SongListDialog::setRowTools(int row)
{
    for(int i = 0; i < 4; i++) {
        QStandardItem * currentUtem = model->item(row, i);
        currentUtem->setToolTip("Оценка: " + model->item(row, 4)->text());
    }
}


void SongListDialog::on_pushButton_save_clicked()//сохранение данных в файл, вместо картинок в QList будут храниться пути к файлам, а сами картинки будут сохранены отдельно
{
    QList <Song*> songs;
    for(int i = 0; i < num; i++)
    {
        QString imageName = QString::number(i).append(".png");
        Song * tmpSong = new Song((model->item(i, 1))->text(), (model->item(i, 2))->text(), (model->item(i, 3))->text(), imageName, (model->item(i, 4))->text());
        ServiceData().savePixmap(model->item(i,0)->data(Qt::DecorationRole).value<QPixmap>(), tmpSong); //сохраняем картинку
        songs.append(tmpSong);
    }
    ServiceData().writeFile(songs);//создаем файл с остальными данными
    m_ui->pushButton_save->setEnabled(false);//запрет на повторное сохранение
}


void SongListDialog::disableButtons(bool state)
{
    m_ui->btnCreate->setEnabled(state);
    m_ui->pushButton_sort->setEnabled(state);
    m_ui->pushButton_save->setEnabled(state);
}



