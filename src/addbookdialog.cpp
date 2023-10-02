//
// Created by 洛青宇 on 2023/4/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AddBookDialog.h" resolved

#include "../include/addbookdialog.h"
#include "ui_AddBookDialog.h"


AddBookDialog::AddBookDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AddBookDialog) {
    ui->setupUi(this);

    connect(ui->pushButton_yes, &QPushButton::clicked, this, [=]() {
        this->title = ui->lineEdit_title->text();
        this->author = ui->lineEdit_author->text();
        this->publisher = ui->lineEdit_publisher->text();
        this->ISBN = ui->lineEdit_ISBN->text();
        if (title.isEmpty()||author.isEmpty()||publisher.isEmpty()||ISBN.isEmpty()) {
            QMessageBox::warning(this, "警告", "输入框不能为空");
        }
        add_book();
    });

    connect(ui->pushButton_return, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

void AddBookDialog::add_book() {
    QSqlQuery query;
    query.prepare("INSERT INTO books (title, author, publisher, ISBN)"
                  " VALUES (:title, :author, :publisher, :ISBN)");
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":publisher", publisher);
    query.bindValue(":ISBN", ISBN);
    if (query.exec()) {
        QMessageBox::information(this, "提示", "图书添加成功");
        accept();
    } else {
        QMessageBox::warning(this, "警告", "图书添加失败");
    }

}

AddBookDialog::~AddBookDialog() {
    delete ui;
}
