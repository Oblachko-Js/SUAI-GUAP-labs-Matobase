#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();
    void onSliderValueChanged(int value);
    void onComboBoxChanged(const QString &text);

private:
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QSlider *slider;
    QLabel *label;
    QPushButton *button;
};

#endif // MAINWINDOW_H
