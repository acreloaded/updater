#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QTextStream>
#include <QTemporaryFile>

//TODO
#include <QtDebug>

#include <JlCompress.h>

//Class to symbolise a mod
class ModEntry {
public:
    //ugly
    QString Name;
    QString Author;
    QString Version;
    QString Description;
    QString Url;

    void clear() {
        Name.clear();
        Author.clear();
        Version.clear();
        Description.clear();
        Url.clear();
    }

    QString toString() {
        return this->Name;
    }
};

class ConfigData
{
public:
    ConfigData();
    int readConfig();
    int init();

    int writeClientScript(QString content, int os);
    int writeServerScript(QString content, int os);

    int extractZipfile(QString zipfile);
    int createZipfile(QStringList files, QString name);
    void rec_copy(QDir folder, QDir current);
    void rec_rem(QDir folder);

    int installMod(QByteArray modData);

    //Default getter and setter
    QString getVersion() const;
    void setVersion(const QString &value);
    QList<QString> getInstalledMods() const;
    void setInstalledMods(const QList<QString> &value);
    QList<ModEntry> getAvailableMods() const;
    void setAvailableMods(const QList<ModEntry> &value);
    void addToAvailableMods(ModEntry &value);
    QString getModserverurl() const;
    void setModserverurl(const QString &value);

    enum Errors {
        SUCCESS,
        NOT_FOUND,
        READ_ERROR,
        WRITE_ERROR,
        OTHER_ERROR
    };

private:
        QString version = "-";
        QList<QString> installedMods;
        QList<ModEntry> availableMods;
        QString modserverurl = "https://ruler501git.tk/acr/mods";
};

#endif // CONFIGDATA_H
