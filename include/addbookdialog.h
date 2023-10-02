//
// Created by 洛青宇 on 2023/4/18.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_ADDBOOKDIALOG_H
#define LIBRARY_MANAGEMENT_SYSTEM_ADDBOOKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class AddBookDialog; }
QT_END_NAMESPACE

class AddBookDialog : public QDialog {
Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);

    ~AddBookDialog() override;
private slots:
    void add_book();
private:
    Ui::AddBookDialog *ui;
    QString title;
    QString ISBN;
    QString author;
    QString publisher;
};


#endif //LIBRARY_MANAGEMENT_SYSTEM_ADDBOOKDIALOG_H
