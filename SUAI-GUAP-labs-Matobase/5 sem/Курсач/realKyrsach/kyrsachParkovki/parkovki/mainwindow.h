#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "parkingfactory.h"
#include "visitors.h"
#include "ticketmanager.h" // Включаем заголовок TicketManager

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool checkRecordExists(const QString &filePath, const QString &parkingId);
    bool checkParkingExists(const QString &parkingId);
    bool checkPersonnelExists(const QString &personnelId);
    bool checkVehicleExists(const QString &vehicleId);

private slots:
    void addParking();
    void deleteParking();
    void updateTable();
    void loadParkingsToTable();
    void addVisitors();
    void deleteVisitors();
    void updateVisitorsTable();
    void addTicket(); // Добавляем слот для кнопки выдачи билетов
    void deleteTicket();
    void updateTicketTable();
    void addVehicle();
    void addPersonnel();
    void deleteVehicle();
    void deletePersonnel();
    void updateVehicleTable();
    void updatePersonnelTable();

private:
    Ui::MainWindow *ui; // Интерфейс главного окна
    ParkingFactory *parkingFactory; // Фабрика парковок
    Visitors *visitorsFactory; // Фабрика посетителей
    TicketManager *ticketManager; // Менеджер билетов
};

#endif
