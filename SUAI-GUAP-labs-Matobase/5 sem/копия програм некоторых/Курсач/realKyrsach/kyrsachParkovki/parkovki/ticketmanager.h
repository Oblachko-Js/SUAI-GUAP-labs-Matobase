#ifndef TICKETMANAGER_H
#define TICKETMANAGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QTableWidget>

class TicketManager : public QObject
{
    Q_OBJECT
public:
    explicit TicketManager(QObject *parent = nullptr);

signals:

public slots:
    void addTicket(const QString &parkingId, const QString &visitorNumber, const QString &date, QTableWidget *table);
    void updateTicketTable(QTableWidget *table); // Обновление таблицы билетов

};

#endif
