#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <QString>

class Personnel {
public:
    Personnel(const QString &id, const QString &name, const QString &position);

    QString getId() const;
    QString getName() const;
    QString getPosition() const;

private:
    QString personnelId;
    QString name;
    QString position;
};

#endif // PERSONNEL_H
