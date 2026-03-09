#ifndef VISITORS_H
#define VISITORS_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>

class Visitors : public QObject
{
    Q_OBJECT
public:
    explicit Visitors(QObject *parent = nullptr);

    void addVisitor(const QString &number, const QString &name, const QString &address, const QString &phone);
    void saveVisitorsToFile(); // Сохранение посетителей в файл
    void loadVisitorsFromfile(QTableWidget *table); // Загрузка посетителей из файла в таблицу

signals:
    void visitorsAdded(); // Сигнал, отправляемый после добавления нового посетителя

private:
    QList<QStringList> visitorData; // Данные о посетителях
};

#endif
