//
// Created by 洛青宇 on 2023/4/18.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_EDITSTUDENTDIALOG_H
#define LIBRARY_MANAGEMENT_SYSTEM_EDITSTUDENTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "../database/studentSqlQueryModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class EditStudentDialog; }
QT_END_NAMESPACE

class EditStudentDialog : public QDialog {
Q_OBJECT

public:
    explicit EditStudentDialog(studentSqlQueryModel *model, const QModelIndex &index,QWidget *parent = nullptr);
    void update_student();
    ~EditStudentDialog() override;

private:
    Ui::EditStudentDialog *ui;
    QString m_student_number;
    QString student_number;
    QString name ;
    QString password ;
    QString email ;
    QString phone;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_EDITSTUDENTDIALOG_H
