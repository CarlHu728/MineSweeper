#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <tuple>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int column = 9;
    int row = 9;
    int mineNum = 10;
    void GetValue(int &getColumn, int& getRow, int& getMineNum);

private slots:
    void on_InputColumn_valueChanged(int arg1);

    void on_InputRow_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
