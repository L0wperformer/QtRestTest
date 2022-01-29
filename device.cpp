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
request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/fhir+json"));
//==========GET===========
if(method == "GET"){
requestMethods->get(request);
return;
}
//========================

//======JSON PARSING======
//All methods beyond this point actually need the request body
QJsonParseError parseErr;
QJsonDocument requestData = QJsonDocument::fromJson(requestBody,&parseErr);
//===Check Request format===
if(requestData.isNull()) { //Parse error
    emit responseReceived("JSON PARSE ERROR:\n" + parseErr.errorString() );
    return;

}
//========================


//==========POST===========
if(method == "POST"){
requestMethods->post(request,requestData.toJson(QJsonDocument::Compact));
}

//=========================

//==========PUT============

//=========================





}

void device::handleIncomingData(QNetworkReply *data){
    if(data->error()) {
        qDebug()<< "ERROR: " << data->errorString();
        return;
    }

    QJsonDocument dataObject = QJsonDocument::fromJson(data->readAll());
    emit responseReceived(dataObject.toJson());




}



