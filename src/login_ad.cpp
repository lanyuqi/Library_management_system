//
// Created by 洛青宇 on 2023/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login_ad.h" resolved

#include <QMessageBox>
#include <QSqlQuery>
#include "../include/login_ad.h"
#include "../include/library_login.h"
#include "../include/admin_main.h"
#include "ui_Login_ad.h"


Login_ad::Login_ad(QWidget *parent) :
        QWidget(parent), ui(new Ui::Login_ad) {
    ui->setupUi(this);

    db = new Database(this);


    this->setWindowTitle("管理员登录");
    //点击返回时，显示主界面
    connect(ui->pushButton_back, &QPushButton::clicked, this, [=]() {
        Library_Login *library_login = new Library_Login;
        library_login->show();
        this->close();
    });
    //点击登录时，显示管理员主界面
    connect(ui->pushButton_login, &QPushButton::clicked, this, &Login_ad::on_loginButton_clicked);
}

void Login_ad::on_loginButton_clicked() {
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "警告", "用户名或密码不能为空");
        return;
    }

    //查询账户密码后，登陆
    QSqlQuery query(db->getDatabase());
    query.prepare("SELECT * FROM administrators WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        QMessageBox::information(this, "登录成功", "欢迎 " + username + "！");
        Admin_main *admin_main = new Admin_main;
        connect(this, &Login_ad::userLogin, admin_main, &Admin_main::handleUserLogin);
        emit userLogin(username, password);
        admin_main->show();
        this->close();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误。");
    }
}


Login_ad::~Login_ad() {
    delete ui;
}
