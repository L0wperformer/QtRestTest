#include "device.h"
#include <QTemporaryFile>
#include <QBuffer>
#include <QFile>




device::device(QObject *parent) : QObject(parent) {

//===When request finishes it returns the reply, which we "catch" and handle in different function
    connect(requestMethods, &QNetworkAccessManager::finished,
            this, &device::handleIncomingData);
//===Tell the request that Json will be sent===
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

}
//=========================================================
//=====================Req/Res function====================
//=========================================================

void device::newRequest(QString method, QString URL, QByteArray requestBody) {
  qDebug() << "requesting... data:"<<requestBody;
//Save url in settings---request Setting is saved AFTER Parsing check
//See below
settings.setValue("Url",URL);



//tell request the URI
request.setUrl(QUrl(URL));



//==========GET===========
if(method == "GET"){
requestMethods->get(request);
return;
}
//========DELETE==========
if(method == "DELETE"){
requestMethods->deleteResource(request);
return;
}

//======JSON PARSING======
//This is only for checking if the Json is formatted
//correctly. The original array will actually be sent
//to avoid needless parsing
QJsonParseError parseErr;
QJsonDocument requestData = QJsonDocument::fromJson(requestBody,&parseErr);
//===Check Request format===
if(requestData.isNull()) { //Parse error
    emit responseReceived("JSON PARSE ERROR:\n" + parseErr.errorString() );
    return;
}

settings.setValue("request",requestBody);



//==========POST===========
if(method == "POST"){
requestMethods->post(request,requestBody);
return;
}
//==========PATCH============
if(method == "PATCH"){
    requestMethods->sendCustomRequest(request,"PATCH",requestBody);
}








}

void device::handleIncomingData(QNetworkReply *data){
    if(data->error()) {
        emit responseReceived("ERROR: " + data->errorString());
        return;
    }

    QJsonDocument dataObject = QJsonDocument::fromJson(data->readAll());

    emit responseReceived(dataObject.toJson());

}
//=========================================================
//=========================================================
//=========================================================




