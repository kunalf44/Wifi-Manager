#ifndef CONNECTION_H
#define CONNECTION_H
#include<QObject>
#include <QNetworkSettingsManager>
#include<QDebug>
#include <QNetworkSettingsServiceModel>
#include <QProcess>
  #include <QVector>
 #include <QNetworkSettingsIPv4>
class Connection: public QObject
{
    Q_OBJECT

public:
    Connection(QObject *parent = nullptr);
    Q_INVOKABLE void connect(const QString user,const QString pass);
    Q_INVOKABLE void disconnect();
     Q_INVOKABLE void interfacesChanged();
    Q_INVOKABLE void servicesChanged();
    Q_INVOKABLE QVector<QString> setwifi_name();
    Q_INVOKABLE QString cuurent_ip();
    Q_INVOKABLE void reboot();
    QString hold_ip="";
    QNetworkSettingsManager *manager;
    QVector<QString> list;
    QNetworkSettingsIPv4 ip;
};

#endif // CONNECTION_H
