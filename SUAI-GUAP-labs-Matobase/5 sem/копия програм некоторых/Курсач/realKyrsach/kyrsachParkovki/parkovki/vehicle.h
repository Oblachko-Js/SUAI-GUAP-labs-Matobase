#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

class Vehicle {
public:
    Vehicle(const QString &id, const QString &brand, const QString &model);

    QString getId() const;
    QString getBrand() const;
    QString getModel() const;

private:
    QString vehicleId;
    QString brand;
    QString model;
};

#endif // VEHICLE_H
