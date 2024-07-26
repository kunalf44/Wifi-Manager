
#include "connection.h"
#include <QNetworkSettingsInterfaceModel>
#include <QNetworkSettingsInterface>
#include <QNetworkSettingsService>
#include <QNetworkSettingsWireless>//signal strernght
Connection::Connection(QObject *parent) : QObject(parent)
{
    manager = new QNetworkSettingsManager(this);
    QObject::connect(manager, &QNetworkSettingsManager::interfacesChanged,
                     this, &Connection::interfacesChanged);

    QObject::connect(manager, &QNetworkSettingsManager::servicesChanged,
                     this, &Connection::servicesChanged);

}

Q_INVOKABLE void Connection::connect(QString user, QString pass)
{
    // Implement your connection logic here
    const QString u=user;
    const QString p=pass;
    manager->connectBySsid(u,p);
}

Q_INVOKABLE QString Connection::cuurent_ip(){
    servicesChanged();
    interfacesChanged();
    return hold_ip;
}

int i=0;
Q_INVOKABLE void Connection::servicesChanged()
{
    QNetworkSettingsServiceFilter serviceFilter;
    // QNetworkSettingsWireless *a;
     serviceFilter.setType(QNetworkSettingsType::Wifi);
    // QList<QNetworkSettingsService*> services = manager->services();
         QList<QNetworkSettingsService*> services = qobject_cast<QNetworkSettingsServiceModel*>(manager->services()->sourceModel())->getModel();
    // QList<QNetworkSettingsService*> services = manager->services(); // Access the services directly
         // for(int i=0;i<list.size();i++) list.pop_back();
         list.clear();
         hold_ip="";
    for (const auto &service : services) {
             qDebug() << service->name();
        if(service->name()!="Wired")  list.push_back(service->name());
        qDebug()<<"ip:"<<service->ipv4()->address();
        if(service->ipv4()->address()!=""){
            hold_ip=service->name() + " " +service->ipv4()->address()+" Range: "+QString::number(service->wirelessConfig()->signalStrength());
            qDebug()<<"wireless config "<<service->wirelessConfig()->signalStrength();
        }
    }
    if(hold_ip==""){
        hold_ip="Not Connected";
    }
}

Q_INVOKABLE void Connection::disconnect()
{
    // void QNetworkSettingsService::disconnectService()
    QNetworkSettingsServiceFilter serviceFilter;
    serviceFilter.setType(QNetworkSettingsType::Wifi);
    QList<QNetworkSettingsService*> services = qobject_cast<QNetworkSettingsServiceModel*>(manager->services()->sourceModel())->getModel();
    for (const auto &service : services) {
        if(service->ipv4()->address()!=""){
            qDebug()<<"Terminating connection.."<<service->name();
            service->disconnectService();
            break;
        }
    }
}

Q_INVOKABLE void Connection::interfacesChanged()
{
    QNetworkSettingsWireless a;
    qDebug()<<a.signalStrength();
    QNetworkSettingsWireless wirelessSettings;
    // Assuming QNetworkSettingsWireless has a signalStrength property
    int signalStrength = wirelessSettings.signalStrength();

    qDebug() << "WiFi Signal Strength:" << signalStrength;
    QList<QNetworkSettingsInterface*> interfaces = manager->interfaces()->getModel();
    // QList<QNetworkSettingsInterface*> interfaces = manager->interfaces()->getModel();
    for (const auto &interface : interfaces) {
        if (interface->type() == QNetworkSettingsType::Wifi) {
            if (interface->powered()) {
                interface->scanServices();
            } else {
                interface->setPowered(true);
            }

            qDebug()<<interface->name()<<"Interface name";
        }
    }
}

Q_INVOKABLE QVector<QString> Connection::setwifi_name(){

    if(list.size()>0){
        return list;
    }
    else qDebug()<<"list is empty";
    return list;

}

Q_INVOKABLE void Connection::reboot(){
    QProcess process;
    process.start("reboot",{});
    if (process.error() == QProcess::FailedToStart) {
        qDebug() << "Failed to start process: " << process.errorString();
    }
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    qDebug()<<output;
}
