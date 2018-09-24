#include <QtWidgets/QApplication>
#include <QDesktopWidget>
#include <QStatusBar>
#include <QDebug>
#include "Bubble.h"

int Bubble::totalHeight = 0;

Bubble::Bubble(QWidget *parent)
    : QWidget(parent)
{
    for(int i = 0;i < sizeof(_hideDialogTimer)/sizeof(_hideDialogTimer[0]);i++){
        _hideDialogTimer[i] = NULL;
    }
}

Bubble::~Bubble()
{
    for(int i = 0; i < maxMessageNum;i++){
        if(_hideDialogTimer[i]){
            delete _hideDialogTimer[i];
        }
    }

    for(int i = 0;i < _messageList.count();i++){
        if(_messageList.at(i)){
            delete _messageList.at(i);
        }
    }
}

void Bubble::showInfo(QString message)
{
    if(_messageList.count() >= maxMessageNum){
        _messageSlip();
    }

    _showDialog(info,message);
}

void Bubble::showWarn(QString message)
{
    if(_messageList.count() >= maxMessageNum){
        _messageSlip();
    }

    _showDialog(warning, message);
}

void Bubble::showError(QString message)
{
    if(_messageList.count() >= maxMessageNum){
        _messageSlip();
    }

    _showDialog(error, message);
}

void Bubble::_messageSlip(void)
{
    if(_messageList.count() >= maxMessageNum){
        QDialog* tmp = _messageList[0];
        for(int i = 1; i < _messageList.count();i++){
            QDialog* dialog = _messageList[i];
            dialog->move(dialog->x(), dialog->y() + tmp->height() + spacing);
        }
        tmp->close();
        tmp->deleteLater();
    }
}

void Bubble::_showDialog(const _messageGrade grade, const QString message)
{
    QDialog* dialog = new QDialog();
    dialog->resize(300,150);
    dialog->move(QApplication::desktop()->screenGeometry().width() - dialog->width() - 20,
            QApplication::desktop()->screenGeometry().height() - dialog->height() - 100 - totalHeight);
    QLabel* label = new QLabel(dialog);
    label->resize(dialog->width(),dialog->height() / 2);
    label->move(10, (dialog->height() - label->height()) / 2);
    label->setWordWrap(true);

    QString gradeLabel("Info");
    switch (grade) {
    case info:
        gradeLabel = QString("Info: ");
        label->setStyleSheet("font:16px;color:green");
        startHideTimer(dialog);
        break;
    case warning:
        gradeLabel = QString(tr("Warn: "));
        label->setStyleSheet("font:16px;color:orange");
        break;
    case error:
        gradeLabel = QString(tr("Error: "));
        label->setStyleSheet("font:16px;color:red");
        break;
    default:
        gradeLabel = QString("Info: ");
        label->setStyleSheet("font:16px;color:green");
        break;
    }
    dialog->setWindowTitle(gradeLabel);
    QString gradeMessage = gradeLabel + message;
    label->setText(gradeMessage);
    dialog->show();
    connect(dialog, &QDialog::finished, this, &Bubble::_attempClose);
    totalHeight += dialog->height() + spacing;
    _messageList.append(dialog);
}

void Bubble::_attempClose(void)
{
    QDialog* actionSender = qobject_cast<QDialog*>(sender());
    _messageList.removeOne(actionSender);
    totalHeight -= actionSender->height() + spacing;
    int lastHeight = 0;
    for(int i = 0;i < _messageList.count();i++){
        QDialog* dialog = _messageList[i];
        dialog->move(QApplication::desktop()->screenGeometry().width() - dialog->width() - 20,
                QApplication::desktop()->screenGeometry().height() - dialog->height() - 100 - lastHeight);
        lastHeight += dialog->height() + spacing;
    }
}

void Bubble::startHideTimer(QDialog* dialog)
{
    for(int i = 0;i < maxMessageNum;i++){
        QTimer *temp = _hideDialogTimer[i];
        if(!temp){
            _hideDialogTimer[i] = new QTimer();
        }

        if(_hideDialogTimer[i] && !_hideDialogTimer[i]->isActive()){
            _hideDialogTimer[i]->start(holdInfo);
            connect(_hideDialogTimer[i],    &QTimer::timeout,   dialog,   &QDialog::close);
            break;
        }
    }
}


