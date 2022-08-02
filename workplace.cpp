#include "workplace.h"
#include "ui_workplace.h"

Workplace::Workplace(QSqlDatabase& db_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Workplace),
    db(db_)
{
    ui->setupUi(this);
}

Workplace::~Workplace()
{
    delete ui;
}

/*-------------------------------------------------------------------------------------------------------------------
 *   Table - процедура, реализующая отображение данных реляционной таблицы.
 *   Формальные параметры:
 *   nameTable - название таблицы, которую необходимо сортировать;
 *   field - название столбца, по которому необходимо сортировать.
 *   Локальные переменные:
 *   query - объект класса QSqlQuery, SQL запрос к базе данных;
 *   n - контейнер с названиями столбцов в выбранной таблице;
 *   index, i - счетчики циклов.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::Table(QString nameTable){
    QSqlQuery query(db);
    // Выполнение запроса
    if (query.exec("SELECT * FROM " + nameTable)){
        ui-> tableWidget -> clear();
        // Отображение сетки на виджете
        ui-> tableWidget ->setShowGrid(true);
        // Отключение нулевого столбца с автоматической нумерацией строк
        ui -> tableWidget -> verticalHeader() -> setVisible(false);
        // Установка ширины столбцов по содержимому
        ui -> tableWidget -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
        // Установка количества столбцов
        ui -> tableWidget -> setRowCount(query.size()+5);
        // Установка количества строк
        ui-> tableWidget -> setColumnCount(query.record().count());

        Names.clear();
        // Обращение к базе данных для замены названия столбцов
        for (int i = 0; i < query.record().count(); i++)
            Names.push_back(query.record().fieldName(i));
        ui -> tableWidget -> setHorizontalHeaderLabels(Names);

        int index = 0;
        // Пока запрос содержит запись, передавать запись в виджет
        while (query.next()){
            ui -> tableWidget -> insertRow(index);
            for (int i = 0; i < query.record().count(); i++){
                ui -> tableWidget -> setItem(index, i, new QTableWidgetItem(query.value(i).toString()));
            }
            index++;
            }
    }
}
/*-------------------------------------------------------------------------------------------------------------------
 *   on_name_t_currentIndexChanged - процедура вывода записей реляционной таблицы в виджет формы.
 *   Формальный параметр:
 *   index - индекс выбранной таблицы в выпадающем списке на форме.
 *   Подпрограмма, используемая в процедуре:
 *   Table - процедура отображения данных реляционной таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_comboBox_currentIndexChanged(int index)
{
    index = ui->comboBox->currentIndex();
        switch (index){
        case 1:{
            Table("Client");
            break;
        }
        case 2:{
            Table("Sdelka");
            break;
        }
        case 3:{
            Table("Valuta");
            break;
        }
        case 4:{
            Table("Kassir");
            break;
        }
        }
}
/*-------------------------------------------------------------------------------------------------------------------
 *   on_add_clicked - процедура добавления записей в таблицу.
 *   Локальная переменная:
 *   index - индекс выбранной таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_add_clicked()
{
    int index = ui->comboBox->currentIndex();
    switch(index){
    case 1:{
        QString Id_client = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
        QString FIO_cl = ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text();
        QString Passport = ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->text();

        if (db.open()){
        // Запрос на добавление в таблицу
            QSqlQuery New(db);
            New.prepare("INSERT INTO Client (Id_client, FIO_cl, Passport) VALUES (:Id_client, :FIO_cl, :Passport);");
        // Позиционная вставка в запрос
            New.bindValue(":Id_client", Id_client);
            New.bindValue(":FIO_cl", FIO_cl);
            New.bindValue(":Passport", Passport);
        // Проверка выполнения запроса
            if (!New.exec())
            {
                QMessageBox::warning(this, "Error", "Запись не удалось создать");
            } else QMessageBox::information(this, "Выполнение запроса", "Запись успешно добавлена в таблицу");
        }
        break;
    }
    case 2:{
        QString Id_sdelka = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
        QString Id_pr = ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text();
        QString Id_kupl = ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->text();
        QString Id_kass = ui->tableWidget->item(ui->tableWidget->currentRow(), 3)->text();
        QString Id_client = ui->tableWidget->item(ui->tableWidget->currentRow(), 4)->text();
        QString Date_sd = ui->tableWidget->item(ui->tableWidget->currentRow(), 5)->text();
        QString Summ_pr = ui->tableWidget->item(ui->tableWidget->currentRow(), 6)->text();
        QString Summ_kupl = ui->tableWidget->item(ui->tableWidget->currentRow(), 7)->text();

        if (db.open()){
        // Запрос на добавление в таблицу
            QSqlQuery New(db);
            New.prepare("INSERT INTO Sdelka (Id_sdelka, Id_prod, Id_k, Id_kas, Id_cl, D_sd, Summ_pr, Summ_kupl)"
                        " VALUES (:Id_sdelka, :Id_prod, :Id_k, :Id_kas, :Id_cl, :D_sd, :Summ_pr, :Summ_kupl);");
        // Позиционная вставка в запрос
            New.bindValue(":Id_sdelka", Id_sdelka);
            New.bindValue(":Id_prod", Id_pr);
            New.bindValue(":Id_k", Id_kupl);
            New.bindValue(":Id_kas", Id_kass);
            New.bindValue(":Id_cl", Id_client);
            New.bindValue(":D_sd", Date_sd);
            New.bindValue(":Summ_pr", Summ_pr);
            New.bindValue(":Summ_kupl", Summ_kupl);
        // Проверка выполнения запроса
            if (!New.exec())
            {
                QMessageBox::warning(this, "Error", "Запись не удалось создать");
            } else QMessageBox::information(this, "Выполнение запроса", "Запись успешно добавлена в таблицу");
        }
        break;
    }
    case 3:{
        QString Id_val = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
        QString Name_val = ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text();
        QString Kurs_pr = ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->text();
        QString Kurs_pok = ui->tableWidget->item(ui->tableWidget->currentRow(), 3)->text();

        if (db.open()){
        // Запрос на добавление в таблицу
            QSqlQuery New(db);
            New.prepare("INSERT INTO Valuta (Id_val, Name_val, Kurs_pr, Kurs_pok) "
                        "VALUES (:Id_val, :Name_val, :Kurs_pr, :Kurs_pok)");
        // Позиционная вставка в запрос
            New.bindValue(":Id_val", Id_val);
            New.bindValue(":Name_val", Name_val);
            New.bindValue(":Kurs_pr", Kurs_pr);
            New.bindValue(":Kurs_pok", Kurs_pok);
        // Проверка выполнения запроса
            if (!New.exec())
            {
                QMessageBox::warning(this, "Error", "Запись не удалось создать");
            } else QMessageBox::information(this, "Выполнение запроса", "Запись успешно добавлена в таблицу");
        }
        break;
    }
    case 4:{
        QString Id_kassir = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();
        QString FIO_Kassir = ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text();

        if (db.open()){
        // Запрос на добавление в таблицу
            QSqlQuery New(db);
            New.prepare("INSERT INTO Kassir (Id_kassir, FIO_Kassir) VALUES (:Id_kassir, :FIO_Kassir);");
        // Позиционная вставка в запрос
            New.bindValue(":Id_kassir", Id_kassir);
            New.bindValue(":FIO_Kassir", FIO_Kassir);
        // Проверка выполнения запроса
            if (!New.exec())
            {
                QMessageBox::warning(this, "Error", "Запись не удалось создать");
            } else QMessageBox::information(this, "Выполнение запроса", "Запись успешно добавлена в таблицу");
        }
        break;
    }
    }
}
/*-------------------------------------------------------------------------------------------------------------------
 *   Del - процедура удаления записи из реляционной таблицы.
 *   Локальные переменные:
 *   Name_t - название выбранной таблицы;
 *   field - название поля записи с идентификатором таблицы;
 *   Id - значение идентификатора таблицы;
 *   Del - запрос на удаление записи из реляционной таблицы.
 *   Подпрограмма, используемая в процедуре:
 *   Table - процедура отображения данных реляционной таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::Del(){
    QString Name_t = tables[ui->comboBox->currentText()];
    QString field = Id[Name_t];
    QString Id = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text();

    if(db.open()){
        QSqlQuery Del(db);
        // Выполнение SQL запроса на удаление записи
        Del.exec("DELETE FROM " + QString(Name_t) +" WHERE " + QString(field) + " = " + Id);
        // Проверка выполнения запроса
        if(!Del.exec())
        {
            QMessageBox::warning(this, "Error", "Запись не удалось удалить");
        } else
            QMessageBox::information(this, "Удаление записи", "Запись успешно удалена");
    }
    Table(QString(Name_t));
}
/*-------------------------------------------------------------------------------------------------------------------
 *   on_del_clicked - слот нажатия кнопки для удаления записи из таблицы.
 *   Подпрограмма, используемая в процедуре:
 *   Del - процедура удаления записи из реляционной таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_del_clicked()
{
    Del();
}
/*-------------------------------------------------------------------------------------------------------------------
 *   on_upd_clicked - процедура изменения записи реляционной таблицы.
 *   Локальные переменные:
 *   newfield - новое значение поля записи реляционной таблицы;
 *   tab - название реляционной таблицы;
 *   Id_tab - идентификатор реляционной таблицы;
 *   Upd - запрос на изменение записи реляционной таблицы.
 *   Подпрограмма, используемая в процедуре:
 *   Table - процедура отображения данных реляционной таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_upd_clicked()
{
    QString newfield = ui->tableWidget->currentItem()->text();
    QString tab = tables[ui->comboBox->currentText()];
    QString Id_tab = Id[tab];

    QSqlQuery Upd(db);
    // SQL запрос на изменение данных
    Upd.prepare("UPDATE " + tab + " SET " + Names[ui->tableWidget->currentColumn()]
            + " = :new WHERE "+ Id_tab + " = " + ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text());
    Upd.bindValue(":new", newfield);
    // Выполнение запроса
    Upd.exec();
    // Проверка выполнения запроса
    if(!Upd.exec())
    {
        QMessageBox::warning(this, "Error", "Запись не обновлена");
    } else
        QMessageBox::information(this, "Обновление записи", "Запись успешно обновлена");

    Table(tab);
}

/*-------------------------------------------------------------------------------------------------------------------
 * sortTable - функция, реализующая сортировку таблиц базы данных.
 * Формальные параметры:
 * nameTable - название таблицы, которую необходимо сортировать;
 * field - название столбца, по которому необходимо сортировать.
 * Локальные переменные:
 * query - объект класса QSqlQuery, SQL запрос к базе данных;
 * n - контейнер с названиями столбцов в выбранной таблице;
 * index, i - счетчики циклов.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::sortTable(QString nameTable, QString field){
    // Очищение виджета вывода таблиц
    ui->tableWidget->clear();
    // Объявление SQL запроса к базе db
    QSqlQuery query(db);
    // Выполнение запроса
    if (query.exec("SELECT * FROM " + nameTable + " ORDER BY " + field)){
    // Обращение к базе данных для замены названия столбцов
        QStringList n;
        for (int i = 0; i < query.record().count(); i++)
            n.push_back(query.record().fieldName(i));
        ui -> tableWidget -> setHorizontalHeaderLabels(Names);
    // Пока запрос содержит запись, добавлять ее в виджет
        int index = 0;
        while (query.next()){
            ui -> tableWidget -> insertRow(index);
            for (int i = 0; i < query.record().count(); i++){
                ui -> tableWidget -> setItem(index, i, new QTableWidgetItem(query.value(i).toString()));
            }
            index++;
        }
    }
}
/*-------------------------------------------------------------------------------------------------------------------
 * on_sort_clicked - слот нажатия кнопки сортировки реляционной таблицы.
 * Локальные переменные:
 * name - название выбранной таблицы;
 * field - название столбца для сортировки.
 * Подпрограмма, используемая в процедуре:
 * sortTable - процедура сортировки реляционной таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_sot_clicked()
{
    QString name = tables[ui->comboBox->currentText()];
    QString field = Names[ui->tableWidget->currentColumn()];
    sortTable(name, field);
}
/*-------------------------------------------------------------------------------------------------------------------
 * read - процедура, реализующая запись данных таблиц базы из текстового файла.
 * Локальные переменные:
 * f - файл по указанному пути, из которого реализуется запись в БД;
 * query - объект класса QSqlQuery, SQL запрос;
 * outF - объект класса QTextStream, тектовый поток;
 * list - контейнер, содержащий данные для записи;
 * str - строка, содержащая записи таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::read()
{
    int table = ui->comboBox->currentIndex();
    switch(table){
    case 1:{
        QFile f("./inf.txt");
        QSqlQuery query;
        if (f.open(QIODevice::ReadOnly)) {
        QTextStream outF(&f);
        QList<QString>list;
        while (!outF.atEnd()) {
        QString str = outF.readLine();
        list = str.split(";");

        if (db.open()) {
        query.prepare("INSERT INTO Client (Id_client, FIO_cl, Passport) VALUES (:Id_client, :FIO_cl, :Passport);");
        query.bindValue(":Id_client", list[0]);
        query.bindValue(":FIO_cl", list[1]);
        query.bindValue(":Passport", list[2]);
        }
        if (!query.exec())
        this->setWindowTitle("Не удалось загрузить данные из файла!");
        else
        this->setWindowTitle("Данные успешно загружены из файла 'inf.txt'");
        }
        f.close();
        }
        break;
    }
    case 2:{
        QFile f("./inf.txt");
        QSqlQuery query;
        if (f.open(QIODevice::ReadOnly)) {
        QTextStream outF(&f);
        QList<QString>list;
        while (!outF.atEnd()) {
        QString str = outF.readLine();
        list = str.split(";");

        if (db.open()) {
        query.prepare("INSERT INTO Sdelka (Id_sdelka, Id_prod, Id_k, Id_kas, Id_cl, D_sd, Summ_pr, Summ_kupl)"
                      " VALUES (:Id_sdelka, :Id_prod, :Id_k, :Id_kas, :Id_cl, :D_sd, :Summ_pr, :Summ_kupl);");
        query.bindValue(":Id_sdelka", list[0]);
        query.bindValue(":Id_prod", list[1]);
        query.bindValue(":Id_k", list[2]);
        query.bindValue(":Id_kas", list[3]);
        query.bindValue(":Id_cl", list[4]);
        query.bindValue(":D_sd", list[5]);
        query.bindValue(":Summ_pr", list[6]);
        query.bindValue(":Summ_kupl", list[7]);
        }
        if (!query.exec())
        this->setWindowTitle("Не удалось загрузить данные из файла!");
        else
        this->setWindowTitle("Данные успешно загружены из файла 'inf.txt'");
        }
        f.close();
        }
        break;
    }
    case 3:{
        QFile f("./inf.txt");
        QSqlQuery query;
        if (f.open(QIODevice::ReadOnly)) {
        QTextStream outF(&f);
        QList<QString>list;
        while (!outF.atEnd()) {
        QString str = outF.readLine();
        list = str.split(";");

        if (db.open()) {
        query.prepare("INSERT INTO Valuta (Id_val, Name_val, Kurs_pr, Kurs_pok) "
                      "VALUES (:Id_val, :Name_val, :Kurs_pr, :Kurs_pok);");
        query.bindValue(":Id_val", list[0]);
        query.bindValue(":Name_val", list[1]);
        query.bindValue(":Kurs_pr", list[2]);
        query.bindValue(":Kurs_pok", list[3]);
        }
        if (!query.exec())
        this->setWindowTitle("Не удалось загрузить данные из файла!");
        else
        this->setWindowTitle("Данные успешно загружены из файла 'inf.txt'");
        }
        f.close();
        }
        break;
    }
    case 4:{
        QFile f("./inf.txt");
        QSqlQuery query;
        if (f.open(QIODevice::ReadOnly)) {
        QTextStream outF(&f);
        QList<QString>list;
        while (!outF.atEnd()) {
        QString str = outF.readLine();
        list = str.split(";");

        if (db.open()) {
        query.prepare("INSERT INTO Kassir (Id_kassir, FIO_Kassir) VALUES (:Id_kassir, :FIO_Kassir);");
        query.bindValue(":Id_kassir", list[0]);
        query.bindValue(":FIO_Kassir", list[1]);
        }
        if (!query.exec())
        this->setWindowTitle("Не удалось загрузить данные из файла!");
        else
        this->setWindowTitle("Данные успешно загружены из файла 'inf.txt'");
        }
        f.close();
        }
        break;
    }
    }
}
/*-------------------------------------------------------------------------------------------------------------------
 * on_files_currentIndexChanged - слот выбора действия с файлами.
 * Формальный параметр:
 * index - индекс выбранной команды из выпадающего списка на форме.
 * Подпрограммы, используемые в процедуре:
 * read - процедура чтения из файла;
 * Table - процедура вывода данных таблицы в виджет формы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_files_currentIndexChanged(int index)
{
    index = ui->files->currentIndex();
    switch(index){
    case 1:{
        // Получение названия таблицы БД
                QString table = tables[ui->comboBox->currentText()];
                if (db.open()) {
    // Выполнение SQL запроса к БД
                QSqlQuery query("SELECT * FROM " + table);
    // Создание файла по указанному пути
                QFile f("./inf.txt");
    // Открытие файла для записи
                if (f.open(QIODevice::WriteOnly)) {
                    QTextStream inF(&f);
    // Пока в запросе есть запись, записывать ее в файл
                    while (query.next()) {
                    for (int i = 0; i < query.record().count(); i++) {
    // Установка разделителей
                    inF << query.value(i).toByteArray() << "; ";
                    }
    // Переход потока на следующую строку
                    inF << "\n";
                    }
    // Проверка выполнения запроса к БД
                    if (!query.exec())
                        QMessageBox::warning(this, "Error", "Не удалось записать в файл");
                    else
                        QMessageBox::information(this, "Запись в файл", "Таблица успешно записана в файл 'inf.txt'");
                    f.close();       // Закрытие файла
                    }
                    db.close();     // Закрытие БД
                }
        break;
    }
    case 2:{
        read();
        Table(ui->comboBox->currentText());
        break;
    }
    }
}
/*-------------------------------------------------------------------------------------------------------------------
 * on_output_clicked - слот обновления таблицы.
 * Локальная переменная:
 * index - индекс выбранной команды из выпадающего списка на форме.
 * Подпрограмма, используемая в процедуре:
 * Table - процедура вывода данных таблицы в виджет формы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_output_clicked()
{
    int index = ui->comboBox->currentIndex();
        switch (index){
        case 1:{
            Table("Client");
            break;
        }
        case 2:{
            Table("Sdelka");
            break;
        }
        case 3:{
            Table("Valuta");
            break;
        }
        case 4:{
            Table("Kassir");
            break;
        }
        }
}
/*-------------------------------------------------------------------------------------------------------------------
 * on_commandLinkButton_clicked - отправление на печать.
 * Локальные переменные:
 * pr - объект класса QPrinter, использует общую систему печати Unix (CUPS) для отправки вывода PDF на принтер;
 * dlg - объект класса , предоставляющий диалоговое окно для указания конфигурации принтера;
 * name_table - название таблицы, выводимой на печать;
 * th - строка кода HTML, заполняющаяя заголовки таблицы;
 * Print - запрос SQL к базе данных на выборку из таблицы;
 * Col - вектор, хранящий названия столбцов таблицы;
 * i - счетчик цикла;
 * html - строка, содержащая код HTML таблицы;
 * doc - документ, в который записывается код HTML таблицы.
-------------------------------------------------------------------------------------------------------------------*/
void Workplace::on_commandLinkButton_clicked()
{
    QPrinter * pr = new QPrinter();
    QPrintDialog dlg(pr, this);
    QString name_table = tables[ui->comboBox->currentText()];

    QString th = "";

    db.open();
    // Создание запроса на выборку из таблицы базы
    QSqlQuery Print(db);
    if (Print.exec("SELECT * FROM " + name_table)){
    // Создание вектора названий столбцов таблицы
        QVector<QString> Col;
        for (int i = 0; i < Print.record().count(); i++)
            Col.push_back(Print.record().fieldName(i));
    // Формирование HTML кода для заголовков столбцов
        for (int i = 0; i < Col.size(); i++){
            th += "<td>" + Col[i] + "</td>";
        }
    };
    // Формирование HTML кода таблицы
    QString html ="<table border='1'> "
                                    // Запись заголовка таблицы в HTML код
                  "<caption>" + name_table + "</caption>"
                  "<tr>" + th + "</tr>";
    // Добавление записей в HTML код таблицы
    while (Print.next()){
        html+="<tr>";
        for (int i = 0; i < Print.record().count(); i++){
            html += "<td>" + Print.value(i).toString() + "</td>";
        }
        html += "</tr> \n";
    }
    html += "</table>";

    if(dlg.exec() == QDialog::Accepted){
                         // Формирование документа PDF для
                         // для отправки на печать
        QTextDocument doc;
        doc.setHtml(html);
        doc.print(pr);
    }
}

