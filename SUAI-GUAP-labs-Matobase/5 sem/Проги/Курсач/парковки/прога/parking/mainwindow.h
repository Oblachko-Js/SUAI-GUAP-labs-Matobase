#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Добавьте объявление метода здесь
    void populateParkingTable();  // <- Добавьте это
    void populateVisitorTable();

private slots:
    void on_pushButton_parking_clicked();
    void on_pushButtonAddParking_clicked();
    void on_pushButtonDeleteParking_clicked();
    void on_pushButton_visitors_clicked();
    void on_pushButton_tickets_clicked();
    void on_pushButton_ts_clicked();
    void on_pushButton_staff_clicked();
    void on_pushButtonAddVisitor_clicked();
    void on_pushButtonDeleteVisitor_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
