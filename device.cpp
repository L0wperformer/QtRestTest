#include "device.h"
#include "httprequestworker.h"



device::device(QObject *parent) : QObject(parent) {
    requestMethods = new QNetworkAccessManager();
//Lambda for handling errors(in debug)
//    connect(requestMethods, &QNetworkAccessManager::finished,
//            this, [=](QNetworkReply *reply) {
//                if (reply->error()) {
//                    qDebug() << reply->errorString();
//                    return;
//                }

//                QString answer = reply->readAll();

//                qDebug() << answer;
//            }
//        );
    connect(requestMethods, &QNetworkAccessManager::finished,
            this, &device::handleIncomingData);


}

void device::request(QString method, QString link, QJsonObject requestBody) {
  qDebug() << "requesting... data:"<<requestBody;

QNetworkRequest request;
request.setUrl(QUrl(link));

if(method == "GET"){
requestMethods->get(request);
}


}

void device::handleIncomingData(QNetworkReply *data){
    if(data->error()) {
        qDebug()<< "ERROR: " << data->errorString();
        return;
    }

    QJsonDocument dataObject = QJsonDocument::fromJson(data->readAll());
    emit responseReceived(dataObject.toJson());




}



