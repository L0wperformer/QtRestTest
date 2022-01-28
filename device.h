#ifndef DEVICE_H
#define DEVICE_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "httprequestworker.h"

class device : public QObject {
  Q_OBJECT
public:
  explicit device(QObject *parent = nullptr);

public slots:
  void request(QString method, QString link, QJsonObject requestBody);

signals:
  void responseReceived(QString response);
private:
  QNetworkAccessManager *requestMethods = nullptr;
  void handleIncomingData(QNetworkReply *data);

};

#endif // DEVICE_H
