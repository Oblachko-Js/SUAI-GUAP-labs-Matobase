/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPlay;
    QPushButton *btnAddKeyframe;
    QPushButton *btnRender;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(600, 400));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnPlay = new QPushButton(centralwidget);
        btnPlay->setObjectName("btnPlay");

        horizontalLayout->addWidget(btnPlay);

        btnAddKeyframe = new QPushButton(centralwidget);
        btnAddKeyframe->setObjectName("btnAddKeyframe");

        horizontalLayout->addWidget(btnAddKeyframe);

        btnRender = new QPushButton(centralwidget);
        btnRender->setObjectName("btnRender");

        horizontalLayout->addWidget(btnRender);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\220\320\275\320\270\320\274\320\260\321\206\320\270\321\217 \320\270 \321\200\320\265\320\275\320\264\320\265\321\200\320\270\320\275\320\263 \320\262\320\270\320\264\320\265\320\276", nullptr));
        btnPlay->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\270\320\263\321\200\320\260\321\202\321\214 \320\260\320\275\320\270\320\274\320\260\321\206\320\270\321\216", nullptr));
        btnAddKeyframe->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\320\273\321\216\321\207\320\265\320\262\320\276\320\271 \320\272\320\260\320\264\321\200", nullptr));
        btnRender->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\275\320\264\320\265\321\200\320\270\321\202\321\214 \320\262\320\270\320\264\320\265\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
