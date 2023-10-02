//
// Created by 洛青宇 on 2023/4/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Library_Login.h" resolved

#include "../include/library_login.h"
#include "../database/CustomSqlQueryModel.h"
#include "../include/login_ad.h"
#include "../include/login_st.h"
#include "ui_Library_Login.h"


Library_Login::Library_Login(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Library_Login) {
    ui->setupUi(this);

    this->setWindowTitle("图书馆管理系统");
    //设置窗口大小
    this->setFixedSize(800, 600);

    //向tableview中添加数据
    CustomSqlQueryModel *model = new CustomSqlQueryModel(this);
    model->setQuery("SELECT * FROM books");
    ui->Book_View->setModel(model);
    ui->Book_View->hideColumn(0);
    ui->Book_View->resizeColumnsToContents();

    //当点击管理员登录按钮时，显示管理员登录窗口
    connect(ui->pushButton_mane, &QPushButton::clicked, this, [=]() {
        Login_ad *login_ad = new Login_ad;
        login_ad->show();
        this->close();
    });

    //点击学生登录按钮时，显示学生登录窗口
    connect(ui->pushButton_student, &QPushButton::clicked, this, [=]() {
        Login_st *login_st = new Login_st;
        login_st->show();
        this->close();
    });

}

Library_Login::~Library_Login() {
    delete ui;
}
