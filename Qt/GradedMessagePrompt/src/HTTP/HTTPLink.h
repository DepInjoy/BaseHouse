#ifndef HTTPLINK_H
#define HTTPLINK_H
#include <QObject>
#include <QtNetwork>

class HTTPLink: public QObject
{
    Q_OBJECT
public:
    HTTPLink();
    ~HTTPLink();

    bool setUrl(const QUrl& url);
    void setHttpRequest(QHash<QString, QByteArray> headers);
    void sendMessage(QByteArray& content, bool cryDes = false);
private slots:
    void _handleNetworkReply(QNetworkReply* reply);
private:
    QNetworkAccessManager*      _networkAccessManager;
    QNetworkRequest             _networkRequest;
};

#endif // HTTPLINK_H
