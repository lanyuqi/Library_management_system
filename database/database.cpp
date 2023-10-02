//
// Created by 洛青宇 on 2023/4/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Database.h" resolved

#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "ui_Database.h"


Database::Database(QWidget *parent) :
        QWidget(parent), ui(new Ui::Database) {
    ui->setupUi(this);

    this->setWindowTitle("数据库");

    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("175.178.88.47");
    db.setPort(3306);
    db.setDatabaseName("librarymanage");
    db.setUserName("LibraryManage");
    db.setPassword( "ltb85523021");

    if (!db.open()) {
        QMessageBox::critical(nullptr, "错误", "无法连接到数据库。");
    };
}


bool Database::isConnect() {
    return db.isOpen();
}

QSqlDatabase Database::getDatabase() {
    return db;
}

Database::~Database() {
    if(db.isOpen())
        db.close();
    delete ui;
}
