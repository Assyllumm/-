#include "input.h"
#include "ui_input.h"
#include "workplace.h"

Input::Input(QSqlDatabase& db_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Input),
    db(db_)
{
    ui->setupUi(this);
    // Вывод на форму изображения
    QPixmap img(":/img/input.png");
    int w = ui->img->width();
    int h = ui->img->height();
    ui->img->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}

Input::~Input()
{
    delete ui;
}
/*--------------------------------------------------------------------------------------------------
 *   on_Show_clicked - слот нажатия на кнопку входа.
 *   Локальные переменные:
 *   Log_in - логин пользователя;
 *   Pas_in - пароль пользователя;
 *   Select_us - SQL запрос на выборку;
 *   db - база данных.
 *   Метод, используемый в процедуре:
 *   lastError - метод вывода последней ошибки запроса в консоль.
--------------------------------------------------------------------------------------------------*/
void Input::on_Show_clicked()
{
    QString Log_in = ui->Log_in->text();
    QString Pas_in = ui->Pas_in->text();

    Select_us = new QSqlQuery(db);
    Select_us->prepare("SELECT * FROM User WHERE Login = :Login AND Password = :Password");
    Select_us->bindValue(":Login", Log_in);
    Select_us->bindValue(":Password", Pas_in);
    Select_us->exec();
    if (!Select_us->exec()){
        qDebug() << Select_us->lastError();
    }
    // Проверка наличия пользователя в базе данных
    if(Select_us->next()){
    // Переход на форму работы с базой данных
        qDebug() << "Вход выполнен";
        Workplace *work = new Workplace(db);
        work->show();
    } else {
    // Предупреждение о незарегистрированном пользователе
        QMessageBox::warning(this, "Ошибка", "Пользователя не существует");
    }
}

