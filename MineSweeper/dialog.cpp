#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    setParent(parent);
    ui->setupUi(this);
    this->setFixedSize(200, 180);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_InputColumn_valueChanged(int arg1)
{
    int col = ui->InputColumn->value();
    int row = ui->InputRow->value();
    ui->InputMine->setMaximum(col * row - 1);
}


void Dialog::on_InputRow_valueChanged(int arg1)
{
    int col = ui->InputColumn->value();
    int row = ui->InputRow->value();
    ui->InputMine->setMaximum(col * row - 1);
}

void Dialog::GetValue(int &getColumn, int& getRow, int& getMineNum) {
    getColumn = ui->InputColumn->value();
    getRow = ui->InputRow->value();
    getMineNum = ui->InputMine->value();
}


void Dialog::on_buttonBox_accepted()
{

}

