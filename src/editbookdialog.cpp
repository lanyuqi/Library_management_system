//
// Created by 洛青宇 on 2023/4/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_EditBookiDalog.h" resolved

#include "../include/editbookdialog.h"
#include "ui_EditBookiDalog.h"


EditBookiDalog::EditBookiDalog(studentSqlQueryModel *model, const QModelIndex &index,QWidget *parent) :
        QDialog(parent), ui(new Ui::EditBookiDalog) {
    ui->setupUi(this);
    book_isbn = index.sibling(index.row(), 2).data().toString();
    connect(ui->pushButton_yes, &QPushButton::clicked, this, [=]() {
        this->title = ui->lineEdit_title->text();
        this->author = ui->lineEdit_author->text();
        this->publisher = ui->lineEdit_publisher->text();
        this->isbn = ui->lineEdit_ISBN->text();
        if (title.isEmpty()||author.isEmpty()||publisher.isEmpty()||isbn.isEmpty()) {
            QMessageBox::warning(this, "警告", "输入框不能为空");
        }else {
            update_book();
        }});
    connect(ui->pushButton_return, &QPushButton::clicked, this, [=]() {
        this->close();
    });
}

void EditBookiDalog::update_book() {

    QSqlQuery query;
    query.prepare("UPDATE books SET title = :titler, isbn = :isbn, author = :author, "
                  "publisher = :publisher  WHERE isbn = :b_isbn");
   query.bindValue(":titler", title);
   query.bindValue(":isbn", isbn);
    query.bindValue(":author", author);
    query.bindValue(":publisher", publisher);
    query.bindValue(":b_isbn", book_isbn);

    if (query.exec()) {
        QMessageBox::information(this, "提示", "图书更新成功");
        qDebug()<<query.executedQuery();
        accept();
    } else {
        qDebug() << "Error:" << query.lastError().text();
        QMessageBox::warning(this, "警告", "图书更新失败");
    };

}

EditBookiDalog::~EditBookiDalog() {
    delete ui;
}
