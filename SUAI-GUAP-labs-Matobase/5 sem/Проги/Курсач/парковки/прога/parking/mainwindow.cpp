#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QString>
#include <iostream>
#include <QMessageBox>

// Классы сущностей

class Parking {
public:
    Parking(int id, const QString& location, const QString& isOccupied)
        : id(id), location(location), isOccupied(isOccupied) {}

    int getId() const { return id; }
    QString getLocation() const { return location; }
    QString getIsOccupied() const { return isOccupied; }

private:
    int id;
    QString location;
    QString isOccupied;
};

class Visitor {
public:
    Visitor(int id, const QString& name, const QString& contact)
        : id(id), name(name), contact(contact) {}

    int getId() const { return id; }
    QString getName() const { return name; }
    QString getContact() const { return contact; }

private:
    int id;
    QString name;
    QString contact;
};

class Ticket {
public:
    Ticket(int id, const QString& issueDate, double amount)
        : id(id), issueDate(issueDate), amount(amount) {}

    int getId() const { return id; }
    QString getIssueDate() const { return issueDate; }
    double getAmount() const { return amount; }

private:
    int id;
    QString issueDate;
    double amount;
};

class TS {
public:
    TS(int id, const QString& model, const QString& licensePlate)
        : id(id), model(model), licensePlate(licensePlate) {}

    int getId() const { return id; }
    QString getModel() const { return model; }
    QString getLicensePlate() const { return licensePlate; }

private:
    int id;
    QString model;
    QString licensePlate;
};

class Staff {
public:
    Staff(int id, const QString& name, const QString& position)
        : id(id), name(name), position(position) {}

    int getId() const { return id; }
    QString getName() const { return name; }
    QString getPosition() const { return position; }

private:
    int id;
    QString name;
    QString position;
};

// Пример паттерна "Наблюдатель"
class Observer {
public:
    virtual void update() = 0;
};

class ParkingObserver : public Observer {
public:
    void update() override {
        std::cout << "Parking updated!" << std::endl;
    }
};

class ParkingFactory {
public:
    static Parking createParking(int id, const QString& location, const QString& isOccupied) {
        // Здесь можно добавить дополнительную логику или проверки
        return Parking(id, location, isOccupied);
    }

    // Метод для создания парковки со значением по умолчанию
    static Parking createDefaultParking(int id, const QString& location) {
        return Parking(id, location, "Свободна");
    }
};

// Класс фабрики для создания посетителей
class VisitorFactory {
public:
    static Visitor createVisitor(int id, const QString& name, const QString& contact) {
        return Visitor(id, name, contact);
    }

    static std::vector<Visitor> createInitialVisitors() {
        return {
            createVisitor(1, "John Doe", "123-456-7890"),
            createVisitor(2, "Jane Smith", "987-654-3210"),
            createVisitor(3, "Alice Johnson", "555-123-4567")
        };
    }
};

// MainWindow реализация
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Установим начальную вкладку, если необходимо
    int mainMenuTabIndex = 0; // Индекс вкладки главного меню
    ui->tabWidget->setCurrentIndex(mainMenuTabIndex); // Главная вкладка по умолчанию

    // Заполняем таблицу парковок при инициализации
    populateParkingTable();
    populateVisitorTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_parking_clicked()
{
    // Переключаемся на вкладку parking при нажатии на кнопку
    int parkingTabIndex = 1; // Индекс вкладки parking
    ui->tabWidget->setCurrentIndex(parkingTabIndex);
}

void MainWindow::on_pushButton_visitors_clicked()
{
    // Переключаемся на вкладку visitors при нажатии на кнопку
    int visitorsTabIndex = 2; // Индекс вкладки visitors
    ui->tabWidget->setCurrentIndex(visitorsTabIndex);
}

void MainWindow::on_pushButton_tickets_clicked()
{
    // Переключаемся на вкладку tickets при нажатии на кнопку
    int ticketsTabIndex = 3; // Индекс вкладки tickets
    ui->tabWidget->setCurrentIndex(ticketsTabIndex);
}

void MainWindow::on_pushButton_ts_clicked()
{
    // Переключаемся на вкладку ts при нажатии на кнопку
    int tsTabIndex = 4; // Индекс вкладки ts
    ui->tabWidget->setCurrentIndex(tsTabIndex);
}

void MainWindow::on_pushButton_staff_clicked()
{
    // Переключаемся на вкладку staff при нажатии на кнопку
    int staffTabIndex = 5; // Индекс вкладки staff
    ui->tabWidget->setCurrentIndex(staffTabIndex);
}

// ПАРКОВКИ
//
//
//
//
//

void MainWindow::populateParkingTable() {
    // Очищаем таблицу
    ui->tableWidgetParking->setRowCount(0);

    // Добавим несколько парковочных мест
    std::vector<Parking> parkings = {
        ParkingFactory::createDefaultParking(1, "A1"),
        ParkingFactory::createDefaultParking(2, "B2"),
        ParkingFactory::createDefaultParking(3, "C3")
    };

    // Заполняем таблицу ID, Местоположение и Статус
    for (const Parking& p : parkings) {
        int row = ui->tableWidgetParking->rowCount();
        ui->tableWidgetParking->insertRow(row);

        ui->tableWidgetParking->setItem(row, 0, new QTableWidgetItem(QString::number(p.getId())));
        ui->tableWidgetParking->setItem(row, 1, new QTableWidgetItem(p.getLocation()));
        ui->tableWidgetParking->setItem(row, 2, new QTableWidgetItem(p.getIsOccupied()));
    }
}

void MainWindow::on_pushButtonAddParking_clicked() {
    // Получаем данные из формы
    int id = ui->lineEditParkingId->text().toInt();
    QString location = ui->lineEditParkingLocation->text();

    // Проверяем уникальность ID и местоположения
    bool isUnique = true;
    for (int row = 0; row < ui->tableWidgetParking->rowCount(); ++row) {
        int currentId = ui->tableWidgetParking->item(row, 0)->text().toInt();
        QString currentLocation = ui->tableWidgetParking->item(row, 1)->text();

        // Уникальность проверяем только по ID и местоположению
        if (currentId == id || currentLocation == location) {
            isUnique = false;
            break;
        }
    }

    // Если данные не уникальны, выводим сообщение об ошибке
    if (!isUnique) {
        QMessageBox::warning(this, "Ошибка", "Парковка с таким ID или местоположением уже существует!");
        return; // Прерываем выполнение, если данные не уникальны
    }

    // Если данные уникальны, создаем новое парковочное место через фабрику
    Parking newParking = ParkingFactory::createDefaultParking(id, location);

    // Добавляем новую запись в таблицу
    int row = ui->tableWidgetParking->rowCount();
    ui->tableWidgetParking->insertRow(row);
    ui->tableWidgetParking->setItem(row, 0, new QTableWidgetItem(QString::number(newParking.getId())));
    ui->tableWidgetParking->setItem(row, 1, new QTableWidgetItem(newParking.getLocation()));
    ui->tableWidgetParking->setItem(row, 2, new QTableWidgetItem(newParking.getIsOccupied()));
}


void MainWindow::on_pushButtonDeleteParking_clicked() {
    // Получаем введенные данные
    int id = ui->lineEditParkingId->text().toInt();
    QString location = ui->lineEditParkingLocation->text();

    // Поиск строки с введенными ID и местоположением
    for (int row = 0; row < ui->tableWidgetParking->rowCount(); ++row) {
        int currentId = ui->tableWidgetParking->item(row, 0)->text().toInt();
        QString currentLocation = ui->tableWidgetParking->item(row, 1)->text();

        // Проверка, если текущие ID и местоположение совпадают с введенными
        if (currentId == id && currentLocation == location) {
            // Удаление строки
            ui->tableWidgetParking->removeRow(row);
            break; // Прерываем цикл после удаления
        }
    }
}


// Функция для заполнения таблицы посетителей
void MainWindow::populateVisitorTable() {
    // Очищаем таблицу
    ui->tableWidgetVisitors->setRowCount(0);

    // Используем фабрику для создания начальных данных
    std::vector<Visitor> visitors = VisitorFactory::createInitialVisitors();

    // Заполняем таблицу
    for (const Visitor& v : visitors) {
        int row = ui->tableWidgetVisitors->rowCount();
        ui->tableWidgetVisitors->insertRow(row);

        ui->tableWidgetVisitors->setItem(row, 0, new QTableWidgetItem(QString::number(v.getId())));
        ui->tableWidgetVisitors->setItem(row, 1, new QTableWidgetItem(v.getName()));
        ui->tableWidgetVisitors->setItem(row, 2, new QTableWidgetItem(v.getContact()));
    }
}

// Функция для добавления посетителя
void MainWindow::on_pushButtonAddVisitor_clicked() {
    // Получаем данные из формы
    int id = ui->lineEditVisitorId->text().toInt();
    QString name = ui->lineEditVisitorName->text();
    QString contact = ui->lineEditVisitorContact->text();

    // Проверяем, есть ли уже такой посетитель по ID или контакту
    for (int row = 0; row < ui->tableWidgetVisitors->rowCount(); ++row) {
        int currentId = ui->tableWidgetVisitors->item(row, 0)->text().toInt();
        QString currentContact = ui->tableWidgetVisitors->item(row, 2)->text();

        if (currentId == id || currentContact == contact) {
            // Если ID или контакт уже существуют, выводим предупреждение
            QMessageBox::warning(this, "Ошибка", "Посетитель с таким ID или контактом уже существует!");
            return;
        }
    }

    // Используем фабрику для создания посетителя
    Visitor newVisitor = VisitorFactory::createVisitor(id, name, contact);

    // Добавляем новую запись в таблицу
    int row = ui->tableWidgetVisitors->rowCount();
    ui->tableWidgetVisitors->insertRow(row);
    ui->tableWidgetVisitors->setItem(row, 0, new QTableWidgetItem(QString::number(newVisitor.getId())));
    ui->tableWidgetVisitors->setItem(row, 1, new QTableWidgetItem(newVisitor.getName()));
    ui->tableWidgetVisitors->setItem(row, 2, new QTableWidgetItem(newVisitor.getContact()));
}

// Удаление посетителя
void MainWindow::on_pushButtonDeleteVisitor_clicked() {
    // Получаем введённые данные
    int id = ui->lineEditVisitorId->text().toInt();
    QString name = ui->lineEditVisitorName->text();
    QString contact = ui->lineEditVisitorContact->text();

    // Поиск строки с введёнными ID, именем и контактом
    for (int row = 0; row < ui->tableWidgetVisitors->rowCount(); ++row) {
        int currentId = ui->tableWidgetVisitors->item(row, 0)->text().toInt();
        QString currentName = ui->tableWidgetVisitors->item(row, 1)->text();
        QString currentContact = ui->tableWidgetVisitors->item(row, 2)->text();

        // Проверка, если текущие ID, имя и контакт совпадают с введёнными
        if (currentId == id && currentName == name && currentContact == contact) {
            // Удаление строки
            ui->tableWidgetVisitors->removeRow(row);
            break; // Прерываем цикл после удаления
        }
    }
}
