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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *main_window;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_parking;
    QPushButton *pushButton_visitors;
    QPushButton *pushButton_tickets;
    QPushButton *pushButton_ts;
    QPushButton *pushButton_staff;
    QWidget *parking;
    QTableWidget *tableWidgetParking;
    QPushButton *pushButtonAddParking;
    QLineEdit *lineEditParkingId;
    QLineEdit *lineEditParkingLocation;
    QPushButton *pushButtonDeleteParking;
    QWidget *visitors;
    QTableWidget *tableWidgetVisitors;
    QLineEdit *lineEditVisitorId;
    QLineEdit *lineEditVisitorName;
    QPushButton *pushButtonAddVisitor;
    QPushButton *pushButtonDeleteVisitor;
    QLineEdit *lineEditVisitorContact;
    QWidget *tickets;
    QWidget *ts;
    QWidget *staff;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 448);
        MainWindow->setMinimumSize(QSize(800, 448));
        MainWindow->setMaximumSize(QSize(800, 448));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 801, 441));
        main_window = new QWidget();
        main_window->setObjectName("main_window");
        groupBox = new QGroupBox(main_window);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(-10, 70, 811, 341));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        pushButton_parking = new QPushButton(groupBox);
        pushButton_parking->setObjectName("pushButton_parking");

        verticalLayout->addWidget(pushButton_parking);

        pushButton_visitors = new QPushButton(groupBox);
        pushButton_visitors->setObjectName("pushButton_visitors");

        verticalLayout->addWidget(pushButton_visitors);

        pushButton_tickets = new QPushButton(groupBox);
        pushButton_tickets->setObjectName("pushButton_tickets");

        verticalLayout->addWidget(pushButton_tickets);

        pushButton_ts = new QPushButton(groupBox);
        pushButton_ts->setObjectName("pushButton_ts");

        verticalLayout->addWidget(pushButton_ts);

        pushButton_staff = new QPushButton(groupBox);
        pushButton_staff->setObjectName("pushButton_staff");

        verticalLayout->addWidget(pushButton_staff);

        tabWidget->addTab(main_window, QString());
        parking = new QWidget();
        parking->setObjectName("parking");
        tableWidgetParking = new QTableWidget(parking);
        if (tableWidgetParking->columnCount() < 3)
            tableWidgetParking->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetParking->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetParking->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetParking->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetParking->setObjectName("tableWidgetParking");
        tableWidgetParking->setGeometry(QRect(0, 20, 401, 241));
        pushButtonAddParking = new QPushButton(parking);
        pushButtonAddParking->setObjectName("pushButtonAddParking");
        pushButtonAddParking->setGeometry(QRect(430, 110, 111, 32));
        lineEditParkingId = new QLineEdit(parking);
        lineEditParkingId->setObjectName("lineEditParkingId");
        lineEditParkingId->setGeometry(QRect(430, 60, 113, 21));
        lineEditParkingLocation = new QLineEdit(parking);
        lineEditParkingLocation->setObjectName("lineEditParkingLocation");
        lineEditParkingLocation->setGeometry(QRect(570, 60, 113, 21));
        pushButtonDeleteParking = new QPushButton(parking);
        pushButtonDeleteParking->setObjectName("pushButtonDeleteParking");
        pushButtonDeleteParking->setGeometry(QRect(570, 110, 111, 32));
        tabWidget->addTab(parking, QString());
        visitors = new QWidget();
        visitors->setObjectName("visitors");
        tableWidgetVisitors = new QTableWidget(visitors);
        if (tableWidgetVisitors->columnCount() < 3)
            tableWidgetVisitors->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetVisitors->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetVisitors->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetVisitors->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tableWidgetVisitors->setObjectName("tableWidgetVisitors");
        tableWidgetVisitors->setGeometry(QRect(0, 20, 401, 241));
        lineEditVisitorId = new QLineEdit(visitors);
        lineEditVisitorId->setObjectName("lineEditVisitorId");
        lineEditVisitorId->setGeometry(QRect(430, 30, 113, 21));
        lineEditVisitorName = new QLineEdit(visitors);
        lineEditVisitorName->setObjectName("lineEditVisitorName");
        lineEditVisitorName->setGeometry(QRect(570, 30, 113, 21));
        pushButtonAddVisitor = new QPushButton(visitors);
        pushButtonAddVisitor->setObjectName("pushButtonAddVisitor");
        pushButtonAddVisitor->setGeometry(QRect(430, 110, 111, 32));
        pushButtonDeleteVisitor = new QPushButton(visitors);
        pushButtonDeleteVisitor->setObjectName("pushButtonDeleteVisitor");
        pushButtonDeleteVisitor->setGeometry(QRect(570, 110, 111, 32));
        lineEditVisitorContact = new QLineEdit(visitors);
        lineEditVisitorContact->setObjectName("lineEditVisitorContact");
        lineEditVisitorContact->setGeometry(QRect(500, 60, 113, 21));
        tabWidget->addTab(visitors, QString());
        tickets = new QWidget();
        tickets->setObjectName("tickets");
        tabWidget->addTab(tickets, QString());
        ts = new QWidget();
        ts->setObjectName("ts");
        tabWidget->addTab(ts, QString());
        staff = new QWidget();
        staff->setObjectName("staff");
        tabWidget->addTab(staff, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270 (\320\237\320\260\320\275\321\207\320\265\320\275\320\272\320\276 \320\220\320\275\320\264\321\200\320\265\320\271 4236)", nullptr));
        groupBox->setTitle(QString());
        pushButton_parking->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270", nullptr));
        pushButton_visitors->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\265\321\202\320\270\321\202\320\265\320\273\320\270", nullptr));
        pushButton_tickets->setText(QCoreApplication::translate("MainWindow", "\320\242\320\260\320\273\320\276\320\275\321\213", nullptr));
        pushButton_ts->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\260\320\275\321\201\320\277\320\276\321\200\321\202\320\275\321\213\320\265 \321\201\321\200\320\265\320\264\321\201\321\202\320\262\320\260", nullptr));
        pushButton_staff->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\202\321\200\321\203\320\264\320\275\320\270\320\272\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(main_window), QCoreApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetParking->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetParking->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetParking->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\275\321\217\321\202\320\276\321\201\321\202\321\214", nullptr));
        pushButtonAddParking->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButtonDeleteParking->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(parking), QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetVisitors->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetVisitors->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetVisitors->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\321\202\320\260\320\272\321\202", nullptr));
        pushButtonAddVisitor->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButtonDeleteVisitor->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(visitors), QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\265\321\202\320\270\321\202\320\265\320\273\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tickets), QCoreApplication::translate("MainWindow", "\320\242\320\260\320\273\320\276\320\275\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ts), QCoreApplication::translate("MainWindow", "\320\242\320\241", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(staff), QCoreApplication::translate("MainWindow", "\320\241\320\276\321\202\321\200\321\203\320\264\320\275\320\270\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
