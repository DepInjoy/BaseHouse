#ifndef MAINQMLSINGLE_H
#define MAINQMLSINGLE_H

#include <QObject>
#include "MainApplication.h"

class MainQmlSingle : public QObject
{
    Q_OBJECT
public:
    explicit MainQmlSingle(MainApplication* app);
    ~MainQmlSingle();
signals:

public slots:
};

#endif // MAINQMLSINGLE_H
