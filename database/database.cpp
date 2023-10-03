//
// Created by 洛青宇 on 2023/4/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Database.h" resolved

#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSettings>
#include "ui_Database.h"


Database::Database(QWidget *parent) :
        QWidget(parent), ui(new Ui::Database) {
    ui->setupUi(this);

    this->setWindowTitle("数据库");
    // 读取配置文件
    QSettings settings("../config.ini", QSettings::IniFormat);
    QString hostname = settings.value("database/hostname").toString();
    int port = settings.value("database/port").toInt();
    QString dbName = settings.value("database/name").toString();
    QString username = settings.value("database/username").toString();
    QString password = settings.value("database/password").toString();

    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(username);
    db.setPassword(password);

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
