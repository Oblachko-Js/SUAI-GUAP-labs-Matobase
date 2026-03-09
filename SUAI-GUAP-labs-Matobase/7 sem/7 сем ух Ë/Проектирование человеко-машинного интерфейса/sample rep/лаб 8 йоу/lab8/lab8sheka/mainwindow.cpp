#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Центральный виджет - сплиттер
    splitter = new QSplitter(this);
    setCentralWidget(splitter);

    // Левая часть: TabWidget с видами модель/представление
    tabWidget = new QTabWidget();
    splitter->addWidget(tabWidget);

    // Модель файловой системы
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::rootPath());

    // QListView
    listView = new QListView();
    listView->setModel(fileModel);
    listView->setRootIndex(fileModel->index(QDir::homePath()));
    tabWidget->addTab(listView, "QListView");

    // QTableView с простой моделью (для демонстрации)
    QStandardItemModel *tableModel = new QStandardItemModel(4, 3, this);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            QStandardItem *item = new QStandardItem(QString("Row %1, Col %2").arg(row).arg(col));
            tableModel->setItem(row, col, item);
        }
    }
    tableView = new QTableView();
    tableView->setModel(tableModel);
    tabWidget->addTab(tableView, "QTableView");

    // QTreeView
    treeView = new QTreeView();
    treeView->setModel(fileModel);
    treeView->setRootIndex(fileModel->index(QDir::homePath()));
    tabWidget->addTab(treeView, "QTreeView");

    // Правая часть: QCalendarWidget в QGroupBox с кнопками
    QWidget *rightWidget = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    calendarWidget = new QCalendarWidget();
    rightLayout->addWidget(calendarWidget);

    groupBox = new QGroupBox("Выбор опций");
    QVBoxLayout *groupLayout = new QVBoxLayout(groupBox);

    buttonGroup = new QButtonGroup(this);
    QRadioButton *radio1 = new QRadioButton("Опция 1");
    QRadioButton *radio2 = new QRadioButton("Опция 2");
    buttonGroup->addButton(radio1);
    buttonGroup->addButton(radio2);
    groupLayout->addWidget(radio1);
    groupLayout->addWidget(radio2);

    groupBox->setLayout(groupLayout);
    rightLayout->addWidget(groupBox);

    rightWidget->setLayout(rightLayout);
    splitter->addWidget(rightWidget);

    // Настройки размера
    splitter->setSizes({300, 300});
    resize(800, 600);
    setWindowTitle("ЛР8: Расширенные виджеты Qt");
}
