#ifndef DEVICE_H
#define DEVICE_H

#include <QDebug>
#include <QJsonObject>
#include <QObject>

class device : public QObject {
  Q_OBJECT
public:
  explicit device(QObject *parent = nullptr);

public slots:
  void request(QString method, QString link, QJsonObject requestBody);

signals:
};

#endif // DEVICE_H
