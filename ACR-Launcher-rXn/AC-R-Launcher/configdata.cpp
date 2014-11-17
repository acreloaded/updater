#include "configdata.h"

ConfigData::ConfigData()
{
    //ACR doesnt count as mod
    //installedMods.insert(installedMods.count(), "../acr");
}

int ConfigData::readConfig() {
    QFile configFile("updater.conf");
        if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return NOT_FOUND;
        }
        QString line;
        line = configFile.readLine();
        line = line.trimmed();
        while(line != NULL) {
            if(line != "") {
                if(!line.split("=")[0].compare("version", Qt::CaseInsensitive)) {
                    version = line.split("=")[1];
                } else if(!line.split("=")[0].compare("modlist", Qt::CaseInsensitive)) {
                    line = line.split("=")[1];
                    QStringList mods = line.split(",");
                    installedMods = mods;
                } else if(!line.split("=")[0].compare("modserverurl", Qt::CaseInsensitive)) {
                    modserverurl = line.split("=")[1];
                }
            }
            line = configFile.readLine();
            line = line.trimmed();
        }
        //Check if read correctly
        if(version.isNull() || modserverurl.isNull() || !modserverurl.contains("/")) {
            configFile.close();
            return READ_ERROR;
        }
        configFile.close();
        return SUCCESS;
}

int ConfigData::init() {
    QDir dir("acr/mods");
    dir.setFilter(QDir::Dirs);
    dir.setFilter(QDir::NoDot);
    dir.setFilter(QDir::NoDotDot);
    setInstalledMods(dir.entryList());
    QFile config("updater.conf");
    if(!config.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text)) {
        return WRITE_ERROR;
    }
    QTextStream confout(&config);
    if(installedMods.count()>0) {
        QString mods;
        foreach (QString m, installedMods) {
            mods = mods + ',' + m;
        }
    }
    confout << "version=" << version << endl << "modlist=" << endl << "modserverurl=" << modserverurl;
    confout.flush();
    config.close();
    return SUCCESS;
}

int ConfigData::writeServerScript(QString content, int os) {
    switch (os) {
    case 1: //Windows
    {
        QFile batch("Server.bat");
        if(!batch.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return WRITE_ERROR;
        }
        batch.write(content.toAscii());
        batch.close();
        break;
    }
    case 2: //UNIX/Linux/Whatever
    {
        //Taken from my *quick* fix of the python version. Feel free to improve ;)
        QFile origFile("acr/server.sh");
        if(!origFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return READ_ERROR;
        }
        QFile shell("Server.sh");
        if(!shell.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return WRITE_ERROR;
        }
        QTextStream sout(&shell);
        QString tmp = origFile.readLine();
        sout << tmp << "cd acr/" << endl;
        tmp = origFile.readLine();
        while(!tmp.contains("CUBE_OPTIONS", Qt::CaseInsensitive)) {
            sout << tmp;
            tmp = origFile.readLine();
        }
        //Now skip and replace the "bad" line...
        sout << content << endl;
        origFile.readLine(); tmp = origFile.readLine();
        //...and write the remaining stuff.
        sout << origFile.readAll();
        shell.close();
        origFile.close();
        //Too lazy to figure out native file permission handling ;)
        QProcess p;
        p.start("chmod +x ./Server.sh");
        p.waitForFinished(-1);
        break;
    }
    default:
    {
        return OTHER_ERROR;
    }
    }
    return SUCCESS;
}


int ConfigData::writeClientScript(QString content, int os) {
    switch (os) {
    case 1: //Windows
    {
        QFile batch("Client.bat");
        if(!batch.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return WRITE_ERROR;
        }
        batch.write(content.toAscii());
        batch.close();
        break;
    }
    case 2: //UNIX/Linux/Whatever
    {
        //Taken from my *quick* fix of the python version. Feel free to improve ;)
        QFile origFile("acr/client.sh");
        if(!origFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return READ_ERROR;
        }
        QFile shell("Client.sh");
        if(!shell.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return WRITE_ERROR;
        }
        QTextStream sout(&shell);
        QString tmp = origFile.readLine();
        sout << tmp << "cd acr/" << endl;
        tmp = origFile.readLine();
        while(!tmp.contains("CUBE_OPTIONS", Qt::CaseInsensitive)) {
            sout << tmp;
            tmp = origFile.readLine();
        }
        //Now skip and replace the "bad" line...
        sout << content << endl;
        origFile.readLine(); tmp = origFile.readLine();
        //...and write the remaining stuff.
        sout << origFile.readAll();
        shell.close();
        origFile.close();
        //Too lazy to figure out native file permission handling ;)
        QProcess p;
        p.start("chmod +x ./Client.sh");
        p.waitForFinished(-1);
        break;
    }
    default:
    {
        return OTHER_ERROR;
    }
    }
    return SUCCESS;
}

int ConfigData::extractZipfile(QString zipfile) {
    if(JlCompress::extractDir(zipfile).at(0).contains("()")) {
        return OTHER_ERROR;
    }
    return SUCCESS;
}

int ConfigData::createZipfile(QStringList files, QString name) {
    QDir tmp;
    tmp.mkdir(name);
    foreach(QString s, files) {
        QFileInfo fi(s);
        if(fi.isFile()) {
            QFile::copy(s, name+"/"+s);
        } else if(fi.isDir()) {
            tmp.mkdir(name+"/"+s);
            rec_copy(QDir(s), QDir(name+"/"+s));
        }
    }
    if(!JlCompress::compressDir(name+".zip", name)) {
        return WRITE_ERROR;
    }
    rec_rem(QDir(name));
    return SUCCESS;
}

//ugly
void ConfigData::rec_copy(QDir folder, QDir current) {
    QDir tmp;
    foreach(QString s, folder.entryList()) {
        if(s.startsWith(".")) {
            continue;
        }
        QFileInfo fi(folder.filePath(s));
        if(fi.isFile()) {
            QFile::copy(folder.filePath(s), current.filePath(s));
        } else if(fi.isDir()) {
            tmp.mkdir(current.path()+"/"+ s);
            rec_copy(QDir(folder.filePath(s)), QDir(current.path()+"/"+s));
        }
    }
}
//again
void ConfigData::rec_rem(QDir folder) {
    QDir tmp;
    foreach(QString s, folder.entryList()) {
        if(s.startsWith(".")) {
            continue;
        }
        QFileInfo fi(folder.filePath(s));
        if(fi.isFile()) {
            QFile::remove(folder.filePath(s));
        } else if(fi.isDir()) {
            rec_rem(QDir(folder.filePath(s)));
        }
    }
    tmp.rmdir(folder.path());
    //qDebug(folder.path().toAscii());
}

int ConfigData::installMod(QByteArray modData) {
    QTemporaryFile q;
    if(!q.isWritable()) {
        return WRITE_ERROR;
    }
    q.write(modData.data());
    qDebug() << q.copy("acr/mod/" + q.fileName()) << "hier";
    extractZipfile(q.fileName());
    q.remove();
}

// DEFAULT GETTERS AND SETTERS BELOW THIS LINE //

QString ConfigData::getVersion() const
{
    return version;
}

void ConfigData::setVersion(const QString &value)
{
    version = value;
}
QList<QString> ConfigData::getInstalledMods() const
{
    return installedMods;
}

void ConfigData::setInstalledMods(const QList<QString> &value)
{
    installedMods = value;
}
QList<ModEntry> ConfigData::getAvailableMods() const
{

    return availableMods;
}

void ConfigData::addToAvailableMods(ModEntry &value) {
    availableMods.append(value);
}

void ConfigData::setAvailableMods(const QList<ModEntry> &value)
{
    availableMods = value;
}
QString ConfigData::getModserverurl() const
{
    return modserverurl;
}

void ConfigData::setModserverurl(const QString &value)
{
    modserverurl = value;
}
