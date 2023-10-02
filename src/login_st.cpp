//
// Created by 洛青宇 on 2023/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_login_st.h" resolved

#include <QMessageBox>
#include <QSqlQuery>
#include "../include/stu_main.h"
#include "../include/login_st.h"
#include "../include/library_login.h"
#include "../include/stu_main.h"
#include "ui_login_st.h"


Login_st::Login_st(QWidget *parent) :
        QWidget(parent), ui(new Ui::Login_st) {
    ui->setupUi(this);

    db = new Database(this);
    //设置为密码
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("学生登录");
    //点击返回时，显示主界面
    connect(ui->pushButton_back, &QPushButton::clicked, this, [=]() {
        Library_Login *library_login = new Library_Login;
        library_login->show();
        this->close();
    });

    //点击登录时，显示学生主界面
    connect(ui->pushButton_login, &QPushButton::clicked, this, &Login_st::on_loginButton_clicked);


}

void Login_st::on_loginButton_clicked() {
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "警告", "用户名或密码不能为空");
        return;
    }

    //查询账户密码后，登陆
    QSqlQuery query(db->getDatabase());
    query.prepare("SELECT * FROM students WHERE student_number = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        QMessageBox::information(this, "登录成功", "欢迎 " + username + "！");
        Stu_main *stu_main = new Stu_main(username, password);
        connect(this, &Login_st::userLogin, stu_main, &Stu_main::handleUserLogin);
        emit userLogin(username, password); //传递学号与密码
        stu_main->show();
        this->close();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误。");
    }
}

Login_st::~Login_st() {
    delete ui;
}
