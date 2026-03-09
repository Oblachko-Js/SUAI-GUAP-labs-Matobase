#include "vehicle.h"

Vehicle::Vehicle(const QString &id, const QString &brand, const QString &model)
    : vehicleId(id), brand(brand), model(model) {}

QString Vehicle::getId() const {
    return vehicleId;
}

QString Vehicle::getBrand() const {
    return brand;
}

QString Vehicle::getModel() const {
    return model;
}
