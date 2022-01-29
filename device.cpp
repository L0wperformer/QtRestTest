#include "device.h"




device::device(QObject *parent) : QObject(parent) {
    requestMethods = new QNetworkAccessManager();

    connect(requestMethods, &QNetworkAccessManager::finished,
            this, &device::handleIncomingData);


}

void device::request(QString method, QString link, QByteArray requestBody) {
  qDebug() << "requesting... data:"<<requestBody;
//Save url in settings
setUrl(link);


QNetworkRequest request;
request.setUrl(QUrl(link));

if(method == "GET"){
requestMethods->get(request);
return;
}
//If method is other than GET, the request body will actually be used
QJsonParseError parseErr;
QJsonDocument requestData = QJsonDocument::fromJson(requestBody,&parseErr);
//===Check Request format===
if(requestData.isNull()) { //Parse error
    emit responseReceived("JSON PARSE ERROR:\n" + parseErr.errorString() );
    return;

}



if(method == "POST"){
//requestMethods->post(request,)
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



