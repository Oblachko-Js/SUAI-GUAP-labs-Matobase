#include "visitors.h"
#include <QCoreApplication>
#include <QApplication>

Visitors::Visitors(QObject *parent) : QObject(parent) {}

void Visitors::addVisitor(const QString &number, const QString &name, const QString &address, const QString &phone)
{
    // Добавляем нового посетителя
    QStringList visitorInfo = {number, name, address, phone};
    visitorData.append(visitorInfo);

    emit visitorsAdded();
}

void Visitors::saveVisitorsToFile()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/visitors.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QSet<QString> uniqueRows; // Сет для хранения уникальных строк
        for (const QStringList &visitorInfo : visitorData) {
            QString rowData = visitorInfo.join(";"); // Преобразуем список в строку
            if (!uniqueRows.contains(rowData)) {
                uniqueRows.insert(rowData); // Добавляем строку в сет уникальных строк
                out << rowData << "\n"; // Записываем уникальную строку в файл
            }
        }
        file.close();
    }
}

void Visitors::loadVisitorsFromfile(QTableWidget *table)
{
    // Очищаем таблицу перед загрузкой новых данных
    table->clearContents();
    table->setRowCount(0);

    // Устанавливаем количество колонок в таблице
    int numColumns = 4; // Для четырех параметров
    table->setColumnCount(numColumns);

    // Устанавливаем заголовки колонок
    QStringList columnHeaders = {"Номер", "Имя", "Адрес", "Телефон"};
    table->setHorizontalHeaderLabels(columnHeaders);

    // Получаем путь к файлу
    QString filePath = QCoreApplication::applicationDirPath() + "/visitors.txt";

    // Открываем файл для чтения данных
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    // Сет для хранения уникальных строк
    QSet<QString> uniqueRows;
    QTextStream in(&file);

    // Читаем данные из файла и проверяем на уникальность
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        QString rowData = infoList.join(";"); // Склеиваем строки для уникальности
        uniqueRows.insert(rowData); // Добавляем строку в сет уникальных строк
    }

    file.close();

    // Загружаем уникальные строки в таблицу
    for (const QString &row : uniqueRows) {
        QStringList infoList = row.split(";");
        int tableRow = table->rowCount();
        table->insertRow(tableRow);
        for (int i = 0; i < infoList.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(infoList.at(i));
            table->setItem(tableRow, i, item);
        }
    }
}
