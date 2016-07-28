#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSortFilterProxyModel>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //Create object drive PostgreSql
    db = QSqlDatabase::addDatabase ("QPSQL");
    //Определяем хост и устанавливаем имя базы данных
    db.setHostName ("127.0.0.1");
    db.setDatabaseName ("test");
    db.setUserName ("test_user");
    db.setPassword ("12345");
    //Setup connect of the db
    bool connectioncheck = db.open();
    if (connectioncheck)
    {
        qDebug() << "Connection to database established." << endl;

        model = new QSqlTableModel(this, db);
        //Stategy readly of the table
        //model->setEditStrategy (QSqlTableModel::OnManualSubmit); //Обновление по всей таблице
        //Указываем стратегию кэширования изменений
        model->setEditStrategy (QSqlTableModel::OnRowChange); //Обновление по строчке таблицы
        //Указываем имя таблицы, данные которой хотим изменить
        model->setTable ("products");
        //Загрузка актуальных данных из таблицы
        model->select ();

        //Назначаем модель объектам представлений
        //ui->tableView->setModel (model);
        //ui->comboBox->setModel (model);
        //ui->comboBox->setModelColumn (1);

        //Назначаем модель объектам представлений
        QSortFilterProxyModel * proxy = new QSortFilterProxyModel(this);
        proxy->setSourceModel (model);
        ui->tableView->setModel (model);

        //устанавливаем виджет как отдельное окно
        edit_form = new RecordEditForm();
        edit_form->setParent (this, Qt::Window);
        edit_form->setModel (model);


        //connect (model, SIGNAL(primeInsert(int,QSqlRecord&)), this, SLOT(onPrimeInsert(int,QSqlRecord&)));
    }
    else
    {
         qDebug() << "Error for database " << db.databaseName() << " :" << db.lastError().text() << endl;
         return;
    }
    //db.close();

//    {
//        qDebug() << db.lastError ().text ();
//    }
//    else
//    {
//        qDebug() << "Success!";
//    }

    /*
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("03111973");
    bool connectioncheck = db.open();
    if (connectioncheck == true){
        qDebug() << "Connection to database established." << endl;
    } else {
        qDebug() << "Error for database " << db.databaseName() << " :" << db.lastError().text() << endl;
    }
    db.close();
    */

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_btn_submit_clicked()
{
    //Применить все закэшированные данные
    model->submitAll ();

  /*
   * QSqlQuery query = QSqlQuery(db);
    if(!query.exec ("select * from products"))
    {
        qDebug() << db.lastError ().databaseText ();
        qDebug() << db.lastError ().driverText ();
        return;
    }
    else
    {
        while (query.next ())
        {
            qDebug() << query.record ();
        }
    }
    */
}

void MainWidget::on_btn_revert_clicked()
{
    //откатить изменения, которые пока находятся в кэше
    model->revertAll ();
}

void MainWidget::on_btn_select_table_clicked()
{
    model->select ();
}

void MainWidget::on_btn_add_clicked()
{
    qDebug() << "Inserting row" << model->insertRow (model->rowCount ());
}

void MainWidget::on_btn_delete_clicked()
{
    int selected_row = ui->tableView->currentIndex ().row();
    if(selected_row >= 0)
    {
        qDebug() << "Remove row" << model->removeRow (selected_row);
    }
    else
    {
        qDebug() << "No row selecting";
    }
}

/*
void MainWidget::onPrimeInsert(int row, QSqlRecord &record)
{
    QSqlQuery result = db.exec ();
    if(result.next ())
    {
        record.setValue ("ID", result.value (0));
        record.setGenerated ("ID", true);
    }
}
*/

void MainWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    edit_form->mapper->setCurrentModelIndex (index);
    edit_form->show ();
}
