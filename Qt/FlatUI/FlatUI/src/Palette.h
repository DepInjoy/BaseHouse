#ifndef PALETTE_H
#define PALETTE_H

#include <QObject>
#include <QColor>

class Palette : public QObject
{
    Q_OBJECT
public:
    explicit Palette(QObject *parent = nullptr);
    Q_PROPERTY(QColor   window              READ window             CONSTANT)
    Q_PROPERTY(QColor   windowInner         READ windowInner        CONSTANT)
    Q_PROPERTY(QColor   disableHint         READ disableHint        CONSTANT)
    Q_PROPERTY(QColor   infoHint            READ infoHint           CONSTANT)
    Q_PROPERTY(QColor   warningHint         READ warningHint        CONSTANT)
    Q_PROPERTY(QColor   errorHint           READ errorHint          CONSTANT)
    Q_PROPERTY(QColor   text                READ text               CONSTANT)

    QColor window(void)         {return _window;}
    QColor windowInner(void)    {return _windowInner;}
    QColor disableHint(void)    {return _disableHint;}
    QColor infoHint(void)       {return _infoHint;}
    QColor warningHint(void)    {return _warningHint;}
    QColor errorHint(void)      {return _errorHint;}
    QColor text(void)           {return _text;}
private:
    QColor _window = 0xECF0F1;
    QColor _windowInner = 0xBDC3C7;
    QColor _disableHint = 0xECF0F1;
    QColor _infoHint = 0x1ABC9C;
    QColor _warningHint = 0xE67E22;
    QColor _errorHint = 0xE74C3C;
    QColor _text = 0x7F8C8D;
};

#endif // PALETTE_H
