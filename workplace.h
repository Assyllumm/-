/*-------------------------------------------------------------------------------------------------------------------
 * Форма workplace
 * Язык: C++
 *
 * Краткое описание:
 * Форма для работы с реляционными таблицами.
 *
 * Переменные, используемые в форме:
 * Names - контейнер, хранящий названия столбцов реляционной таблицы, полученные запросом к системной таблице SQLITE;
 * tables - контейнер пар (ключ-значение) названий таблиц базы данных;
 * Id - контейнер пар (ключ-значение) идентификаторов таблиц базы данных;
 * db -  файл базы данных.
 *
 * Функции, используемые в форме:
 * on_add_clicked - слот добавления записи в таблицу;
 * on_comboBox_currentIndexChanged - слот выбора названия таблицы из выпадающего списка на форме;
 * on_del_clicked - слот удаления записи из таблицы;
 * on_upd_clicked - слот изменения записи в таблице;
 * on_sort_clicked - слот сотрировки записей в таблице;
 * Table - процедура отображения записей реляционной таблицы в виджете формы;
 * Del - процедура удаления записи из реляционной таблицы;
 * sortTable - процедура сортировки записей реляционной таблицы;
 * on_files_currentIndexChanged - слот выбора команды для работы с файлами;
 * on_commandLinkButton_clicked - процедура отправки таблицы на печать в виде PDF файла;
 * on_out_clicked - обновление таблицы в виджете формы;
 * read - чтение данных из файла и запись в таблицу.
------------------------------------------------------------------------------------------------------------------*/

#ifndef WORKPLACE_H
#define WORKPLACE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

namespace Ui {
class Workplace;
}

class Workplace : public QDialog
{
    Q_OBJECT

public:
    explicit Workplace(QSqlDatabase& db_,QWidget *parent = nullptr);
    ~Workplace();

private slots:

    void on_comboBox_currentIndexChanged(int index);
    void on_add_clicked();
    void on_del_clicked();
    void on_upd_clicked();
    void on_sot_clicked();
    void on_files_currentIndexChanged(int index);
    void on_output_clicked();
    void on_commandLinkButton_clicked();

private:
    Ui::Workplace *ui;
    QSqlDatabase& db;
    void Table(QString nameTable);
    QStringList Names;
    void Del();
    void sortTable(QString nameTable, QString field);
    void read();

    std::map<QString, QString> tables = {{"Клиент", "Client"}, {"Сделка", "Sdelka"}, {"Валюта", "Valuta"}, {"Кассир", "Kassir"}};
    std::map <QString, QString> Id {{"Client", "Id_client"}, {"Sdelka", "Id_sdelka"}, {"Valuta", "Id_val"}, {"Kassir", "Id_kassir"}};
};

#endif // WORKPLACE_H
