/*--------------------------------------------------------------------------------------------------
 * Форма MainWindow
 * Язык: C++
 * Краткое описание:
 * Форма регистрации.
 *
 * Переменная, используемая в форме:
 * db -  файл базы данных;
 * createUs - SQL-запрос на создание таблицы с пользователями системы;
 * createClient - SQL-запрос на создание таблицы клиентов;
 * createValuta - SQL-запрос на создание таблицы валют;
 * createKassir - SQL-запрос на создание таблицы кассиров;
 * createSdelka - SQL-запрос на создание таблицы сделок;
 * Registr - SQL-запрос на создание нового пользователя.
 *
 * Функции, используемые в форме:
 * on_Registr_clicked - слот перехода на форму регистрации;
 * on_Avtoriz_clicked - слот авторизации пользователя.
--------------------------------------------------------------------------------------------------*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Registr_clicked();
    void on_Avtoriz_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *createUs;
    QSqlQuery *createClient;
    QSqlQuery *createValuta;
    QSqlQuery *createKassir;
    QSqlQuery *createSdelka;
    QSqlQuery *Registr;
};
#endif // MAINWINDOW_H
