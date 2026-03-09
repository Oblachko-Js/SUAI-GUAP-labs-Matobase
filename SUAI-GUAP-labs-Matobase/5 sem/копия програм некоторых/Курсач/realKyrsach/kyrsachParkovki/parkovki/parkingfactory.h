#ifndef PARKINGFACTORY_H
#define PARKINGFACTORY_H

#include <QObject>
#include <QTableWidget>

class ParkingFactory : public QObject
{
    Q_OBJECT

public:
    explicit ParkingFactory(QObject *parent = nullptr);
    ~ParkingFactory();

    void addParking(const QString &id, const QString &gps, const QString &size, const QString &type, const QString &cost);
    void loadParkingsToTable(QTableWidget *table);

signals:
    void parkingAdded(); // Сигнал, отправляемый после добавления новой парковки

private:
    QStringList parkingData; // Данные о парковке для последующей загрузки в таблицу
};

#endif
