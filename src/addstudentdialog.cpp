//
// Created by 洛青宇 on 2023/4/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AddStudentDialog.h" resolved

#include "../include/addstudentdialog.h"
#include "ui_AddStudentDialog.h"


AddStudentDialog::AddStudentDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AddStudentDialog) {
    ui->setupUi(this);

    connect(ui->pushButton_yes, &QPushButton::clicked, this, [=]() {
        this->student_number = ui->lineEdit_student_number->text();
        this->name = ui->lineEdit_name->text();
        this->password = ui->lineEdit_pwd->text();
        this->email = ui->lineEdit_email->text();
        this->phone = ui->lineEdit_phone->text();
        if (student_number.isEmpty()||name.isEmpty()||password.isEmpty()||email.isEmpty()||phone.isEmpty()) {
            QMessageBox::warning(this, "警告", "输入框不能为空");
        }else {
            add_student();
        }
    });

    connect(ui->pushButton_return, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

AddStudentDialog::~AddStudentDialog() {
    delete ui;
}
void AddStudentDialog::add_student() {
    QSqlQuery query;
    query.prepare("INSERT INTO students (student_number, name, password, email, phone_number)"
                  " VALUES (:student_number, :name, :password, :email, :phone_number)");
    query.bindValue(":student_number", student_number);
    query.bindValue(":name", name);
    query.bindValue(":password", password);
    query.bindValue(":email", email);
    query.bindValue(":phone_number", phone);

    if (query.exec()) {
        QMessageBox::information(this, "提示", "学生添加成功");
        accept();
    } else {
        qDebug() << "Error:" << query.lastError().text();
        QMessageBox::warning(this, "警告", "学生添加失败");
    };

}
