#include "mainworker.h"

MainWorker::MainWorker(QObject *parent) : QObject(parent)
{
    SavedData = new ConfStruct();
    message = new QString();
    msgOut.setString(message);
}

//Left for non-gui stuff
void MainWorker::parseCmd(QStringList av) {
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
        runServer();
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
        installedMods(true);
    } else if(QString(av[1]).contains("init", Qt::CaseInsensitive)) {
        init();
    } else {
        help(av[2]);
    }
    //Quick and dirty...
    cout << msgOut.readAll().toStdString();
}

//So we have GUI...
void MainWorker::parseCmd(QString av) {
    if(!av.contains("init", Qt::CaseInsensitive)) {
        loadData();
    }
    //Better than calling functions directly by name (imo)
    if(av.contains("runclient", Qt::CaseInsensitive)) {
        runClient();
    } else if(av.contains("runserver", Qt::CaseInsensitive)) {
        runServer();
    } else if(av.contains("updateall", Qt::CaseInsensitive)) {
        updateAll();
    } else if(av.contains("updateme", Qt::CaseInsensitive)) {
        updateMe();
    } else if(av.contains("updateacr", Qt::CaseInsensitive)) {
        updateGame();
    } else if(av.contains("updatemods", Qt::CaseInsensitive)) {
        //TODO
    } else if(av.contains("installmods", Qt::CaseInsensitive)) {
        //TODO
    } else if(av.contains("listmods", Qt::CaseInsensitive)) {
        //TODO
    } else if(av.contains("installlocalmods", Qt::CaseInsensitive)) {
        //TODO
    } else if(av.contains("installedmods", Qt::CaseInsensitive)) {
        installedMods(true);
    } else if(av.contains("init", Qt::CaseInsensitive)) {
        init();
    } else {
        help(av);
    }
    emit(messageToDisplay());
}

void MainWorker::pruneMod(QString badMod) {
    QList<QString> newList;
    for(int i = 0; i < SavedData->modlist.count(); i++) {
        if(SavedData->modlist[i].compare(badMod.trimmed(), Qt::CaseInsensitive)) {
            newList.append(SavedData->modlist[i]);
        }
    }
    SavedData->modlist = newList;
}

void MainWorker::loadData() {
    QFile configFile("updater.conf");
    if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        msgOut << "No config file fond, creating one..." << endl;
        init();
        return;
    }
    QString line;
    line = configFile.readLine();
    line = line.trimmed();
    while(line != NULL) {
        if(line != "") {
            if(line.split("=")[0].compare("version", Qt::CaseInsensitive)) {
                SavedData->version = line.split("=")[1];
            } else if(line.split("=")[0].compare("modlist", Qt::CaseInsensitive)) {
                line = line.split("=")[1];
                QStringList mods = line.split(",");
                SavedData->modlist = mods;
            } else if(line.split("=")[0].compare("modserverurl", Qt::CaseInsensitive)) {
                //TODO
            }
        }
        line = configFile.readLine();
        line = line.trimmed();
    }
}

//TODO return
void MainWorker::writeClientExecutable() {
    QString extraMods = "";
    foreach (QString mod, SavedData->modlist) {
        extraMods += "--mod=mods/" + mod.trimmed().split('-')[0] + " ";
    }
#ifdef Q_OS_WIN32
    QFile batch("Client.bat");
    if(!batch.open(QIODevice::WriteOnly | QIODevice::Text)) {
        msgOut << "Unable to write custom launcher, do you have writing permission?." << endl;
        return;
    }
    QTextStream bout(&batch);
    bout << "cd acr\nbin_win32\\ac_client.exe --home=data " << extraMods << "--mod=acr --init %*";
    batch.close();
    msgOut << "Wrote Client Launcher" << endl;
    return;
#endif
#ifdef Q_OS_UNIX
    //Taken from my *quick* fix of the python version. Feel free to improve ;)
    QFile origFile("acr/client.sh");
    if(!origFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        msgOut << "Unable to read original launcher, check your installation!." << endl;
        return;
    }
    QFile shell("Client.sh");
    if(!shell.open(QIODevice::WriteOnly | QIODevice::Text)) {
        msgOut << "Unable to write custom launcher, do you have writing permission?." << endl;
        return;
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
    sout << "CUBE_OPTIONS=\"--home=data " << extraMods<< "--mod=acr --init\"" << endl;
    origFile.readLine(); tmp = origFile.readLine();
    //...and write the remaining stuff.
    sout << origFile.readAll();
    shell.close();
    origFile.close();
    //Too lazy to figure out native file permission handling ;)
    QProcess p;
    p.start("chmod +x ./Client.sh");
    p.waitForFinished(-1);
#ifndef Q_OS_LINUX //Unix, but not Linux
    msgOut << "You are using an uncommon UNIX, probably you'll have to compile the game yourself." << endl;
#endif
    msgOut << "Wrote Client Launcher" << endl;
    return;
#endif
    msgOut << "You have to supply your own bat/sh type file. I don't know how to write one for your system" << endl;
    return;
}

void MainWorker::writeServerExecutable() {
    QString extraMods = "";
    foreach (QString mod, SavedData->modlist) {
        extraMods += "--mod=mods/" + mod.trimmed().split('-')[0] + " ";
    }
#ifdef Q_OS_WIN32
    QFile batch("Server.bat");
    if(!batch.open(QIODevice::WriteOnly | QIODevice::Text)) {
        msgOut << "Unable to write custom launcher, do you have writing permission?." << endl;
        return;
    }
    QTextStream bout(&batch);
    bout << "cd acr\nbin_win32\\ac_server.exe --home=data " << extraMods << "--mod=acr -Cconfig/servercmdline.txt%*" << endl << pause;
    batch.close();
    msgOut << "Wrote Server Launcher" << endl;
    return;
#endif
#ifdef Q_OS_UNIX
    //Taken from my *quick* fix of the python version. Feel free to improve ;)
    QFile origFile("acr/server.sh");
    if(!origFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        msgOut << "Unable to read original launcher, check your installation!." << endl;
        return;
    }
    QFile shell("Server.sh");
    if(!shell.open(QIODevice::WriteOnly)) {
        msgOut << "Unable to write custom launcher, do you have writing permission?." << endl;
        return;
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
    sout << "CUBE_OPTIONS=\"--home=data " << extraMods<< "--mod=acr\"" << endl;
    origFile.readLine(); tmp = origFile.readLine();
    //...and write the remaining stuff.
    sout << origFile.readAll();
    shell.close();
    origFile.close();
    //Too lazy to figure out native file permission handling ;)
    QProcess p;
    p.start("chmod +x ./Server.sh");
    p.waitForFinished(-1);
#ifndef Q_OS_LINUX //Unix, but not Linux
    msgOut << "You are using an uncommon UNIX, probably you'll have to compile the game yourself." << endl;
#endif
    msgOut << "Wrote Server Launcher" << endl;
    return;
#endif
    msgOut << "You have to supply your own bat/sh type file. I don't know how to write one for your system" << endl;
    return;
}

void MainWorker::init() {
    msgOut << "Initializing...";
    QFile config("updater.conf");
    if(!config.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text)) {
        msgOut << "Unable to write config file, do you have writing permission?." << endl;
        return;
    }
    QTextStream confout(&config);
    QString mods;
    foreach (QString m, SavedData->modlist) {
        mods = mods + ',' + m;
    }
    confout << "version=" << SavedData->version << endl << "modlist=" << mods << endl << "modserverurl=" << SavedData->modserverurl;
    msgOut << "Config successfuly written" << endl;
}

void MainWorker::updateAll() {
    msgOut << "Updating everything..." << endl;

    updateGame();
    updateMe();

    //TODO
    msgOut << "Done updating" << endl;
}

void MainWorker::updateGame() {
    //Downloader d("http://qt-project.org/doc/qt-5/qtnetwork-downloadmanager-downloadmanager-pro.html", "list.htm");
    //d.waitForFinished();
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

//Helper
void MainWorker::downloadFinished() {
    msgOut << "test2";
    msgOut.flush();
}

QStringList MainWorker::installedMods(bool console) {
    if(console) {
        //for non-GUI
        foreach (QString mod, SavedData->modlist) {
           msgOut << mod.split("-")[0] << " version " << mod.split("-")[1] << endl;
        }
        return *new QStringList();
    }
    return SavedData->modlist;
}

void MainWorker::runClient() {
    writeClientExecutable();
#ifdef Q_OS_WIN32
    QProcess p;
    p.start("Client.bat");
    p.waitForFinished(-1);
    return;
#endif
#ifdef Q_OS_UNIX
    QProcess p;
    p.start("./Client.sh");
    p.waitForFinished(-1);
    return;
#endif
    msgOut << "I don't recognize your OS" << endl;
}

void MainWorker::runServer() {
    writeServerExecutable();
#ifdef Q_OS_WIN32
    QProcess p;
    p.start("Server.bat");
    p.waitForFinished(-1);
    return;
#endif
#ifdef Q_OS_UNIX
    QProcess p;
    p.start("./server.sh");
    p.waitForFinished(-1);
    return;
#endif
    msgOut << "I don't recognize your OS" << endl;
}

void MainWorker::help(QString cmd) {
    msgOut << "You need to specify a valid option for the updater" << endl;
    msgOut << "Available options are:" << endl;
    msgOut << "init - Initiates the updater configs" << endl;
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
