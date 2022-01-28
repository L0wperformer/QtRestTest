#include "device.h"

device::device(QObject *parent) : QObject(parent) {}

void device::request(QString method, QString link, QJsonObject requestBody) {
  qDebug() << "Method: " << method << "Link: " << link << "Request:\n"
           << requestBody;
}
