#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include "QHttp2Configuration"


class RestClient: public QObject
{
    Q_OBJECT
public:
    RestClient(QObject* parent=nullptr);
    ~RestClient();
    QSharedPointer<QNetworkReply> Get(const QString&);
private:
   QNetworkAccessManager* client;
};

#endif // RESTCLIENT_H
