#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "input.h"
#include "Test_log_pas.h"
#include "test_mod.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Вывод на форму изображения
    QPixmap img(":/img/reg.png");
    int w = ui->image->width();
    int h = ui->image->height();
    ui->image->setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./database.db");
    db.open();
    if (db.open()){
        qDebug() << "open";
    } else qDebug() << "not open";

    // Создание таблиц в базе данных
    createUs = new QSqlQuery(db);
    createUs->prepare("CREATE TABLE IF NOT EXISTS User "
                      "(Id_us    INTEGER PRIMARY KEY,"
                      "Login    VARCHAR,"
                      "Password VARCHAR);");
    if(createUs->exec()){
        qDebug() << "create";
    } else qDebug() << createUs->lastError();


    createClient = new QSqlQuery(db);
    createClient->prepare(""
                          "CREATE TABLE IF NOT EXISTS Client "
                          "(Id_client INTEGER      PRIMARY KEY AUTOINCREMENT, "
                          "FIO_cl    VARCHAR (75) UNIQUE, "
                          "Passport  VARCHAR (11) UNIQUE);");
    if(createClient->exec()){
        qDebug() << "create";
    } else qDebug() << "error";

    createValuta = new QSqlQuery(db);
    createValuta->prepare("CREATE TABLE IF NOT EXISTS Valuta "
                          "(Id_val   INTEGER      PRIMARY KEY AUTOINCREMENT,"
                          "Name_val VARCHAR (50),"
                          "Kurs_pr  VARCHAR,"
                          "Kurs_pok VARCHAR);");
    if(createValuta->exec()){
        qDebug() << "create";
    } else qDebug() << "error";

    createKassir = new QSqlQuery(db);
    createKassir->prepare("CREATE TABLE IF NOT EXISTS Kassir "
                          "(Id_kassir  INTEGER      PRIMARY KEY AUTOINCREMENT,"
                          "FIO_Kassir VARCHAR (75) UNIQUE);");
    if(createKassir->exec()){
        qDebug() << "create";
    } else qDebug() << "error";

    createSdelka = new QSqlQuery(db);
    QString st = "CREATE TABLE IF NOT EXISTS Sdelka ("
                 "Id_sdelka INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Id_prod     INTEGER, "
                 "Id_k   INTEGER,"
                 "Id_kas   INTEGER,"
                 "Id_cl   INTEGER,"
                 "D_sd   VARCHAR,"
                 "Summ_pr   VARCHAR,"
                 "Summ_kupl VARCHAR, "
                 "FOREIGN KEY (Id_prod)  REFERENCES Valuta (Id_val) ON DELETE CASCADE,"
                 "FOREIGN KEY (Id_k)  REFERENCES Valuta (Id_val) ON DELETE CASCADE,"
                 "FOREIGN KEY (Id_kas)  REFERENCES Kassir (Id_kassir) ON DELETE CASCADE,"
                 "FOREIGN KEY (Id_cl)  REFERENCES Client (Id_client) ON DELETE CASCADE"
                 ");";
    createSdelka->prepare(st);

    if(createSdelka->exec()){
        qDebug() << "create";
    } else qDebug() << createSdelka->lastError();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*--------------------------------------------------------------------------------------------------
 *   on_Registr_clicked - слот перехода на форму регистрации.
 *   Локальные переменные:
 *   Log - логин пользователя;
 *   Pass - пароль пользователя;
 *   Lp - объект класса модульного теста;
 *   Registr - SQL запрос на добавление;
 *   st - строка с SQL запросом;
 *   db - база данных.
 *   Метод, используемый в процедуре:
 *   lastError - метод вывода последней ошибки запроса в консоль.
--------------------------------------------------------------------------------------------------*/
void MainWindow::on_Registr_clicked()
{
    QString Log = ui->Login->text();
    QString Pass = ui->Password->text();
    Log_pas Lp;

    if(Lp.Reg(Log, Pass)){
        if (db.open()){
            qDebug() << "base open";
        } else qDebug() << "base not open";

        Registr = new QSqlQuery(db);
        QString st = "INSERT INTO User (Login, Password ) VALUES (:Login , :Password);";
        Registr->prepare(st);
        Registr->bindValue(":Login", Log);
        Registr->bindValue(":Password", Pass);

        if (Registr->exec()){
            QMessageBox::information(this, "Регистрация", "Пользователь успешно зарегистрирован");
            qDebug() << Registr->lastError();
        } else QMessageBox::warning(this, "Ошибка регистрации", "Пользователь не зарегистрирован");
    } else QMessageBox::warning(this, "Ошибка регистрации", "Формат логина или пароля несоответствует требуемому");

}
/*--------------------------------------------------------------------------------------------------
 *   on_Avtoriz_clicked - слот нажатия на кнопку входа.
 *   Локальная переменная:
 *   in - объект класса Input.
 *   Метод, используемый в процедуре:
 *   show - метод открытия формы..
--------------------------------------------------------------------------------------------------*/
void MainWindow::on_Avtoriz_clicked()
{
    Input *in = new Input(db);
    in->show();
}

