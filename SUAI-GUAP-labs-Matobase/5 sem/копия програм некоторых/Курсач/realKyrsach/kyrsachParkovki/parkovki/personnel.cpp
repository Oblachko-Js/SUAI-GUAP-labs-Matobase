#include "personnel.h"

Personnel::Personnel(const QString &id, const QString &name, const QString &position)
    : personnelId(id), name(name), position(position) {}

QString Personnel::getId() const {
    return personnelId;
}

QString Personnel::getName() const {
    return name;
}

QString Personnel::getPosition() const {
    return position;
}
