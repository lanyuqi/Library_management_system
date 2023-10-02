//
// Created by 洛青宇 on 2023/4/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EditStudentDialog.h" resolved

#include "../include/editstudentdialog.h"
#include "ui_EditStudentDialog.h"


EditStudentDialog::EditStudentDialog(studentSqlQueryModel *model, const QModelIndex &index,QWidget *parent) :
        QDialog(parent), ui(new Ui::EditStudentDialog) {
    ui->setupUi(this);
    //从Qmodelindex中获取学号
    m_student_number = index.sibling(index.row(), 1).data().toString();
    connect(ui->pushButton_yes, &QPushButton::clicked, this, [=]() {
        this->student_number = ui->lineEdit_student_number->text();
        this->name = ui->lineEdit_name->text();
        this->password = ui->lineEdit_pwd->text();
        this->email = ui->lineEdit_email->text();
        this->phone = ui->lineEdit_phone->text();
        if (student_number.isEmpty()||name.isEmpty()||password.isEmpty()||email.isEmpty()||phone.isEmpty()) {
            QMessageBox::warning(this, "警告", "输入框不能为空");
        }else {
            update_student();
        }});
}

void EditStudentDialog::update_student() {

    QSqlQuery query;
    query.prepare("UPDATE students SET student_number = :student_number, name = :name, password = :password, "
                  "email = :email, phone_number = :phone_number WHERE student_number = :m_student_number");
    query.bindValue(":student_number", student_number);
    query.bindValue(":name", name);
    query.bindValue(":password", password);
    query.bindValue(":email", email);
    query.bindValue(":phone_number", phone);
    query.bindValue(":m_student_number", m_student_number);

    if (query.exec()) {
        QMessageBox::information(this, "提示", "学生更新成功");
        qDebug()<<query.executedQuery();
        accept();
    } else {
        qDebug() << "Error:" << query.lastError().text();
        QMessageBox::warning(this, "警告", "学生更新失败");
    };

}



EditStudentDialog::~EditStudentDialog() {
    delete ui;
}
