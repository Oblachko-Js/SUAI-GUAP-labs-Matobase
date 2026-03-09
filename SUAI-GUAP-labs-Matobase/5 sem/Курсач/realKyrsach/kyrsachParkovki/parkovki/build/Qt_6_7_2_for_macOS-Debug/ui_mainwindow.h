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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Menu;
    QTextBrowser *textBrowser;
    QWidget *Parking;
    QPushButton *pushButton_add_parking;
    QPushButton *pushButton_delete_parking;
    QLineEdit *lineEdit_gps;
    QLineEdit *lineEdit_type;
    QLineEdit *lineEdit_size;
    QLineEdit *lineEdit_id_parking;
    QLineEdit *lineEdit_cost;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_2;
    QTableWidget *tableParking;
    QWidget *Visitors;
    QLineEdit *lineEdit_visitors_number;
    QLineEdit *lineEdit_visitors_phone;
    QLineEdit *lineEdit_visitors_adress;
    QLineEdit *lineEdit_visitors_name;
    QPushButton *pushButton_add_visitors;
    QPushButton *pushButton_delete_visitors;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_11;
    QTableWidget *tableVisitors;
    QWidget *Ticket;
    QPushButton *pushButton_delete_ticket;
    QPushButton *pushButton_add_ticket;
    QLineEdit *lineEdit_parking_number;
    QLineEdit *lineEdit_visitors_number_t;
    QLineEdit *lineEdit_date;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QTableWidget *tableTicket;
    QWidget *TS;
    QLineEdit *lineEdit_vehicle_id;
    QLineEdit *lineEdit_vehicle_brand;
    QLineEdit *lineEdit_vehicle_model;
    QTableWidget *tableVehicles;
    QPushButton *pushButton_add_vehicle;
    QPushButton *pushButton_delete_vehicle;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QWidget *Staff;
    QLineEdit *lineEdit_personnel_id;
    QLineEdit *lineEdit_personnel_name;
    QLineEdit *lineEdit_personnel_position;
    QTableWidget *tablePersonnel;
    QPushButton *pushButton_add_personnel;
    QPushButton *pushButton_delete_personnel;
    QLabel *label_21;
    QLabel *label_20;
    QLabel *label_22;
    QLabel *label_23;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 516);
        MainWindow->setMinimumSize(QSize(800, 516));
        MainWindow->setMaximumSize(QSize(800, 516));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 10, 801, 531));
        Menu = new QWidget();
        Menu->setObjectName("Menu");
        Menu->setStyleSheet(QString::fromUtf8(""));
        textBrowser = new QTextBrowser(Menu);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(110, 50, 561, 291));
        tabWidget->addTab(Menu, QString());
        Parking = new QWidget();
        Parking->setObjectName("Parking");
        pushButton_add_parking = new QPushButton(Parking);
        pushButton_add_parking->setObjectName("pushButton_add_parking");
        pushButton_add_parking->setGeometry(QRect(220, 380, 100, 32));
        pushButton_delete_parking = new QPushButton(Parking);
        pushButton_delete_parking->setObjectName("pushButton_delete_parking");
        pushButton_delete_parking->setGeometry(QRect(470, 380, 100, 32));
        lineEdit_gps = new QLineEdit(Parking);
        lineEdit_gps->setObjectName("lineEdit_gps");
        lineEdit_gps->setGeometry(QRect(340, 340, 113, 21));
        lineEdit_type = new QLineEdit(Parking);
        lineEdit_type->setObjectName("lineEdit_type");
        lineEdit_type->setGeometry(QRect(210, 340, 113, 21));
        lineEdit_size = new QLineEdit(Parking);
        lineEdit_size->setObjectName("lineEdit_size");
        lineEdit_size->setGeometry(QRect(470, 340, 113, 21));
        lineEdit_id_parking = new QLineEdit(Parking);
        lineEdit_id_parking->setObjectName("lineEdit_id_parking");
        lineEdit_id_parking->setGeometry(QRect(80, 340, 113, 21));
        lineEdit_cost = new QLineEdit(Parking);
        lineEdit_cost->setObjectName("lineEdit_cost");
        lineEdit_cost->setGeometry(QRect(600, 340, 113, 21));
        label = new QLabel(Parking);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 320, 111, 16));
        label->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(Parking);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(340, 320, 111, 16));
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(Parking);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(470, 320, 111, 16));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(Parking);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(600, 320, 111, 16));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(Parking);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(210, 320, 111, 16));
        label_9->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Parking);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(340, 10, 111, 16));
        label_2->setAlignment(Qt::AlignCenter);
        tableParking = new QTableWidget(Parking);
        tableParking->setObjectName("tableParking");
        tableParking->setGeometry(QRect(0, 30, 791, 271));
        tabWidget->addTab(Parking, QString());
        Visitors = new QWidget();
        Visitors->setObjectName("Visitors");
        lineEdit_visitors_number = new QLineEdit(Visitors);
        lineEdit_visitors_number->setObjectName("lineEdit_visitors_number");
        lineEdit_visitors_number->setGeometry(QRect(140, 340, 113, 21));
        lineEdit_visitors_phone = new QLineEdit(Visitors);
        lineEdit_visitors_phone->setObjectName("lineEdit_visitors_phone");
        lineEdit_visitors_phone->setGeometry(QRect(530, 340, 113, 21));
        lineEdit_visitors_adress = new QLineEdit(Visitors);
        lineEdit_visitors_adress->setObjectName("lineEdit_visitors_adress");
        lineEdit_visitors_adress->setGeometry(QRect(400, 340, 113, 21));
        lineEdit_visitors_name = new QLineEdit(Visitors);
        lineEdit_visitors_name->setObjectName("lineEdit_visitors_name");
        lineEdit_visitors_name->setGeometry(QRect(270, 340, 113, 21));
        pushButton_add_visitors = new QPushButton(Visitors);
        pushButton_add_visitors->setObjectName("pushButton_add_visitors");
        pushButton_add_visitors->setGeometry(QRect(210, 380, 100, 32));
        pushButton_delete_visitors = new QPushButton(Visitors);
        pushButton_delete_visitors->setObjectName("pushButton_delete_visitors");
        pushButton_delete_visitors->setGeometry(QRect(470, 380, 100, 32));
        label_3 = new QLabel(Visitors);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(140, 320, 111, 16));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(Visitors);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(400, 320, 111, 16));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(Visitors);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(530, 320, 111, 16));
        label_5->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(Visitors);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(340, 10, 111, 16));
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(Visitors);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(270, 320, 111, 16));
        label_11->setAlignment(Qt::AlignCenter);
        tableVisitors = new QTableWidget(Visitors);
        tableVisitors->setObjectName("tableVisitors");
        tableVisitors->setGeometry(QRect(0, 30, 791, 271));
        tabWidget->addTab(Visitors, QString());
        Ticket = new QWidget();
        Ticket->setObjectName("Ticket");
        pushButton_delete_ticket = new QPushButton(Ticket);
        pushButton_delete_ticket->setObjectName("pushButton_delete_ticket");
        pushButton_delete_ticket->setGeometry(QRect(470, 380, 100, 32));
        pushButton_add_ticket = new QPushButton(Ticket);
        pushButton_add_ticket->setObjectName("pushButton_add_ticket");
        pushButton_add_ticket->setGeometry(QRect(210, 380, 100, 32));
        lineEdit_parking_number = new QLineEdit(Ticket);
        lineEdit_parking_number->setObjectName("lineEdit_parking_number");
        lineEdit_parking_number->setGeometry(QRect(200, 340, 113, 21));
        lineEdit_visitors_number_t = new QLineEdit(Ticket);
        lineEdit_visitors_number_t->setObjectName("lineEdit_visitors_number_t");
        lineEdit_visitors_number_t->setGeometry(QRect(330, 340, 121, 21));
        lineEdit_date = new QLineEdit(Ticket);
        lineEdit_date->setObjectName("lineEdit_date");
        lineEdit_date->setGeometry(QRect(470, 340, 113, 21));
        label_12 = new QLabel(Ticket);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(200, 320, 111, 16));
        label_12->setAlignment(Qt::AlignCenter);
        label_13 = new QLabel(Ticket);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(300, 10, 201, 20));
        label_13->setAlignment(Qt::AlignCenter);
        label_14 = new QLabel(Ticket);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(330, 320, 121, 16));
        label_14->setAlignment(Qt::AlignCenter);
        label_15 = new QLabel(Ticket);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(470, 320, 111, 16));
        label_15->setAlignment(Qt::AlignCenter);
        tableTicket = new QTableWidget(Ticket);
        tableTicket->setObjectName("tableTicket");
        tableTicket->setGeometry(QRect(0, 30, 791, 271));
        tabWidget->addTab(Ticket, QString());
        TS = new QWidget();
        TS->setObjectName("TS");
        lineEdit_vehicle_id = new QLineEdit(TS);
        lineEdit_vehicle_id->setObjectName("lineEdit_vehicle_id");
        lineEdit_vehicle_id->setGeometry(QRect(200, 340, 113, 21));
        lineEdit_vehicle_brand = new QLineEdit(TS);
        lineEdit_vehicle_brand->setObjectName("lineEdit_vehicle_brand");
        lineEdit_vehicle_brand->setGeometry(QRect(330, 340, 113, 21));
        lineEdit_vehicle_model = new QLineEdit(TS);
        lineEdit_vehicle_model->setObjectName("lineEdit_vehicle_model");
        lineEdit_vehicle_model->setGeometry(QRect(460, 340, 113, 21));
        tableVehicles = new QTableWidget(TS);
        tableVehicles->setObjectName("tableVehicles");
        tableVehicles->setGeometry(QRect(0, 30, 791, 271));
        pushButton_add_vehicle = new QPushButton(TS);
        pushButton_add_vehicle->setObjectName("pushButton_add_vehicle");
        pushButton_add_vehicle->setGeometry(QRect(210, 380, 100, 32));
        pushButton_delete_vehicle = new QPushButton(TS);
        pushButton_delete_vehicle->setObjectName("pushButton_delete_vehicle");
        pushButton_delete_vehicle->setGeometry(QRect(470, 380, 100, 32));
        label_16 = new QLabel(TS);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(300, 10, 201, 20));
        label_16->setAlignment(Qt::AlignCenter);
        label_17 = new QLabel(TS);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(200, 320, 111, 16));
        label_17->setAlignment(Qt::AlignCenter);
        label_18 = new QLabel(TS);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(330, 320, 111, 16));
        label_18->setAlignment(Qt::AlignCenter);
        label_19 = new QLabel(TS);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(460, 320, 111, 16));
        label_19->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(TS, QString());
        Staff = new QWidget();
        Staff->setObjectName("Staff");
        lineEdit_personnel_id = new QLineEdit(Staff);
        lineEdit_personnel_id->setObjectName("lineEdit_personnel_id");
        lineEdit_personnel_id->setGeometry(QRect(200, 340, 113, 21));
        lineEdit_personnel_name = new QLineEdit(Staff);
        lineEdit_personnel_name->setObjectName("lineEdit_personnel_name");
        lineEdit_personnel_name->setGeometry(QRect(330, 340, 113, 21));
        lineEdit_personnel_position = new QLineEdit(Staff);
        lineEdit_personnel_position->setObjectName("lineEdit_personnel_position");
        lineEdit_personnel_position->setGeometry(QRect(460, 340, 113, 21));
        tablePersonnel = new QTableWidget(Staff);
        tablePersonnel->setObjectName("tablePersonnel");
        tablePersonnel->setGeometry(QRect(0, 30, 791, 271));
        pushButton_add_personnel = new QPushButton(Staff);
        pushButton_add_personnel->setObjectName("pushButton_add_personnel");
        pushButton_add_personnel->setGeometry(QRect(210, 380, 100, 32));
        pushButton_delete_personnel = new QPushButton(Staff);
        pushButton_delete_personnel->setObjectName("pushButton_delete_personnel");
        pushButton_delete_personnel->setGeometry(QRect(470, 380, 100, 32));
        label_21 = new QLabel(Staff);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(300, 10, 201, 20));
        label_21->setAlignment(Qt::AlignCenter);
        label_20 = new QLabel(Staff);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(200, 320, 111, 16));
        label_20->setAlignment(Qt::AlignCenter);
        label_22 = new QLabel(Staff);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(330, 320, 111, 16));
        label_22->setAlignment(Qt::AlignCenter);
        label_23 = new QLabel(Staff);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(460, 320, 111, 16));
        label_23->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(Staff, QString());
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 37));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\275\321\207\320\265\320\275\320\272\320\276 \320\220\320\275\320\264\321\200\320\265\320\271 4236", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:24pt;\">\320\227\320\264\321\200\320\260\320\262\321\201\321\202\320\262\321\203\320\271\321\202\320\265. \320\237\321\200\320\276\321\210\321\203 \320\262\320\260\321\201, \320\262\321\213\320\261\320\265\321\200\320\260\320\271\321\202\320\265, \321\207\321\202\320\276 \320\262\321\213 \321\205\320\276\321\202\320\270\321\202\320\265 \321\201\320\264"
                        "\320\265\320\273\320\260\321\202\321\214 \320\262 \320\264\320\260\320\275\320\275\320\276\320\274 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\320\270. \320\241\320\262\320\265\321\200\321\205\321\203 \320\265\321\201\321\202\321\214 &quot;\320\262\320\270\320\264\320\266\320\265\321\202\321\213&quot; \321\201 \320\277\320\276\320\274\320\276\321\211\321\214\321\216 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \320\222\321\213 \320\274\320\276\320\266\320\265\321\202\320\265 \320\277\320\265\321\200\320\265\320\274\320\265\321\211\320\260\321\202\321\214\321\201\321\217 \320\262 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\320\270.</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Menu), QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
        pushButton_add_parking->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_delete_parking->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID \320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Parking), QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270", nullptr));
        pushButton_add_visitors->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_delete_visitors->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\265\321\202\320\270\321\202\320\265\320\273\320\270", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\244\320\230\320\236", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Visitors), QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\265\321\202\320\270\321\202\320\265\320\273\320\270", nullptr));
        pushButton_delete_ticket->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\267\320\262\321\200\320\260\321\202", nullptr));
        pushButton_add_ticket->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\264\320\260\321\202\321\214", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "ID \320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\264\320\260\321\207\320\260 \320\277\320\260\321\200\320\272\320\276\320\262\320\276\321\207\320\275\321\213\321\205 \320\274\320\265\321\201\321\202", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\277\320\276\321\201\320\265\321\202\320\270\321\202\320\265\320\273\321\217", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \320\262\321\213\320\264\320\260\321\207\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Ticket), QCoreApplication::translate("MainWindow", "\320\221\320\270\320\273\320\265\321\202\321\213", nullptr));
        pushButton_add_vehicle->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_delete_vehicle->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\264\320\260\321\207\320\260 \320\277\320\260\321\200\320\272\320\276\320\262\320\276\321\207\320\275\321\213\321\205 \320\274\320\265\321\201\321\202", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "ID \320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\200\320\272\320\260", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TS), QCoreApplication::translate("MainWindow", "\320\242\321\200\320\260\320\275\321\201\320\277\320\276\321\200\321\202\320\275\320\276\320\265 \321\201\321\200\320\265\320\264\321\201\321\202\320\262\320\276", nullptr));
        pushButton_add_personnel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_delete_personnel->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\264\320\260\321\207\320\260 \320\277\320\260\321\200\320\272\320\276\320\262\320\276\321\207\320\275\321\213\321\205 \320\274\320\265\321\201\321\202", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "ID \320\237\320\260\321\200\320\272\320\276\320\262\320\272\320\270", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\273\320\266\320\275\320\276\321\201\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Staff), QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\321\201\320\276\320\275\320\260\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
