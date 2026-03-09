#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vehicle.h"
#include "personnel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    parkingFactory = new ParkingFactory(this); // Создаем объект ParkingFactory
    visitorsFactory = new Visitors(this); // Создаем объект Visitors
    ticketManager = new TicketManager(this);

    connect(parkingFactory, &ParkingFactory::parkingAdded, this, &MainWindow::updateTable); // Связываем сигнал о добавлении парковки с обновлением таблицы
    connect(visitorsFactory, &Visitors::visitorsAdded, this, &MainWindow::updateVisitorsTable); // Связываем сигнал о добавлении посетителя с обновлением таблицы

    // Обновляем таблицы при старте программы
    updateTable();
    updateVisitorsTable();
    updateTicketTable();
    updateVehicleTable();
    updatePersonnelTable();

    connect(ui->pushButton_add_parking, &QPushButton::clicked, this, &MainWindow::addParking);
    connect(ui->pushButton_delete_parking, &QPushButton::clicked, this, &MainWindow::deleteParking);
    connect(ui->pushButton_add_visitors, &QPushButton::clicked, this, &MainWindow::addVisitors); // Связываем кнопку добавления посетителя с соответствующим слотом
    connect(ui->pushButton_delete_visitors, &QPushButton::clicked, this, &MainWindow::deleteVisitors);
    connect(ui->pushButton_add_ticket, &QPushButton::clicked, this, &MainWindow::addTicket);
    connect(ui->pushButton_delete_ticket, &QPushButton::clicked, this, &MainWindow::deleteTicket);
    connect(ui->pushButton_add_vehicle, &QPushButton::clicked, this, &MainWindow::addVehicle);
    connect(ui->pushButton_delete_vehicle, &QPushButton::clicked, this, &MainWindow::deleteVehicle);
    connect(ui->pushButton_add_personnel, &QPushButton::clicked, this, &MainWindow::addPersonnel);
    connect(ui->pushButton_delete_personnel, &QPushButton::clicked, this, &MainWindow::deletePersonnel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addParking()
{
    QString id = ui->lineEdit_id_parking->text();
    QString gps = ui->lineEdit_gps->text();
    QString size = ui->lineEdit_size->text();
    QString type = ui->lineEdit_type->text();
    QString cost = ui->lineEdit_cost->text();

    // Проверяем наличие парковки с таким ID
    QString filePath = QCoreApplication::applicationDirPath() + "/parkings.txt";
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList infoList = line.split(";");
            if (!infoList.isEmpty() && infoList[0] == id) {
                QMessageBox::warning(this, "Ошибка", "Парковка с таким ID уже существует!");
                file.close();
                return; // Прекращаем выполнение функции, если ID уже существует
            }
        }
        file.close();
    } else {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    // Открываем файл для записи данных
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << id << ";" << gps << ";" << size << ";" << type << ";" << cost << ";Имеется в наличии\n";
        file.close();

        qDebug() << "Данные сохранены в файл:" << filePath;

        // Очищаем таблицу перед загрузкой новых данных
        ui->tableParking->clearContents();
        ui->tableParking->setRowCount(0);

        // Получаем данные о парковках из файла и загружаем их в таблицу
        loadParkingsToTable();

        qDebug() << "Добавлена новая парковка:";
        qDebug() << "ID:" << id << "GPS:" << gps << "Размер:" << size << "Тип:" << type << "Оплата:" << cost;
    } else {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }
}

void MainWindow::deleteParking()
{
    QString id = ui->lineEdit_id_parking->text();

    // Открываем файл для чтения данных
    QString filePath = QCoreApplication::applicationDirPath() + "/parkings.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream in(&file);
    QString updatedData; // Создаем строку для хранения обновленных данных

    // Перебираем строки файла
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == id) {
            // Проверяем статус парковки
            if (infoList.last().trimmed() == "Занято") {
                QMessageBox::warning(this, "Ошибка", "Невозможно удалить занятую парковку");
                file.close();
                return;
            }
        } else {
            // Добавляем строку в обновленные данные
            updatedData += line + "\n";
        }
    }

    file.close();

    // Открываем файл для записи данных
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }

    QTextStream out(&file);

    // Перезаписываем файл с учетом изменений
    out << updatedData;

    file.close();

    // Удаляем парковку из таблицы
    for (int row = 0; row < ui->tableParking->rowCount(); ++row) {
        QTableWidgetItem *item = ui->tableParking->item(row, 0);
        if (item && item->text() == id) {
            ui->tableParking->removeRow(row);
            qDebug() << "Парковка успешно удалена";
            break;
        }
    }
}

void MainWindow::updateTable()
{
    loadParkingsToTable(); // Перезагружаем таблицу после добавления новой парковки
}

void MainWindow::loadParkingsToTable()
{
    // Очищаем таблицу перед загрузкой новых данных
    ui->tableParking->clearContents();
    ui->tableParking->setRowCount(0);

    // Устанавливаем количество колонок в таблице
    int numColumns = 6; // Для шести параметров
    ui->tableParking->setColumnCount(numColumns);

    // Устанавливаем заголовки колонок
    QStringList columnHeaders = {"ID", "Местоположение", "Размер", "Тип", "Оплата", "Наличие"};
    ui->tableParking->setHorizontalHeaderLabels(columnHeaders);

    // Получаем путь к файлу
    QString filePath = QCoreApplication::applicationDirPath() + "/parkings.txt";

    // Открываем файл для чтения данных
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    // Сет для хранения уникальных строк
    QSet<QString> uniqueRows;
    QTextStream in(&file);

    // Проходим по файлу и добавляем уникальные строки в таблицу и сет
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        QString rowData = infoList.join(";"); // Склеиваем строки, чтобы проверять их на уникальность
        if (!uniqueRows.contains(rowData)) {
            uniqueRows.insert(rowData); // Добавляем строку в сет уникальных строк
            int row = ui->tableParking->rowCount();
            ui->tableParking->insertRow(row);
            for (int i = 0; i < infoList.size(); ++i) {
                QTableWidgetItem *item = new QTableWidgetItem(infoList.at(i));
                ui->tableParking->setItem(row, i, item);
            }
        }
    }

    file.close();

    // Перезаписываем файл, используя уникальные строки
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }

    QTextStream out(&file);
    for (const QString &row : uniqueRows) {
        out << row << "\n"; // Пишем строку в файл
    }

    file.close();
}

void MainWindow::addVisitors()
{
    QString number = ui->lineEdit_visitors_number->text();
    QString name = ui->lineEdit_visitors_name->text();
    QString address = ui->lineEdit_visitors_adress->text();
    QString phone = ui->lineEdit_visitors_phone->text();

    visitorsFactory->addVisitor(number, name, address, phone);
    visitorsFactory->saveVisitorsToFile(); // Сохраняем посетителей в файл
    visitorsFactory->loadVisitorsFromfile(ui->tableVisitors);
}

void MainWindow::deleteVisitors()
{
    QString number = ui->lineEdit_visitors_number->text();

    // Открываем файл с билетами для чтения
    QString ticketFilePath = QCoreApplication::applicationDirPath() + "/ticket.txt";
    QFile ticketFile(ticketFilePath);
    if (!ticketFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла с билетами для чтения";
        return;
    }

    QTextStream ticketIn(&ticketFile);

    // Проверяем, есть ли билеты на данного посетителя
    bool hasTickets = false;
    while (!ticketIn.atEnd()) {
        QString line = ticketIn.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.at(1) == number) {
            hasTickets = true;
            break;
        }
    }

    ticketFile.close();

    // Если есть билеты на посетителя, выводим сообщение об ошибке и завершаем функцию
    if (hasTickets) {
        QMessageBox::warning(this, "Ошибка", "Невозможно удалить посетителя, на которого есть билеты");
        return;
    }

    // Создаем множество для хранения уникальных строк данных
    QSet<QString> uniqueRows;

    // Открываем файл для чтения данных о посетителях
    QString filePath = QCoreApplication::applicationDirPath() + "/visitors.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream in(&file);

    // Заполняем множество уникальных строк данными из файла, исключая строки с данным номером посетителя
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        if (infoList.isEmpty() || infoList.at(0) != number) {
            uniqueRows.insert(line);
        }
    }

    file.close();

    // Открываем файл для записи данных
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }

    QTextStream out(&file);

    // Перезаписываем файл с учетом изменений
    foreach (const QString &row, uniqueRows) {
        out << row << "\n";
    }

    file.close();

    // Удаляем посетителя из таблицы
    for (int row = 0; row < ui->tableVisitors->rowCount(); ++row) {
        QTableWidgetItem *item = ui->tableVisitors->item(row, 0);
        if (item && item->text() == number) {
            ui->tableVisitors->removeRow(row);
            qDebug() << "Посетитель успешно удален";
            break;
        }
    }
}

void MainWindow::updateVisitorsTable()
{
    visitorsFactory->loadVisitorsFromfile(ui->tableVisitors); // Загружаем посетителей из файла в таблицу
}

void MainWindow::addTicket()
{
    QString parkingId = ui->lineEdit_parking_number->text();
    QString visitorNumber = ui->lineEdit_visitors_number_t->text();
    QString date = ui->lineEdit_date->text();

    // Добавляем билет
    ticketManager->addTicket(parkingId, visitorNumber, date, ui->tableTicket);

    // Проверка на наличие записей о транспортном средстве
    QString vehicleFilePath = QCoreApplication::applicationDirPath() + "/vehicles.txt";
    bool vehicleIdentified = checkRecordExists(vehicleFilePath, parkingId);

    // Проверка на наличие записей о персонале
    QString personnelFilePath = QCoreApplication::applicationDirPath() + "/personnel.txt";
    bool personnelAvailable = checkRecordExists(personnelFilePath, parkingId);

    // Обновляем последний добавленный билет
    int lastRow = ui->tableTicket->rowCount() - 1;
    ui->tableTicket->setItem(lastRow, 3, new QTableWidgetItem(vehicleIdentified ? "Идентифицировано" : "Не идентифицировано"));
    ui->tableTicket->setItem(lastRow, 4, new QTableWidgetItem(personnelAvailable ? "Есть в наличии" : "Нет в наличии"));

    // Обновляем таблицу
    updateTicketTable();
    updateTable();
}

void MainWindow::deleteTicket()
{
    // Получаем ID парковки и номер посетителя, введенные пользователем
    QString parkingId = ui->lineEdit_parking_number->text();
    QString visitorNumber = ui->lineEdit_visitors_number_t->text();

    // Проверяем наличие транспортного средства по этому билету
    if (checkRecordExists(QCoreApplication::applicationDirPath() + "/vehicles.txt", parkingId)) {
        QMessageBox::warning(this, "Ошибка", "Нельзя удалить билет, пока на него инициализировано транспортное средство!");
        return;
    }

    // Проверяем наличие персонала по этому билету
    if (checkRecordExists(QCoreApplication::applicationDirPath() + "/personnel.txt", parkingId)) {
        QMessageBox::warning(this, "Ошибка", "Нельзя удалить билет, пока на него инициализирован персонал!");
        return;
    }

    // Открываем файл с билетами для чтения и записи
    QString filePath = QCoreApplication::applicationDirPath() + "/ticket.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    // Считываем билеты из файла и удаляем выбранный билет
    QTextStream in(&file);
    QStringList ticketLines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        if (infoList.size() >= 2 && infoList[0] == parkingId && infoList[1] == visitorNumber) {
            // Пропускаем удаление выбранного билета
            continue;
        }
        ticketLines.append(line);
    }
    file.resize(0); // Очищаем содержимое файла
    QTextStream out(&file);
    for (const QString &line : ticketLines) {
        out << line << "\n"; // Записываем оставшиеся билеты обратно в файл
    }
    file.close();

    // Обновляем таблицу билетов
    updateTicketTable();

    // Изменяем статус парковки, если билет возвращается
    QFile parkingFile(QCoreApplication::applicationDirPath() + "/parkings.txt");
    if (!parkingFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream parkingIn(&parkingFile);
    QString updatedParkingData;
    while (!parkingIn.atEnd()) {
        QString line = parkingIn.readLine();
        QStringList infoList = line.split(";");
        if (infoList.size() >= 1 && infoList[0] == parkingId && infoList.last().trimmed() == "Занято") {
            // Парковка становится доступной после возврата билета
            infoList.last() = "Имеется в наличии";
            line = infoList.join(";");
        }
        updatedParkingData += line + "\n";
    }
    parkingFile.resize(0); // Очищаем содержимое файла
    QTextStream parkingOut(&parkingFile);
    parkingOut << updatedParkingData; // Записываем обновленные данные о парковках обратно в файл
    parkingFile.close();

    updateTicketTable();
    updateTable();
}

// Вспомогательная функция для проверки существования записи в файле
bool MainWindow::checkRecordExists(const QString &filePath, const QString &parkingId)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == parkingId) {
            file.close();
            return true; // Запись найдена
        }
    }
    file.close();
    return false; // Запись не найдена
}

void MainWindow::updateTicketTable()
{
    // Очищаем таблицу перед загрузкой новых данных
    ui->tableTicket->clearContents();
    ui->tableTicket->setRowCount(0);

    // Устанавливаем количество колонок в таблице
    int numColumns = 5; // Обновлено на 5 для новых столбцов
    ui->tableTicket->setColumnCount(numColumns);

    // Устанавливаем заголовки колонок
    QStringList columnHeaders = {"ID парковки", "Номер посетителя", "Дата выдачи", "Транспортное средство", "Персонал"};
    ui->tableTicket->setHorizontalHeaderLabels(columnHeaders);

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
        int row = ui->tableTicket->rowCount();
        ui->tableTicket->insertRow(row);
        for (int i = 0; i < infoList.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(infoList.at(i));
            ui->tableTicket->setItem(row, i, item);
        }

        // Предполагаем, что последние два поля должны быть заполнены на основе каких-либо условий
        QString parkingId = infoList.at(0);
        bool vehicleIdentified = checkRecordExists(QCoreApplication::applicationDirPath() + "/vehicles.txt", parkingId);
        bool personnelAvailable = checkRecordExists(QCoreApplication::applicationDirPath() + "/personnel.txt", parkingId);

        ui->tableTicket->setItem(row, 3, new QTableWidgetItem(vehicleIdentified ? "Идентифицировано" : "Не идентифицировано"));
        ui->tableTicket->setItem(row, 4, new QTableWidgetItem(personnelAvailable ? "Есть персонал" : "Нет персонала"));
    }

    file.close();
}

void MainWindow::addVehicle()
{
    QString vehicleId = ui->lineEdit_vehicle_id->text();
    QString brand = ui->lineEdit_vehicle_brand->text();
    QString model = ui->lineEdit_vehicle_model->text();

    // Проверяем, существует ли парковка с указанным ID
    if (!checkParkingExists(vehicleId)) {
        QMessageBox::warning(this, "Ошибка", "Парковка с указанным ID не найдена!");
        return;
    }

    // Проверяем, существует ли транспортное средство с таким ID
    if (checkVehicleExists(vehicleId)) {
        QMessageBox::warning(this, "Ошибка", "Транспортное средство с таким ID уже существует!");
        return;
    }

    // Создаем объект Vehicle
    Vehicle newVehicle(vehicleId, brand, model);

    QString filePath = QCoreApplication::applicationDirPath() + "/vehicles.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }

    QTextStream out(&file);
    out << newVehicle.getId() << ";" << newVehicle.getBrand() << ";" << newVehicle.getModel() << "\n";
    file.close();

    // Обновляем таблицу
    updateVehicleTable();
}

void MainWindow::addPersonnel()
{
    QString personnelId = ui->lineEdit_personnel_id->text();
    QString name = ui->lineEdit_personnel_name->text();
    QString position = ui->lineEdit_personnel_position->text();

    // Проверяем, существует ли парковка с указанным ID
    if (!checkParkingExists(personnelId)) {
        QMessageBox::warning(this, "Ошибка", "Парковка с указанным ID не найдена!");
        return;
    }

    // Проверяем, существует ли персонал с таким ID
    if (checkPersonnelExists(personnelId)) {
        QMessageBox::warning(this, "Ошибка", "Персонал с таким ID уже существует!");
        return;
    }

    // Создаем объект Personnel
    Personnel newPersonnel(personnelId, name, position);

    QString filePath = QCoreApplication::applicationDirPath() + "/personnel.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для записи";
        return;
    }

    QTextStream out(&file);
    out << newPersonnel.getId() << ";" << newPersonnel.getName() << ";" << newPersonnel.getPosition() << "\n";
    file.close();

    // Обновляем таблицу
    updatePersonnelTable();
}

// Вспомогательная функция для проверки существования парковки
bool MainWindow::checkParkingExists(const QString &parkingId)
{
    QString parkingFilePath = QCoreApplication::applicationDirPath() + "/parkings.txt";
    QFile parkingFile(parkingFilePath);
    if (!parkingFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return false;
    }

    QTextStream parkingIn(&parkingFile);
    while (!parkingIn.atEnd()) {
        QString line = parkingIn.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == parkingId) {
            parkingFile.close();
            return true; // Парковка найдена
        }
    }
    parkingFile.close();
    return false; // Парковка не найдена
}

// Вспомогательная функция для проверки существования транспортного средства
bool MainWindow::checkVehicleExists(const QString &vehicleId)
{
    QString vehicleFilePath = QCoreApplication::applicationDirPath() + "/vehicles.txt";
    QFile vehicleFile(vehicleFilePath);
    if (!vehicleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return false;
    }

    QTextStream vehicleIn(&vehicleFile);
    while (!vehicleIn.atEnd()) {
        QString line = vehicleIn.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == vehicleId) {
            vehicleFile.close();
            return true; // Транспортное средство найдено
        }
    }
    vehicleFile.close();
    return false; // Транспортное средство не найдено
}

// Вспомогательная функция для проверки существования персонала
bool MainWindow::checkPersonnelExists(const QString &personnelId)
{
    QString personnelFilePath = QCoreApplication::applicationDirPath() + "/personnel.txt";
    QFile personnelFile(personnelFilePath);
    if (!personnelFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return false;
    }

    QTextStream personnelIn(&personnelFile);
    while (!personnelIn.atEnd()) {
        QString line = personnelIn.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == personnelId) {
            personnelFile.close();
            return true; // Персонал найден
        }
    }
    personnelFile.close();
    return false; // Персонал не найден
}

void MainWindow::deleteVehicle()
{
    QString vehicleId = ui->lineEdit_vehicle_id->text();

    QString filePath = QCoreApplication::applicationDirPath() + "/vehicles.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения и записи";
        return;
    }

    QTextStream in(&file);
    QStringList vehicleLines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == vehicleId) {
            continue; // Пропускаем удаление выбранного транспортного средства
        }
        vehicleLines.append(line);
    }

    file.resize(0); // Очищаем содержимое файла
    QTextStream out(&file);
    for (const QString &line : vehicleLines) {
        out << line << "\n"; // Записываем оставшиеся транспортные средства обратно в файл
    }
    file.close();

    // Обновляем таблицу
    updateVehicleTable();
}

void MainWindow::deletePersonnel()
{
    QString personnelId = ui->lineEdit_personnel_id->text();

    QString filePath = QCoreApplication::applicationDirPath() + "/personnel.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения и записи";
        return;
    }

    QTextStream in(&file);
    QStringList personnelLines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        if (!infoList.isEmpty() && infoList.first() == personnelId) {
            continue; // Пропускаем удаление выбранного персонала
        }
        personnelLines.append(line);
    }

    file.resize(0); // Очищаем содержимое файла
    QTextStream out(&file);
    for (const QString &line : personnelLines) {
        out << line << "\n"; // Записываем оставшихся персонал обратно в файл
    }
    file.close();

    // Обновляем таблицу
    updatePersonnelTable();
}

void MainWindow::updateVehicleTable()
{
    ui->tableVehicles->clearContents();
    ui->tableVehicles->setRowCount(0);

    // Устанавливаем количество колонок в таблице
    int numColumns = 3; // Предполагаем, что у нас 3 колонки: ID, Марка, Модель
    ui->tableVehicles->setColumnCount(numColumns);

    // Устанавливаем заголовки колонок
    QStringList columnHeaders = {"ID парковки", "Марка", "Модель"};
    ui->tableVehicles->setHorizontalHeaderLabels(columnHeaders);

    QString filePath = QCoreApplication::applicationDirPath() + "/vehicles.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        int row = ui->tableVehicles->rowCount();
        ui->tableVehicles->insertRow(row);
        for (int i = 0; i < infoList.size(); ++i) {
            ui->tableVehicles->setItem(row, i, new QTableWidgetItem(infoList.at(i)));
        }
    }

    file.close();
    updateTicketTable();
}

void MainWindow::updatePersonnelTable()
{
    ui->tablePersonnel->clearContents();
    ui->tablePersonnel->setRowCount(0);

    // Устанавливаем количество колонок в таблице
    int numColumns = 3; // Предполагаем, что у нас 3 колонки: ID, Имя, Должность
    ui->tablePersonnel->setColumnCount(numColumns);

    // Устанавливаем заголовки колонок
    QStringList columnHeaders = {"ID парковки", "Имя", "Должность"};
    ui->tablePersonnel->setHorizontalHeaderLabels(columnHeaders);

    QString filePath = QCoreApplication::applicationDirPath() + "/personnel.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка при открытии файла для чтения";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList infoList = line.split(";");
        int row = ui->tablePersonnel->rowCount();
        ui->tablePersonnel->insertRow(row);
        for (int i = 0; i < infoList.size(); ++i) {
            ui->tablePersonnel->setItem(row, i, new QTableWidgetItem(infoList.at(i)));
        }
    }

    file.close();
    updateTicketTable();
}
