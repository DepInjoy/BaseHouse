#ifndef PALETTE_H
#define PALETTE_H

#include <QObject>

class Palette : public QObject
{
    Q_OBJECT
public:
    explicit Palette(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PALETTE_H