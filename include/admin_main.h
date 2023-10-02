//
// Created by 洛青宇 on 2023/4/11.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_ADMIN_MAIN_H
#define LIBRARY_MANAGEMENT_SYSTEM_ADMIN_MAIN_H

#include <QWidget>
#include <QString>
#include <QSortFilterProxyModel>
#include "addstudentdialog.h"
#include "addbookdialog.h"
#include "editbookdialog.h"
#include "../database/studentSqlQueryModel.h"
#include <QtWidgets/QTableView>
#include <QtSql/QSqlTableModel>


QT_BEGIN_NAMESPACE
namespace Ui { class Admin_main; }
QT_END_NAMESPACE

class Admin_main : public QWidget {
Q_OBJECT

enum class ObjectType{
    Student,
    Book
};

public:
    explicit Admin_main(QWidget *parent = nullptr);
    ~Admin_main() override;
public slots:
    void handleUserLogin(QString &username, QString &password);

private slots:
    void on_updatePassword_clicked();
    void on_searchButton_clicked(QString line);
    void on_addButton_clicked(ObjectType type, studentSqlQueryModel *model);
    void on_editButton_clicked(ObjectType type);
    void on_deleteButton_clicked(const QString &tableName, const QString &idColumnName, QTableView *tableView);

private:
    Ui::Admin_main *ui;
    studentSqlQueryModel *model_stu;
    studentSqlQueryModel *model_book;
    studentSqlQueryModel *model_loans;
    QSortFilterProxyModel *proxyModel;
    QSortFilterProxyModel *CurrentProxyModel;
    QString username;
    QString password;

};


#endif //LIBRARY_MANAGEMENT_SYSTEM_ADMIN_MAIN_H
