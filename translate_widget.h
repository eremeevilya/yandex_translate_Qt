#ifndef TRANSLATE_WIDGET_H
#define TRANSLATE_WIDGET_H

#include <QWidget>
#include "network_translate.h"

namespace Ui {
class TranslateWidget;
}

class TranslateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TranslateWidget(QWidget *parent = 0);
    ~TranslateWidget();

private slots:
    void onSetListLangs(QString str_langs);

    void onSetTranslate(QString str_translate);

    void onError(QString error_string);

    void onLang_1_Changed(int);

    void onLang_2_Changed(int);

    void on_btn_clear_clicked();

    void on_btn_rev_clicked();

    void on_btn_translate_clicked();

private:
    Ui::TranslateWidget *ui;

    NetworkTranslate *translate;

    QString current_lang_1 = "en";
    QString current_lang_2 = "ru";
};

#endif // TRANSLATE_WIDGET_H
