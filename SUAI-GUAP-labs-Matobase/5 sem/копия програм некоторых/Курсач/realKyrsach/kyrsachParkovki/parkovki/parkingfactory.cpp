#include "parkingfactory.h"
#include <QTableWidgetItem>

ParkingFactory::ParkingFactory(QObject *parent) : QObject(parent) {}

ParkingFactory::~ParkingFactory() {}

void ParkingFactory::addParking(const QString &id, const QString &gps, const QString &size, const QString &type, const QString &cost)
{
    // Формируем строку данных о парковке
    QString parkingInfo = id + ";" + gps + ";" + size + ";" + type + ";" + cost + ";Имеется в наличии";
    parkingData.append(parkingInfo);

    qDebug() << "Добавлена новая парковка:";
    qDebug() << "ID:" << id << "GPS:" << gps << "Размер:" << size << "Тип:" << type << "Оплата:" << cost;

    // Отправляем сигнал о добавлении новой парковки
    emit parkingAdded();
}

void ParkingFactory::loadParkingsToTable(QTableWidget *table)
{
    // Очищаем таблицу перед загрузкой новых данных
    table->clearContents();
    table->setRowCount(0);

    // Проходим по списку данных о парковках и добавляем их в таблицу
    for (const QString &parkingInfo : parkingData) {
        QStringList infoList = parkingInfo.split(";");
        int row = table->rowCount();
        table->insertRow(row);
        for (int i = 0; i < infoList.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(infoList.at(i));
            table->setItem(row, i, item);
        }
    }
}
