#ifndef RECORDEDITFORM_H
#define RECORDEDITFORM_H

#include <QWidget>
//подключаем библиотеку, которая позволяет
//использовать виджет для работы с таблицей
//и связывает с полями модели
#include <QDataWidgetMapper>

namespace Ui {
class RecordEditForm;
}

class RecordEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecordEditForm(QWidget *parent = 0);
    ~RecordEditForm();

    //поле виджета
    QDataWidgetMapper* mapper;

    //функция, которая устанавливает модель для виджета
    void setModel(QAbstractItemModel* model);

private slots:
    void on_bnt_apply_clicked();

    void on_btn_close_clicked();

private:
    Ui::RecordEditForm *ui;
};

#endif // RECORDEDITFORM_H
