#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Создаем центральный виджет и вертикальный layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Инициализация виджетов
    label = new QLabel("Выберите опцию и настройте ползунок", this);
    comboBox = new QComboBox(this);
    lineEdit = new QLineEdit(this);
    slider = new QSlider(Qt::Horizontal, this);
    button = new QPushButton("Подтвердить", this);

    // Настройка QComboBox
    comboBox->addItem("Опция 1");
    comboBox->addItem("Опция 2");
    comboBox->addItem("Опция 3");

    // Настройка QSlider
    slider->setRange(0, 100);
    slider->setValue(50);

    // Настройка QLineEdit
    lineEdit->setPlaceholderText("Введите текст");

    // Добавляем виджеты в layout
    layout->addWidget(label);
    layout->addWidget(comboBox);
    layout->addWidget(lineEdit);
    layout->addWidget(slider);
    layout->addWidget(button);

    // Подключение сигналов и слотов
    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::onSliderValueChanged);
    connect(comboBox, &QComboBox::currentTextChanged, this, &MainWindow::onComboBoxChanged);

    // Устанавливаем размер окна
    setWindowTitle("ЛР7: Двумерный интерфейс Qt");
    resize(400, 300);
}

void MainWindow::onButtonClicked() {
    QString message = QString("Вы выбрали: %1\nТекст: %2\nЗначение ползунка: %3")
                          .arg(comboBox->currentText())
                          .arg(lineEdit->text())
                          .arg(slider->value());
    QMessageBox::information(this, "Результат", message);
}

void MainWindow::onSliderValueChanged(int value) {
    label->setText(QString("Значение ползунка: %1").arg(value));
}

void MainWindow::onComboBoxChanged(const QString &text) {
    lineEdit->setText(text);
}
