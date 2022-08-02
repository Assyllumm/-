/*-------------------------------------------------------------------------------------------------------------------
 * Форма input
 * Язык: C++
 * Краткое описание:
 * Форма авторизации.
 *
 * Переменная, используемая в форме:
 * Select_us - SQL-запрос на выборку данных о всех пользователях из базы данных;
 * db -  файл базы данных.
 *
 * Функции, используемые в форме:
 * on_Show_clicked - слот нажатия кнопки выхода.
------------------------------------------------------------------------------------------------------------------*/
#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QSqlDatabase& db_, QWidget *parent = nullptr);
    ~Input();

private slots:
    void on_Show_clicked();

private:
    Ui::Input *ui;
    QSqlDatabase& db;
    QSqlQuery *Select_us;
};

#endif // INPUT_H
