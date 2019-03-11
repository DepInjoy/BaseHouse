#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H
#include <QObject>

class MainQmlSingle;
class MainApplication : public QObject
{
    Q_OBJECT
public:
    explicit MainApplication(QObject *parent = nullptr);
    ~MainApplication();
signals:

public slots:
private:
    void _init(void);
};
static MainApplication* _app;
static MainApplication* mainApp();
#endif // MAINAPPLICATION_H
