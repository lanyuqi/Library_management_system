//
// Created by 洛青宇 on 2023/4/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Stu_main.h" resolved

#include "../include/stu_main.h"
#include "ui_stu_main.h"
#include "../include/library_login.h"


Stu_main::Stu_main(const QString &username, const QString & password,
                   QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Stu_main) {
    ui->setupUi(this);
    this->username = username;
    this->password = password;
    ui->label_welcome_2->setText("欢迎您，" + username + "同学");
    StudentSqlModel model;
    this->student_name = model.getUser("students", "name",username);
    ui->label_loans_2->setText(model.queryDataByUsername("loans", "borrower_id", username));
    ui->label_overtime_2->setText(model.getOverdueCount("loans", "start_date",
                                                        "end_date", username));
    ui->stackedWidget->setCurrentIndex(0);

    //借阅显示与搜索
    model_book = new CustomSqlQueryModel(this);
    model_book->setQuery("SELECT * FROM books");
    proxyModel_book = new QSortFilterProxyModel(this);
    //还书显示与搜索
    model_loans = new StudentSqlModel(this);

    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        switch (ui->listWidget->row(item)) {
            case 0:
                ui->stackedWidget->setCurrentIndex(0);
                break;
            case 1:
                ui->stackedWidget->setCurrentIndex(2);
                proxyModel_book->setSourceModel(model_book);
                ui->tableView_book->setModel(proxyModel_book);
                ui->tableView_book->update();
                break;
            case 2:
                ui->stackedWidget->setCurrentIndex(3);
                model_loans->studentdata_loans("loans", "borrower_id", username);
                QSortFilterProxyModel *proxyModel_loans = new QSortFilterProxyModel(this);
                proxyModel_loans->setSourceModel(model_loans);
                ui->tableView_loans_book->setModel(proxyModel_loans);
                ui->tableView_loans_book->hideColumn(0);
                ui->tableView_loans_book->update();
                break;
        }});

    //修改密码界面
    connect(ui->pushButton_pwd_2, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);});

    //点击退出系统时，退出程序
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        if (ui->listWidget->row(item ) == 4) {
            return QApplication::exit();
        }
    });
    //点击退出登陆时，显示图书界面
    connect(ui->listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        if (ui->listWidget->row(item ) == 3) {
            Library_Login *library_login = new Library_Login;
            library_login->show();
            this->close();
        }
    });

    //借阅书籍
    connect(ui->pushButton_loans, &QPushButton::clicked, this, [=]() {
        on_loansButton_clicked();});

    //还书
    connect(ui->pushButton_return_loans, &QPushButton::clicked, this, [=]() {
        on_returnloansButton_clicked();});

}
//获取上一窗口传递的密码与用户
void Stu_main::handleUserLogin(QString &user_name, QString &pass_word) {
    this->username = user_name;
    this->password = pass_word;

}

//借书
void Stu_main::on_loansButton_clicked() {
    QModelIndexList selectedRows = ui->tableView_book->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要借阅的书籍");
        return;
    }

    QString bookId = selectedRows.first().sibling(selectedRows.first().row(), 2).data().toString();
    QString borrower_name = student_name;
    QString borrowDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString returnDate = QDateTime::currentDateTime().addDays(30).toString("yyyy-MM-dd");

    QSqlQuery query;
    bool isPrepared = query.prepare("INSERT INTO loans (isbn, borrower_id, start_date, end_date, borrower_name) "
                  "VALUES (:bookId, :borrowerId, :borrowDate, :returnDate, :borrower_name)");
    query.bindValue(":bookId", bookId);
    query.bindValue(":borrowerId", username);
    query.bindValue(":borrowDate", borrowDate);
    query.bindValue(":returnDate", returnDate);
    query.bindValue(":borrower_name", borrower_name);

    qDebug()<<bookId;
    qDebug()<<borrower_name;
    qDebug()<<borrowDate;
    qDebug()<<returnDate;
    qDebug()<< username;

    if (!isPrepared) {
        qDebug() << query.lastError().text();
        return;
    }
    if (query.exec()) {
        QMessageBox::information(this, "提示", "借书成功");
        qDebug() <<query.executedQuery();
        // 刷新数据模型
        model_loans->setQuery(model_loans->query().lastQuery());
    } else {
        QMessageBox::warning(this, "警告", "借书失败");
        qDebug() << query.lastError().text();
        qDebug() <<query.executedQuery();
    }
}

void Stu_main::on_returnloansButton_clicked() {
    QModelIndexList selectedRows = ui->tableView_loans_book->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要归还的书籍");
        return;
    }

    QSqlQuery query;
    int loanId = selectedRows.first().sibling(selectedRows.first().row(),0).data().toInt();
    query.prepare("DELETE FROM loans WHERE id = :loanId");
    query.bindValue(":loanId", loanId);

    if (query.exec()) {
        QMessageBox::information(this, "提示", "还书成功");

        // 刷新数据模型
        model_loans->studentdata_loans("loans", "borrower_id", username);
    } else {
        QMessageBox::warning(this, "警告", "还书失败");
    }

}

Stu_main::~Stu_main() {
    delete ui;
}
