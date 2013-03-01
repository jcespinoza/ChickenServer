/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Fri 4. Dec 01:41:30 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include < QAction>
#include < QApplication>
#include < QButtonGroup>
#include < QHeaderView>
#include < QLabel>
#include < QMainWindow>
#include < QMenuBar>
#include < QPushButton>
#include < QSpinBox>
#include < QStatusBar>
#include < QTextEdit>
#include < QToolBar>
#include < QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnQuit;
    QLabel *label;
    QSpinBox *spinBox;
    QPushButton *btnReset;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(687, 472);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 70, 651, 291));
        textEdit->setReadOnly(true);
        btnStart = new QPushButton(centralWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(30, 20, 75, 23));
        btnStop = new QPushButton(centralWidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(110, 20, 75, 23));
        btnQuit = new QPushButton(centralWidget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));
        btnQuit->setGeometry(QRect(590, 370, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 20, 61, 16));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(280, 20, 42, 22));
        spinBox->setMaximum(9);
        spinBox->setValue(5);
        btnReset = new QPushButton(centralWidget);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setGeometry(QRect(370, 20, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 687, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0  ));
        btnStart->setText(QApplication::translate("MainWindow", "Start Server", 0  ));
        btnStop->setText(QApplication::translate("MainWindow", "Stop Server", 0  ));
        btnQuit->setText(QApplication::translate("MainWindow", "Salir", 0  ));
        label->setText(QApplication::translate("MainWindow", "Conexiones :", 0  ));
        btnReset->setText(QApplication::translate("MainWindow", "Reset Game", 0  ));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
