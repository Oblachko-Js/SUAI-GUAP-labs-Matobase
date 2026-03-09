#include "ticketmanager.h"
#include <QCoreApplication>

TicketManager::TicketManager(QObject *parent) : QObject(parent)
{

}

void TicketManager::addTicket(const QString &parkingId, const QString &visitorNumber, const QString &date, QTableWidget *table)
{
    // Проверяем, существует ли парковка с указанным ID
    QString parkingFilePath = QCoreApplication::applicationDirPath() + "/parkings.txt";
    QFile parkingFile(parkingFilePath);
    if (!parkingFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream parkingIn(&parkingFile);
    bool parkingExists = false;
    while (!parkingIn.atEnd()) {
        QString line = parkingIn.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == parkingId) {
            parkingExists = true;
            break;
        }
    }
    parkingFile.close();

    if (!parkingExists) {
        QMessageBox::warning(nullptr, "Ошибка", "Парковка с указанным ID не найдена!");
        return;
    }

    // Проверяем, существует ли посетитель с указанным номером
    QString visitorsFilePath = QCoreApplication::applicationDirPath() + "/visitors.txt";
    QFile visitorsFile(visitorsFilePath);
    if (!visitorsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream visitorsIn(&visitorsFile);
    bool visitorExists = false;
    while (!visitorsIn.atEnd()) {
        QString line = visitorsIn.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == visitorNumber) {
            visitorExists = true;
            break;
        }
    }
    visitorsFile.close();

    if (!visitorExists) {
        QMessageBox::warning(nullptr, "Ошибка", "Посетитель с указанным номером не найден!");
        return;
    }

    // Создаем билет
    QString ticketFilePath = QCoreApplication::applicationDirPath() + "/ticket.txt";
    QFile ticketFile(ticketFilePath);
    if (!ticketFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }

    QTextStream out(&ticketFile);
    out << parkingId << ";" << visitorNumber << ";" << date << "\n";
    ticketFile.close();

    // Обновляем таблицу билетов
    updateTicketTable(table);

    // Изменяем статус парковки
    QFile parkingFileModify(parkingFilePath);
    if (!parkingFileModify.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QString updatedParkingData;
    QTextStream parkingInModify(&parkingFileModify);
    while (!parkingInModify.atEnd()) {
        QString line = parkingInModify.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == parkingId) {
            infoList.last() = "Занято";
            line = infoList.join(";");
        }
        updatedParkingData += line + "\n";
    }
    parkingFileModify.close();

    if (!parkingFileModify.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }

    QTextStream parkingOutModify(&parkingFileModify);
    parkingOutModify << updatedParkingData;
    parkingFileModify.close();
}

void TicketManager::updateTicketTable(QTableWidget *table)
{
    // Очищаем таблицу перед загрузкой новых данных
    table->clearContents();
    table->setRowCount(0);

    // Устанавливаем количество колонок в таблице
    int numColumns = 3; // Для трех параметров
    table->setColumnCount(numColumns);

    // Устанавливаем заголовки колонок
    QStringList columnHeaders = {"ID парковки", "Номер посетителя", "Дата выдачи"};
    table->setHorizontalHeaderLabels(columnHeaders);

    // Получаем путь к файлу
    QString filePath = QCoreApplication::applicationDirPath() + "/ticket.txt";

    // Открываем файл для чтения данных
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream in(&file);

    // Проходим по файлу и добавляем строки в таблицу
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        int row = table->rowCount();
        table->insertRow(row);
        for (int i = 0; i < infoList.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(infoList.at(i));
            table->setItem(row, i, item);
        }
    }

    file.close();
}
