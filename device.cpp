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
//Save url in settings
setUrl(URL);

//tell request the URI
request.setUrl(QUrl(URL));



//==========GET===========
if(method == "GET"){
requestMethods->get(request);
return;
}
//========================

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


//==========POST===========
if(method == "POST"){

requestMethods->post(request,requestBody);
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
//=========================================================
//=========================================================
//=========================================================




