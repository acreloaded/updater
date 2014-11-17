#include "mainworker.h"

MainWorker::MainWorker() : QObject()
{
    SavedData = new ConfigData();
}

//Left for non-gui stuff
void MainWorker::parseCmd(QStringList av)
{
    if(av.length() < 2) {
        help("");
        return;
    } else if(!QString(av[1]).contains("init", Qt::CaseInsensitive)) {
        loadData();
    }
    //Better than calling functions directly by name (imo)
    if(QString(av[1]).contains("runclient", Qt::CaseInsensitive)) {
        runClient();
    } else if(QString(av[1]).contains("runserver", Qt::CaseInsensitive)) {
        runServer(false);
    } else if(QString(av[1]).contains("updateall", Qt::CaseInsensitive)) {
        updateAll();
    } else if(QString(av[1]).contains("updateme", Qt::CaseInsensitive)) {
        updateMe();
    } else if(QString(av[1]).contains("updateacr", Qt::CaseInsensitive)) {
        updateGame();
    } else if(QString(av[1]).contains("updatemods", Qt::CaseInsensitive)) {
        //TODO
    } else if(QString(av[1]).contains("installmods", Qt::CaseInsensitive)) {
        //TODO
    } else if(QString(av[1]).contains("listmods", Qt::CaseInsensitive)) {
        //TODO
    } else if(QString(av[1]).contains("installlocalmods", Qt::CaseInsensitive)) {
        //TODO
    } else if(QString(av[1]).contains("installedmods", Qt::CaseInsensitive)) {
        //TODO
    } else if(QString(av[1]).contains("backup", Qt::CaseInsensitive)) {
        //TODO
    } else if(QString(av[1]).contains("init", Qt::CaseInsensitive)) {
        init();
    } else {
        help(av[2]);
    }
    //Quick and dirty...
    cout << msgOut.readAll().toStdString();
}


//Remove mod from list -DONE
QString MainWorker::pruneMod(QString badMod) {
    QString ret_value = "Not found!";
    QList<QString> newList;
    for(int i = 0; i < SavedData->getInstalledMods().count(); i++) {
        if(SavedData->getInstalledMods()[i].compare(badMod.trimmed(), Qt::CaseInsensitive)) {
            newList.append(SavedData->getInstalledMods()[i]);
            ret_value = "\"" + badMod + "\"" + " removed!";
        }
    }
    SavedData->setInstalledMods(newList);
}

//Get config data and mods -DONE
QString MainWorker::loadData() {
    //Read config data
    QString ret_val = "";
    switch(SavedData->readConfig()) {
    case ConfigData::NOT_FOUND:
    {
        switch (SavedData->init()) {
        case ConfigData::WRITE_ERROR:
            ret_val =+ "Unable to write config file, do you have writing permission? ";
        case ConfigData::SUCCESS:
            ret_val =+ "Config successfuly written ";
        }
    }
    case ConfigData::READ_ERROR:
        ret_val =+ "Error loading ConfigData ";
    case ConfigData::SUCCESS:
        ret_val =+ "Loaded ConfigData ";
    }

    //Get mods anyway ;)
    d = new ModListDownloader(SavedData->getModserverurl(), SavedData);
    connect(d, SIGNAL(isReady()), this, SLOT(on_modListDownloader_isReady()));
    return ret_val;
}

void MainWorker::on_modListDownloader_isReady() {
    emit modListDownloader_isReady();
}



//TODO return
QString MainWorker::writeClientExecutable() {
    QString extraMods = "";
    foreach (QString mod, SavedData->getInstalledMods()) {
        extraMods += "--mod=mods/" + mod.trimmed().split('-')[0] + " ";
    }
#ifdef Q_OS_WIN32
    switch (SavedData->writeClientScript("cd acr\nbin_win32\\ac_client.exe --home=data " + extraMods + "--mod=acr --init %*", 1)) {
    case ConfigData::WRITE_ERROR:
        return "Unable to write custom launcher, do you have writing permission?";
    case ConfigData::READ_ERROR:
        return "Unable to read original launcher, check your installation!";
    case ConfigData::OTHER_ERROR:
        return "Unable to write a launcher!";
    }
    return "Wrote Client Launcher.";
#endif
#ifdef Q_OS_UNIX
    switch (SavedData->writeClientScript("CUBE_OPTIONS=\"--home=data " + extraMods + "--mod=acr --init\"", 2)) {
    case ConfigData::WRITE_ERROR:
        return "Unable to write custom launcher, do you have writing permission?";
    case ConfigData::READ_ERROR:
        return "Unable to read original launcher, check your installation!";
    case ConfigData::OTHER_ERROR:
        return "Unable to write a launcher!";
    }
#ifndef Q_OS_LINUX //Unix, but not Linux
     return "You are using an uncommon UNIX, probably you'll have to compile the game yourself.\n Wrote Client Launcher.";
#endif
    return "Successfully wrote Client Launcher.";
#endif
    return "You have to supply your own bat/sh type file. I don't know how to write one for your system!";
}

QString MainWorker::writeServerExecutable() {
    QString extraMods = "";
    foreach (QString mod, SavedData->getInstalledMods()) {
        extraMods += "--mod=mods/" + mod.trimmed().split('-')[0] + " ";
    }
#ifdef Q_OS_WIN32
    switch (SavedData->writeServerScript("cd acr\nbin_win32\\ac_server.exe --home=data " + extraMods + "--mod=acr --init %*", 1)) {
    case ConfigData::WRITE_ERROR:
        return "Unable to write custom launcher, do you have writing permission?";
    case ConfigData::READ_ERROR:
        return "Unable to read original launcher, check your installation!";
    case ConfigData::OTHER_ERROR:
        return "Unable to write a launcher!";
    }
    return "Wrote Server Launcher!";
#endif
#ifdef Q_OS_UNIX
    switch (SavedData->writeServerScript("CUBE_OPTIONS=\"--home=data " + extraMods + "--mod=acr --init\"", 2)) {
    case ConfigData::WRITE_ERROR:
        return "Unable to write custom launcher, do you have writing permission?";
    case ConfigData::READ_ERROR:
        return "Unable to read original launcher, check your installation!";
    case ConfigData::OTHER_ERROR:
        return "Unable to write a launcher!";
    }
#ifndef Q_OS_LINUX //Unix, but not Linux
    return "You are using an uncommon UNIX, probably you'll have to compile the game yourself.\nWrote Server Launcher.";
#endif
    return "Wrote Server Launcher!";
#endif
    return "You have to supply your own bat/sh type file. I don't know how to write one for your system.";
}

void MainWorker::init() {
    SavedData->init();
}

void MainWorker::updateAll() {
    msgOut << "Updating everything..." << endl;

    updateGame();
    updateMe();

    //TODO
    msgOut << "Done updating" << endl;
}

void MainWorker::updateGame() {
    /*Downloader d("file:///");
    d.getData();
    qDebug("dursch");
    /*FileDownloader *fd;
    fd = new FileDownloader(QUrl::fromEncoded("http://example.com"), this);
    connect(fd, SIGNAL(downloaded()), this, SLOT(downloadFinished()));
    fd->start();
    ql.exec();
    qDebug("downready");
    QFile f("test.htm");
    f.open(QIODevice::WriteOnly);
    f.write(fd->downloadedData());
    f.close();*/
}

void MainWorker::updateMe() {
    //TODO
}

//TODO: Implement downloaders

QStringList MainWorker::avialableMods() {
    QStringList tmp;
    foreach (ModEntry me, SavedData->getAvailableMods()) {
        tmp.append(me.toString());
    }
    return tmp;
}

QStringList MainWorker::installedMods() {
    return SavedData->getInstalledMods();
}

QStringList MainWorker::getModInfos(QString mod) {
    QStringList result;
    foreach (ModEntry m, SavedData->getAvailableMods()) {
      if(!m.Name.compare(mod)) {
          result.append(m.Name);
          result.append(m.Url);
          result.append("Version " + m.Version);
          result.append("By " + m.Author);
          result.append(m.Description);
      }
    }
    return result;
}

QString MainWorker::runClient() {
    QString ret_val = writeClientExecutable();
#ifdef Q_OS_WIN32
    QProcess p;
    p.start("Client.bat");
    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.waitForFinished(-1);
    return ret_val;
#endif
#ifdef Q_OS_UNIX
    QProcess p;
    p.start("./Client.sh");
    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.waitForFinished(-1);
    return ret_val;
#endif
    return "I don't recognize your OS";
}

QString MainWorker::runServer(bool new_window) {
    QString ret_val = writeServerExecutable();
    if(new_window) {
        ServerConsole *sc = new ServerConsole(0, ret_val);
        sc->show();
        return ret_val;
    }
#ifdef Q_OS_WIN32
    QProcess p;
    p.start("Server.bat");
    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.waitForFinished(-1);
    return ret_val;
#endif
#ifdef Q_OS_UNIX
    QProcess p;
    p.start("./server.sh");
    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.waitForFinished(-1);
    return ret_val;
#endif
    return "I don't recognize your OS" ;
}

QString MainWorker::createBackup() {
    QStringList filesandfolders;
    filesandfolders.append("acr");
    filesandfolders.append("updater.conf");
    if(SavedData->createZipfile(filesandfolders, QDateTime::currentDateTime().toString()) != SavedData->SUCCESS) {
        return "Something went wrong. Better look yourself.";
    }
    return "Backup created!";
}

QString MainWorker::installBackup(QString file) {
    if(SavedData->extractZipfile(file) == SavedData->SUCCESS) {
        return "Backup installed!";
    } else {
        return "Error installing backup!";
    }
}

QString MainWorker::installMod(QString mod) {
    //Check if already installed
    foreach (QString instMod, SavedData->getInstalledMods()) {
        if(!instMod.compare(mod)) {
            return "You already have a version of this mod installed!\nMaybe try an update?";
        }
    }
    //Select the mod we want to install
    ModEntry me;
    foreach (ModEntry currMod, SavedData->getAvailableMods()) {
        if(!currMod.Name.compare(mod)) {
            me = currMod;
        }
    }
    DownloadDialog dloadDialog(me.Url);
    connect(&dloadDialog, SIGNAL(downloadReady(QByteArray)), this, SLOT(on_DownloadDialog_downloadReady(QByteArray)));
    dloadDialog.exec();
    return "Downloaded mod \"" + mod +"\"";
}

void MainWorker::on_DownloadDialog_downloadReady(QByteArray data) {
    if(SavedData->installMod(data) != ConfigData::SUCCESS) {
        emit installerReady("Error installing mod!");
    }
    emit installerReady("Mod installed!");
}


void MainWorker::help(QString cmd) {
    msgOut << "You need to specify a valid option for the updater" << endl;
    msgOut << "Available options are:" << endl;
    msgOut << "init - Initiates the updater configs" << endl;
    msgOut << "backup - Create a backup of the files and config" << endl;
    msgOut << "updateall - Checks everything for updates" << endl;
    msgOut << "updateme - update the updater" << endl;
    msgOut << "updateacr - Checks for updates to ACR" << endl;
    msgOut << "updatemods - Check for mod updates" << endl;
    msgOut << "installmods <mod1>, <mod2>... - Comma separated list of mods to install" << endl;
    msgOut << "listmods - Gets the mod list from the server with versions" << endl;
    msgOut << "installlocalmod <file> - installs a zipfile as a mod" << endl;
    msgOut << "removemods <mod1>, <mod2>... - Comma separated list of mods to remove" << endl;
    msgOut << "installedmods - Prints out the installed mods along with versions" << endl;
    msgOut << "runclient - runs the client" << endl;
    msgOut << "runserver - runs the server" << endl;
    //msgOut << "help <option> - Explains how to use <option> or if excluded gives you this dialogue";
    return;
}

QString MainWorker::getMsg() {
    QString tmp = msgOut.readAll();
    msgOut.reset();
    return tmp;
}
