#include "translate_widget.h"
#include "ui_translate_widget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>
#include <QDebug>

TranslateWidget::TranslateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TranslateWidget)
{
    ui->setupUi(this);

    setWindowTitle("Yandex Translate  1.2.1");
    setWindowIcon(QIcon(":/images/icon.png"));

    translate = new NetworkTranslate(this);
    connect(translate, SIGNAL(langs(QString)), SLOT(onSetListLangs(QString)));
    connect(translate, SIGNAL(translate(QString)), SLOT(onSetTranslate(QString)));
    connect(translate, SIGNAL(errorNetworkreply(QString)), SLOT(onError(QString)));

    translate->getLangs();
}

TranslateWidget::~TranslateWidget()
{
    delete ui;
}

void TranslateWidget::onSetListLangs(QString str_langs)
{
    qDebug()<<"str_langs:"<<str_langs;

    // Парсим JSON
    /* Пример ответа
    {
    "dirs": [
    "ru-en",
    "ru-pl",
    "ru-hu",
    ...
    ],
    "langs": {
    "ru": "русский",
    "en": "английский",
    "pl": "польский",
    ...
    }
    */
    QJsonDocument document = QJsonDocument::fromJson(str_langs.toUtf8());
    QJsonObject ob = document.object().value("langs").toObject();
    QStringList keys = ob.keys();
    qDebug()<<"keys: "<< keys<<"keys size:"<<keys.size();
    qDebug()<<"ob size:"<<ob.size();

    QString lang_name, lang_code;
    for(int i = 0; i < keys.size(); i++)
    {
        lang_name = ob.value(keys[i]).toString();
        lang_code = keys[i];

        qDebug()<<lang_code<<lang_name;

        ui->comboBox_lang_1->addItem(lang_name, QVariant(lang_code));
        if(lang_code == current_lang_1)
            ui->comboBox_lang_1->setCurrentIndex(i);
        ui->comboBox_lang_2->addItem(lang_name, QVariant(lang_code));
        if(lang_code == current_lang_2)
            ui->comboBox_lang_2->setCurrentIndex(i);
    }
    connect(ui->comboBox_lang_1, SIGNAL(currentIndexChanged(int)), SLOT(onLang_1_Changed(int)));
    connect(ui->comboBox_lang_2, SIGNAL(currentIndexChanged(int)), SLOT(onLang_2_Changed(int)));
    qDebug()<<current_lang_1<<"-"<<current_lang_2;
}

void TranslateWidget::onSetTranslate(QString str_translate)
{
    qDebug()<<"str_translate:"<<str_translate;

    // Парсим JSON
                /*
                Пример ответа
                {"code":200, "lang":"en-ru", "text":["текст"]}
                 */
    QJsonDocument document = QJsonDocument::fromJson(str_translate.toUtf8());

    int code = document.object().value("code").toInt();
    if(code != 200)
    {
        QString message = document.object().value("message").toString();
        QMessageBox::information(this, "", "Error translate:" + QString::number(code) + "\r\n" + message);
        return;
    }

    ui->textEdit_lang_2->clear();
    QJsonArray arr = document.object().value("text").toArray();
    for(int i = 0; i < arr.count(); i++)
    {
        ui->textEdit_lang_2->append(arr.at(i).toString());
        ui->textEdit_lang_2->append("\r\n\n");
    }
}

void TranslateWidget::onError(QString error_string)
{
    QMessageBox::information(this, tr("Error"), error_string);
}

void TranslateWidget::onLang_1_Changed(int)
{
    qDebug()<<"on_comboBox_lang_1_currentIndexChanged(int)";
    qDebug()<<current_lang_1<<"-"<<current_lang_2;

    current_lang_1 = ui->comboBox_lang_1->currentData().toString();

    qDebug()<<current_lang_1<<"-"<<current_lang_2;
}

void TranslateWidget::onLang_2_Changed(int)
{
    qDebug()<<current_lang_1<<"-"<<current_lang_2;

    current_lang_2 = ui->comboBox_lang_2->currentData().toString();

    qDebug()<<current_lang_1<<"-"<<current_lang_2;
}

void TranslateWidget::on_btn_clear_clicked()
{
    ui->textEdit_lang_1->clear();
    ui->textEdit_lang_2->clear();
}

void TranslateWidget::on_btn_rev_clicked()
{
    qDebug()<<current_lang_1<<"-"<<current_lang_2;

    int index_lang_1 = ui->comboBox_lang_1->currentIndex();
    int index_lang_2 = ui->comboBox_lang_2->currentIndex();

    ui->comboBox_lang_1->setCurrentIndex(index_lang_2);
    ui->comboBox_lang_2->setCurrentIndex(index_lang_1);
    current_lang_1 = ui->comboBox_lang_1->currentData().toString();
    current_lang_2 = ui->comboBox_lang_2->currentData().toString();

    qDebug()<<current_lang_1<<"-"<<current_lang_2;
}

void TranslateWidget::on_btn_translate_clicked()
{
    translate->getTranslate(ui->textEdit_lang_1->toPlainText(), current_lang_1 + "-" + current_lang_2);
}
