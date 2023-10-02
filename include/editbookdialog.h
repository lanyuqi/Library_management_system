//
// Created by 洛青宇 on 2023/4/26.
//

#ifndef LIBRARY_MANAGEMENT_SYSTEM_EDITBOOKDIALOG_H
#define LIBRARY_MANAGEMENT_SYSTEM_EDITBOOKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "../database/studentSqlQueryModel.h"
#include "../database/StudentSqlModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class EditBookiDalog; }
QT_END_NAMESPACE

class EditBookiDalog : public QDialog {
Q_OBJECT

public:
    explicit EditBookiDalog(studentSqlQueryModel *model, const QModelIndex &index,QWidget *parent = nullptr);

    ~EditBookiDalog() override;
private slots:
    void update_book();
private:
    Ui::EditBookiDalog *ui;
    QString book_isbn;
    QString title;
    QString author;
    QString publisher;
    QString isbn;

};


#endif //LIBRARY_MANAGEMENT_SYSTEM_EDITBOOKDIALOG_H
