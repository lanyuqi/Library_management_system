//
// Created by 洛青宇 on 2023/4/6.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_STU_MAIN_H
#define LIBRARY_MANAGEMENT_SYSTEM_STU_MAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "../database/StudentSqlModel.h"
#include "../database/CustomSqlQueryModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Stu_main; }
QT_END_NAMESPACE

class Stu_main : public QMainWindow {
Q_OBJECT

public:
    explicit Stu_main(const QString &username , const QString &password,
                      QWidget *parent = nullptr);
    void on_loansButton_clicked();
    void on_returnloansButton_clicked();
    ~Stu_main() override;
public slots:
    void handleUserLogin(QString &username, QString &password);

private:
    Ui::Stu_main *ui;
    QString username;
    QString student_name;
    QString password;
    CustomSqlQueryModel *model_book;
    StudentSqlModel *model_loans;
    QSortFilterProxyModel *proxyModel_book;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_STU_MAIN_H
