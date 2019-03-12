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

    enum MsgLevel{
        MSG_DISABLE_LEVEL,
        MSG_INFO_LEVEL,
        MSG_WARNING_LEVEL,
        MSG_ERROR_LEVEL,
        MSG_ACCEPTED_LEVEL,
        MSG_REFUSED_LEVEL,
        MSG_END_LEVEL,
    };

    Q_ENUMS(MsgLevel)
signals:

public slots:
};

#endif // MAINQMLSINGLE_H
