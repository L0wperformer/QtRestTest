#ifndef DEVICE_H
#define DEVICE_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>


class device : public QObject {
  Q_OBJECT

public:
  explicit device(QObject *parent = nullptr);

public slots:
  void newRequest(QString method, QString link, QByteArray requestBody);

  QString getUrl(){
      return settings.value("Url").toString();
  }

signals:
  void responseReceived(QString response);
private:
  QNetworkAccessManager  *requestMethods= new QNetworkAccessManager(this);
  QNetworkRequest request;
  void handleIncomingData(QNetworkReply *data);

  QSettings settings;
  void setUrl(QString url){
      settings.setValue("Url",url);
  }
};

#endif // DEVICE_H
