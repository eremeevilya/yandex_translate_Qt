#include "network_translate.h"
#include <QByteArray>
#include <QUrl>
#include <QDebug>

NetworkTranslate::NetworkTranslate(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

NetworkTranslate::~NetworkTranslate()
{
}

void NetworkTranslate::getTranslate(const QString &text, const QString &lang)
{
    if(!is_finished)
        return;
    is_finished = false;
    action = TRANSLATE;

    QUrl url = str_url_translate;

    QString str_post = "key=" + key + "&"
                       "text=" + text + "&"
                       "lang=" + lang;
    QByteArray options;
    options = str_post.toUtf8();

    m_request.setUrl(url);

    m_reply = m_manager->post(m_request, options);

    connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(m_reply, SIGNAL(readyRead()), this, SLOT(onRead()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onErrorNetworkReply(QNetworkReply::NetworkError)));
    //connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)), m_reply, SLOT(ignoreSslErrors(QList<QSslError>)));
    connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(onSSLErrors(QList<QSslError>)));
}

void NetworkTranslate::getLangs()
{
    if(!is_finished)
        return;
    is_finished = false;
    action = LANGS;

    QUrl url = str_url_list_lang;

    QString str_post = "key=" + key + "&"
                                      "ui=ru";
    QByteArray options;
    options = str_post.toUtf8();

    m_request.setUrl(url);

    m_reply = m_manager->post(m_request, options);

    connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(m_reply, SIGNAL(readyRead()), this, SLOT(onRead()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(onErrorNetworkReply(QNetworkReply::NetworkError)));
    //connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)), m_reply, SLOT(ignoreSslErrors(QList<QSslError>)));
    connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(onSSLErrors(QList<QSslError>)));
}

void NetworkTranslate::onRead()
{
    QByteArray byte_array = m_reply->readAll();

    QString str_result = QString(byte_array);

    switch(action)
    {
    case TRANSLATE:
        emit translate(str_result);
        break;
    case LANGS:
        emit langs(str_result);
        break;
    }
}

void NetworkTranslate::onFinished()
{
    qDebug()<<"finished";
    is_finished = true;

    m_reply->deleteLater();
}

void NetworkTranslate::onErrorNetworkReply(QNetworkReply::NetworkError)
{
    qDebug()<<"error network reply";

    emit errorNetworkreply(m_reply->errorString());
}

void NetworkTranslate::onSSLErrors(QList<QSslError> list_errors)
{
    qDebug()<<"SSL Errors";
    qDebug()<<list_errors;

    m_reply->ignoreSslErrors(list_errors);
    m_reply->ignoreSslErrors();
}
