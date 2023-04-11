/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *InputRow;
    QSpinBox *InputColumn;
    QSpinBox *InputMine;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(200, 180);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(20, 140, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        InputRow = new QSpinBox(Dialog);
        InputRow->setObjectName("InputRow");
        InputRow->setGeometry(QRect(90, 20, 81, 25));
        InputRow->setMinimum(9);
        InputRow->setMaximum(24);
        InputRow->setValue(9);
        InputColumn = new QSpinBox(Dialog);
        InputColumn->setObjectName("InputColumn");
        InputColumn->setGeometry(QRect(90, 60, 81, 25));
        InputColumn->setMinimum(9);
        InputColumn->setMaximum(30);
        InputColumn->setValue(9);
        InputMine = new QSpinBox(Dialog);
        InputMine->setObjectName("InputMine");
        InputMine->setGeometry(QRect(90, 100, 81, 25));
        InputMine->setMinimum(10);
        InputMine->setMaximum(80);
        InputMine->setValue(10);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 49, 25));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 60, 49, 25));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 100, 49, 25));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Row:", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Column:", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Mine:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
