#include "HTTPLink.h"

HTTPLink::HTTPLink():
    _networkAccessManager(NULL)
{
    _networkAccessManager = new QNetworkAccessManager();
    //Signal named finished is emitted when network reply finished.
    //Connect this signal with slot.
    connect(_networkAccessManager, &QNetworkAccessManager::finished,
            this,   &HTTPLink::_handleNetworkReply);
}

HTTPLink::~HTTPLink()
{
    if(_networkAccessManager){
        delete _networkAccessManager;
        _networkAccessManager = NULL;
    }
}

bool HTTPLink::setUrl(const QUrl &url)
{
    if(!url.isValid()){
        qWarning() << "Invalid url " << url.toString();
        return false;
    }

    _networkRequest.setUrl(url);
    return true;
}

void HTTPLink::setHttpRequest(QHash<QString, QByteArray> headers)
{
#if 0
    if(!headers.size())
        return;
#endif
    _networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,
            QVariant("application/json"));
}

void HTTPLink::sendMessage(QByteArray& content, bool cryDes)
{
    Q_UNUSED(cryDes)
    _networkAccessManager->post(_networkRequest, content);
}
/*
 * @param reply     The reply that has just finished.
*/
void HTTPLink::_handleNetworkReply(QNetworkReply* reply)
{
    QByteArray bytes = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
    QJsonObject jsonObj = jsonDoc.object();
    switch (reply->error()) {
    // No error was found and handle them
    case QNetworkReply::NoError:
        if(jsonObj.contains("msg")){
            QString msgStr = jsonObj.value("msg").toString();
            qDebug() << "reply status message: " << msgStr;
        }else{
            qDebug() << "Get reply : " << QString::fromUtf8(bytes);
        }
        break;
    default:
        // Found HTTP error and show them.
        qWarning() << "Reply error message: "
                   << bytes << QString::fromUtf8(bytes)
                   << reply->errorString();
        break;
    }
    // It's responsibile to delete the reply object.
    reply->deleteLater();
}


