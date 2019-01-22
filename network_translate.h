#ifndef NETWORK_TRANSLATE_H
#define NETWORK_TRANSLATE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class NetworkTranslate : public QObject
{
    Q_OBJECT

private:
    const static int TRANSLATE = 1;
    const static int LANGS = 2;

public:
    NetworkTranslate(QObject *parent = 0);
    ~NetworkTranslate();

    void getTranslate(const QString &text, const QString &lang);

    void getLangs();

signals:
    void translate(QString);

    void langs(QString);

    void errorNetworkreply(QString error_string);

private slots:
    void onRead();

    void onFinished();

    void onErrorNetworkReply(QNetworkReply::NetworkError);

    void onSSLErrors(QList<QSslError> list_errors);

private:
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    QNetworkRequest m_request;

    int action = 0;

    bool is_finished = true;

    // URL для перевода
    const QString str_url_translate = "https://translate.yandex.net/api/v1.5/tr.json/translate";
    // URL для получения списка языков
    const QString str_url_list_lang = "https://translate.yandex.net/api/v1.5/tr.json/getLangs";
    // ключ яндкс API
    const QString key = "trnsl.1.1.20180806T132531Z.fdb0c73c6677e0ef.1b95e9437c7a549dd517db761dfd0a9ec58a5dc2";
};

#endif // NETWORK_TRANSLATE_H
