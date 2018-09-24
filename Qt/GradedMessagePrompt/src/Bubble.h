#ifndef BUBBLE_H
#define BUBBLE_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QTimer>

class Bubble : public QWidget
{
    Q_OBJECT
public:
    explicit Bubble(QWidget *parent = 0);
    ~Bubble();
    static int totalHeight;

    void showInfo(QString message);
    void showWarn(QString message);
    void showError(QString message);
signals:

public slots:
private slots:
    void _attempClose(void);
private:
    typedef enum{
        info = 0,
        warning,
        error,
    }_messageGrade;

    void _messageSlip(void);
    void _showDialog(const _messageGrade grade, const QString string);

    static const quint8 maxMessageNum = 5;
    static const quint8 spacing = 50;
    static const quint16 holdInfo = 4000;           //unit s
    QList<QDialog*>                     _messageList;
    QTimer*                             _hideDialogTimer[5];
    void startHideTimer(QDialog* dialog);
};

#endif // BUBBLE_H
