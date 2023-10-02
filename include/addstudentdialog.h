//
// Created by 洛青宇 on 2023/4/18.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_ADDSTUDENTDIALOG_H
#define LIBRARY_MANAGEMENT_SYSTEM_ADDSTUDENTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>


QT_BEGIN_NAMESPACE
namespace Ui { class AddStudentDialog; }
QT_END_NAMESPACE

class AddStudentDialog : public QDialog {
Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr);
    ~AddStudentDialog() override;

private slots:
    void add_student();
private:
    Ui::AddStudentDialog *ui;
    QString student_number;
    QString name ;
    QString password ;
    QString email ;
    QString phone;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_ADDSTUDENTDIALOG_H
