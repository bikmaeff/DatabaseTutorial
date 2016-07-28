#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
//Подключаем библиотеку для работы с СУБД
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "recordeditform.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_btn_submit_clicked();

    void on_btn_revert_clicked();

    void on_btn_select_table_clicked();

    void on_btn_add_clicked();

    void on_btn_delete_clicked();

    //void onPrimeInsert(int row, QSqlRecord &record);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWidget *ui;
    //Создаем поле базы данных
    QSqlDatabase db;
    //Create table model
    QSqlTableModel * model;
    //Создаем член класса виджета
    RecordEditForm * edit_form;
};

#endif // MAINWIDGET_H
