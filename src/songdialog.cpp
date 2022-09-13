#include "songdialog.h"
#include "ui_songdialog.h"
//#include "servicedata.h"
#include <QFileDialog>
#include <QList>
#include <QStandardItemModel>
#include <iostream>
#include <QLabel>
#include <QLineEdit>

SongDialog::SongDialog(QWidget* parent): QDialog(parent), m_ui(new Ui::SongDialog())
{
    m_ui->setupUi(this);
    connect(m_ui->btnCreate, &QPushButton::clicked, this, &SongDialog::choosePreview);
    connect(this, SIGNAL(signalAll()), this, SLOT(unlock_buttomBoxOK())); //сигнал проверки введенных данных
    connect(m_ui->status, &QSlider::valueChanged, this, &SongDialog::statusSetValue);//сигналы для отслеживания состояний слайдера
    connect(m_ui->status, &QSlider::sliderMoved, this, &SongDialog::statusSetValue);
    connect(m_ui->status, &QSlider::sliderPressed, this, &SongDialog::statusGetValue);
    connect(m_ui->status, &QSlider::sliderReleased, this, &SongDialog::statusGetValue);
    m_ui->buttonBox_OK->button(QDialogButtonBox::Ok)->setEnabled(false);
    QDir dir;
    if (!dir.exists(m_imageDir))
        dir.mkpath(m_imageDir);
}

SongDialog::~SongDialog()
{
    delete m_ui;
}

void SongDialog::choosePreview()
{
    const auto filename = QFileDialog::getOpenFileName(this, tr("Выберите изображение"),
        QString(), "(*.jpeg *.jpg *png *gif)");
    if (filename.isEmpty())
        return;
    const QString copyName = copiedPreview(filename);
    showPreview(copyName);
    check = true;
    isPixmap = 1;
    emit signalAll();
}

QString SongDialog::copiedPreview(const QString& filePath) const
{
    const QImage image(filePath);
    const auto smaller = image.scaled(m_ui->labelPreview->width(), m_ui->labelPreview->height(),
        Qt::AspectRatioMode::KeepAspectRatioByExpanding);

    QString name = "1.png";
    if (!smaller.save(fullImagePath(name), "PNG"))
        return QString();
    return  name;
}

void SongDialog::showPreview(const QString& relativePath) const
{

    if (relativePath.isEmpty())
        return;
    const auto fn = fullImagePath(relativePath);
    if (!QFile::exists(fn))
        return;

    const QPixmap pixmap(fn);
    m_ui->labelPreview->setPixmap(pixmap);
}


QString SongDialog::fullImagePath(const QString& relativePath) const
{
    QDir dir;
    dir.cd(m_imageDir);
    return dir.absoluteFilePath(relativePath);
}

void SongDialog::setToolStr(const QString &strTool)
{
    this->strTool = strTool;
    m_ui->buttonBox_OK->setToolTip(strTool);
}

void SongDialog::preview_draw(int &numb)//запись измененной картинки в таблицу
{
    if(check)
    {
        const auto fn = fullImagePath("1.png");
        const QPixmap pixmap(fn);
        QStandardItem *item = new QStandardItem();
        item->setData(pixmap, Qt::DecorationRole);
        model->setItem(numb, 0, item);
        check = false;
    }
}

void SongDialog::write_albom_info(int &numb)//перенос введенных данных в таблицу
{
    const QString slide = QString::number(m_ui->status->value());
    model->setItem(numb, 1, new QStandardItem(m_ui->lineEdit_name->text()));
    model->setItem(numb, 2, new QStandardItem(m_ui->lineEdit_author->text()));
    model->setItem(numb, 3, new QStandardItem(m_ui->lineEdit_time->text()));
    model->setItem(numb, 4, new QStandardItem(slide));
}

void SongDialog::set_info(int &numb)//заполнение данными из таблицы при нажатии кнопки редактировать
{
    m_ui->labelPreview->setPixmap(model->item(numb,0)->data(Qt::DecorationRole).value<QPixmap>());
    m_ui->lineEdit_name->setText((model->item(numb, 1))->text());
    m_ui->lineEdit_author->setText((model->item(numb, 2))->text());
    m_ui->lineEdit_time->setText((model->item(numb, 3))->text());
    m_ui->status->setSliderPosition(stoi((model->item(numb, 4)->text()).toStdString()));
    isPixmap = 1;
}

void SongDialog::on_buttonBox_OK_clicked(QAbstractButton *button)//сохранение изменений в таблицу либо добавление нового элемента
{
    if(button == m_ui->buttonBox_OK->button(QDialogButtonBox::Ok))
    {
        preview_draw(*num);
        write_albom_info(*num);
        (*num)++;
        cancelButtonClicked = false; //копка отмены не была нажата, значит произошли изменения, о чем мы сообщаем переменной cancelButtonClicked
    } else
    {
        cancelButtonClicked = true;
    }
}

void SongDialog::unlock_buttomBoxOK() //проверка на корректность введенных данных(они не пустые) или изменений(они должныы быть)
{
    if(isName + isTime + isPixmap + isAuthor == 4 && (isSongCreated || //если песня создавалась, то автоматически true и сверять данные не с чем
                                                           m_ui->lineEdit_name->text() != model->item(*num, 1)->text() ||
                                                           m_ui->lineEdit_author->text() != model->item(*num, 2)->text() ||
                                                           m_ui->lineEdit_time->text() != model->item(*num, 3)->text() ||
                                                           QString::number(m_ui->status->value()) != model->item(*num, 4)->text() ||
                                                           m_ui->labelPreview->pixmap()->toImage() != model->item(*num,0)->data(Qt::DecorationRole).value<QImage>()
                                                           ))
    {
        m_ui->buttonBox_OK->setToolTip("Ok");
        m_ui->buttonBox_OK->button(QDialogButtonBox::Ok)->setEnabled(true); //разблокировали кнопку ОК
    } else {
         m_ui->buttonBox_OK->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void SongDialog::on_lineEdit_name_textChanged(const QString &arg1) //3 очень похожих функций для отслеживания любых изменений в дталоговом окне
{

    if(m_ui->lineEdit_name->text() != "")
    {
        isName = 1;
        emit signalAll(); //включение сигнала, вызывающую функию разблокировки кнопки ОК, если данные корректны
        m_ui->lineEdit_name->setStyleSheet("background-color: rgb(255, 255, 255)");
    } else
    {
        m_ui->lineEdit_name->setStyleSheet("background-color: rgb(255, 144, 144)");
        m_ui->buttonBox_OK->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void SongDialog::on_lineEdit_author_textChanged(const QString &arg1)
{
    if(m_ui->lineEdit_author->text() != "")
    {
        isAuthor = 1;
        emit signalAll();
        m_ui->lineEdit_author->setStyleSheet("background-color: rgb(255, 255, 255)");
    } else
    {
        m_ui->lineEdit_author->setStyleSheet("background-color: rgb(255, 144, 144)");
        m_ui->buttonBox_OK->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void SongDialog::on_lineEdit_time_textChanged(const QString &arg1)
{
    if(m_ui->lineEdit_time->text() != "")
    {
        isTime = 1;
        emit signalAll();
        m_ui->lineEdit_time->setStyleSheet("background-color: rgb(255, 255, 255)");
    } else
    {
        m_ui->lineEdit_time->setStyleSheet("background-color: rgb(255, 144, 144)");
        m_ui->buttonBox_OK->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
/*
void SongDialog::textCheck(QAbstractLineEdit * editted, const QString &arg)
{
    if(editted->text() != "")
    {
        emit signalAll();
        editted->setStyleSheet("background-color: rgb(255, 255, 255)");
    } else
    {
        editted->setStyleSheet("background-color: rgb(255, 144, 144)");
        m_ui->buttonBox_OK->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
*/
