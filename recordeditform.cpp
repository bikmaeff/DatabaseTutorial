#include "recordeditform.h"
#include "ui_recordeditform.h"

RecordEditForm::RecordEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordEditForm)
{
    ui->setupUi(this);

    //создаем экземляр объекта виджета
    mapper = new QDataWidgetMapper(this);
    //связываем с моделью
    //mapper->setModel ();
    //связываем поля виджета и таблицы
    //mapper->addMapping (ui->cmb_product,1);
    //mapper->addMapping (ui->spb_company_id,2);
    //mapper->addMapping (ui->txt_details,3);

    //режим по умолчанию
    //mapper->setSubmitPolicy (QDataWidgetMapper::AutoSubmit);
    //режим ручной
    mapper->setSubmitPolicy (QDataWidgetMapper::ManualSubmit);
}

RecordEditForm::~RecordEditForm()
{
    delete ui;
}

void RecordEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel (model);
    mapper->addMapping (ui->cmb_product,1);
    mapper->addMapping (ui->spb_company_id,2);
    //текст без форматирования
    mapper->addMapping (ui->txt_details,3, "plainText");
}

void RecordEditForm::on_bnt_apply_clicked()
{
    mapper->submit ();
}

void RecordEditForm::on_btn_close_clicked()
{
    close ();
}
