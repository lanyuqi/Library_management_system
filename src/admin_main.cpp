//
// Created by 洛青宇 on 2023/4/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Admin_main.h" resolved

#include "../include/admin_main.h"
#include "ui_Admin_main.h"
#include "../database/studentSqlQueryModel.h"
#include <QApplication>
#include <QTableView>
#include <QSqlError>
#include <QMessageBox>
#include "../include/login_ad.h"
#include "../include/library_login.h"
#include "../include/editstudentdialog.h"

Admin_main::Admin_main(QWidget *parent) :
        QWidget(parent), ui(new Ui::Admin_main) {
    ui->setupUi(this);

    this->setWindowTitle("管理员主界面");

    //点击退出系统时，退出程序
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        if (ui->listWidget->row(item ) == 5) {
            return QApplication::exit();
        }
    });

    //点击退出登陆时，显示图书界面
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        if (ui->listWidget->row(item ) == 4) {
            Library_Login *library_login = new Library_Login;
            library_login->show();
            this->close();
        }
    });

    //默认界面设置为0
    studentSqlQueryModel model;
    ui->stackedWidget->setCurrentIndex(0);
    ui->label->setText("系统管理");
    ui->label_welcome->setText("欢迎您，管理员"+ this->username);
    ui->label_student_number->setText(model.getColumnCount("students","student_number"));
    ui->label_loans->setText(model.getColumnCount("loans","borrower_id"));
    ui->label_library_number->setText(model.getColumnCount("books","isbn"));
    ui->label_overtime->setText(model.getOverdueCount("loans","start_date","end_date"));


    //创建数据模型提供tableview显示
    model_stu = new studentSqlQueryModel(this);
    model_book = new studentSqlQueryModel(this);
    model_loans = new studentSqlQueryModel(this);

    //实现搜索功能
    QSortFilterProxyModel *proxyModel_stu = new QSortFilterProxyModel(this);
    QSortFilterProxyModel *proxyModel_book = new QSortFilterProxyModel(this);
    QSortFilterProxyModel *proxyModel_loans = new QSortFilterProxyModel(this);
    proxyModel_stu->setSourceModel(model_stu);
    proxyModel_book->setSourceModel(model_book);
    proxyModel_loans->setSourceModel(model_loans);
    ui->tableView_student->setModel(proxyModel_stu);
    ui->tableView_book->setModel(proxyModel_book);
    ui->tableView_loans->setModel(proxyModel_loans);

    //切换左侧导航栏进行切换页面，同时设置当前页面的数据模型
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        switch (ui->listWidget->row(item)) {
            case 0:
                //管理员界面
                ui->stackedWidget->setCurrentIndex(0);
                break;
            case 1:
                //学生信息界面
                ui->stackedWidget->setCurrentIndex(2);
                CurrentProxyModel = proxyModel_stu;
                model_stu->setModel(1);
                proxyModel_stu->setSourceModel(model_stu);
                ui->tableView_student->setModel(proxyModel_stu);
                ui->tableView_student->update();
                break;
            case 2:
                //图书信息界面
                ui->stackedWidget->setCurrentIndex(4);
                CurrentProxyModel = proxyModel_book;
                model_book->setModel(2);
                proxyModel_book->setSourceModel(model_book);
                ui->tableView_book->setModel(proxyModel_book);
                ui->tableView_book->update();
                break;
            case 3:
                //借阅信息界面
                ui->stackedWidget->setCurrentIndex(3);
                CurrentProxyModel = proxyModel_loans;
                model_loans->setModel(3);
                proxyModel_loans->setSourceModel(model_loans);
                ui->tableView_loans->setModel(proxyModel_loans);
                ui->tableView_loans->update();
                break;
            case 4:

                ui->stackedWidget->setCurrentIndex(5);
                break;
        }
    });

    connect(ui->pushButton_pwd, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

    //修改密码界面
    ui->lineEdit_oldpasswd->setPlaceholderText("请输入原密码");
    ui->lineEdit_newpasswd->setPlaceholderText("请输入新密码");
    ui->lineEdit_newpasswd_2->setPlaceholderText("请再次输入新密码");
    connect(ui->pushButton_back, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->pushButton_update,&QPushButton::clicked,this,&Admin_main::on_updatePassword_clicked);
    //学生信息界面
    ui->tableView_student->hideColumn(0);
    ui->tableView_student->resizeColumnsToContents();
    ui->lineEdit_search->setPlaceholderText("请输您要搜索的内容");
    connect(ui->pushButton_search, &QPushButton::clicked,
            this, [=](){on_searchButton_clicked(ui->lineEdit_search->text());});
    //添加学生
    connect(ui->pushButton_addstu, &QPushButton::clicked, this, [=](){
        on_addButton_clicked(ObjectType::Student,model_stu);
    });
    //修改学生
    connect(ui->pushButton_alter_stu, &QPushButton::clicked, this, [=](){
        on_editButton_clicked(ObjectType::Student);
    });
    //删除学生
    connect(ui->pushButton_delstu,&QPushButton::clicked,this, [=]() {
        on_deleteButton_clicked("students", "student_number", ui->tableView_student);
        ui->tableView_student->update();
    });

    //图书信息界面
    ui->tableView_book->hideColumn(0);
    ui->tableView_book->resizeColumnsToContents();
    ui->lineEdit_Book_search->setPlaceholderText("请输您要搜索的内容");
    connect(ui->pushButton_book_search, &QPushButton::clicked,
            this, [=](){on_searchButton_clicked(ui->lineEdit_Book_search->text());});
    //归还图书
    connect(ui->pushButton_loans_book, &QPushButton::clicked,this, [=](){
        on_deleteButton_clicked("loans", "borrower_id", ui->tableView_loans);});
    //添加图书
    connect(ui->pushButton_add_book, &QPushButton::clicked, this, [=](){
        on_addButton_clicked(ObjectType::Book,model_book);
    });
//修改图书
    connect(ui->pushButton_alter_book, &QPushButton::clicked, this, [=](){
        on_editButton_clicked(ObjectType::Book);
    });
    //删除图书
    connect(ui->pushButton_delete_book,&QPushButton::clicked,this, [=]() {
        on_deleteButton_clicked("books", "title", ui->tableView_book);});
    //借阅信息界面
    ui->tableView_loans->hideColumn(0);
    ui->tableView_loans->resizeColumnsToContents();
    ui->lineEdit_loan_search->setPlaceholderText("请输您要搜索的内容");
    connect(ui->pushButton_loans_search, &QPushButton::clicked,
            this, [=](){on_searchButton_clicked(ui->lineEdit_loan_search->text());});
    //归还图书
    connect(ui->pushButton_loans,&QPushButton::clicked,this, [=]() {
        on_deleteButton_clicked("loans", "isbn", ui->tableView_loans);
    });

    connect(ui->pushButton_search, &QPushButton::clicked,
            this, [=](){on_searchButton_clicked(ui->lineEdit_loan_search->text());});



}

//获取上一窗口传递的密码与用户
void Admin_main::handleUserLogin(QString &user_name, QString &pass_word) {
    this->username = user_name;
    this->password = pass_word;
}

//修改密码
void Admin_main::on_updatePassword_clicked() {
    QString oldPwd = ui->lineEdit_oldpasswd->text();

    QString newPwd = ui->lineEdit_newpasswd->text();
    QString newPwd2 = ui->lineEdit_newpasswd_2->text();
    if (oldPwd != password) {
        QMessageBox::warning(this, "警告", "原密码错误");
        return;
    }
    if (newPwd != newPwd2) {
        QMessageBox::warning(this, "警告", "两次输入的新密码不一致");
        return;
    }
    QSqlQuery query;
    query.prepare("update administrators set password = ? where username = ?");
    query.addBindValue(newPwd);
    query.addBindValue(username);
    if (query.exec()) {
        QMessageBox::information(this, "提示", "修改成功");
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        QSqlError error = query.lastError();
        QMessageBox::warning(this, "警告", "修改失败"  + error.text());
    }
}

//搜索
void Admin_main::on_searchButton_clicked(QString line) {
    QString search = line;

    CurrentProxyModel->setFilterFixedString(search);
    CurrentProxyModel->setFilterKeyColumn(-1);
}

//添加信息
void Admin_main::on_addButton_clicked(ObjectType type, studentSqlQueryModel *model ){
    QDialog *dialog = nullptr;
    switch (type) {
        case ObjectType::Student:
            dialog = new AddStudentDialog(this);
            break;
        case ObjectType::Book:
            dialog = new AddBookDialog(this);
            break;
    }

    if (dialog && dialog->exec() == QDialog::Accepted) {
        // 添加成功，根据类型刷新相应的数据模型
        model->setQuery(model->query().lastQuery());
    }
}

//修改信息
void Admin_main::on_editButton_clicked(ObjectType type) {

    QDialog *editDialog = nullptr;
    QModelIndexList selectedRows;
    switch (type) {
        case ObjectType::Student:
            selectedRows = ui->tableView_student->selectionModel()->selectedRows();

            if (selectedRows.isEmpty()) {
                QMessageBox::warning(this, "警告", "请先选择要修改的行");
                return;
            }
            editDialog= new EditStudentDialog(model_stu, selectedRows.first(), this);
            break;
        case ObjectType::Book:
            selectedRows = ui->tableView_book->selectionModel()->selectedRows();

            editDialog = new EditBookiDalog(model_book, selectedRows.first(), this);
            break;
    }


    if (editDialog->exec() == QDialog::Accepted) {
        // 刷新数据模型
        model_stu->setQuery(model_stu->query().lastQuery());
    }

    delete editDialog;
}
//删除信息
void Admin_main::on_deleteButton_clicked(const QString &tableName, const QString &idColumnName, QTableView *tableView) {
    // 获取选中的行
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的行");
        return;
    }

    // 确认删除操作
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除", "确认删除选定记录？", QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }
    // 删除选中的行
    for (const QModelIndex &index : selectedRows) {
        QString id = index.sibling(index.row(), 1).data().toString();

        QSqlQuery query;
        query.prepare(QString("DELETE FROM %1 WHERE %2 = :id").arg(tableName, idColumnName));
        qDebug() << " delete:" << id;
        query.bindValue(":id", id);
        if (!query.exec()) {
            QMessageBox::warning(this,"提示","删除失败");
            qDebug() << "Error:" << query.lastError().text();

        }else{
            QMessageBox::information(this,"提示","删除成功！");
            qDebug() << "Executed query:" << query.executedQuery();
            }
        }
    }


Admin_main::~Admin_main() {
    delete ui;
}


