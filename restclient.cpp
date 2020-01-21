#include "restclient.h"

RestClient::RestClient(QObject* parent): QObject(parent)
{
    client = new QNetworkAccessManager();
}

RestClient::~RestClient()
{
    delete client;
}

QSharedPointer<QNetworkReply> RestClient::Get(const QString& url)
{
    QUrl qurl(url);
    QNetworkRequest req(qurl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "*/*");
    req.setAttribute(QNetworkRequest::HTTP2AllowedAttribute, QVariant(true));
    QNetworkReply* reply = client->get(req);
    QSharedPointer<QNetworkReply> ret(reply);
    return ret;
}
