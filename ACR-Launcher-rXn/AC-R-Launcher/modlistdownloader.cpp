#include "modlistdownloader.h"

ModListDownloader::ModListDownloader(QString url, ConfigData *data) : QObject()
{
    qna = new QNetworkAccessManager();
    qnreq = new QNetworkRequest(QUrl(url));
    qna->get(*qnreq);
    qna->connect(qna, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseModList(QNetworkReply*)));
    this->data = data;
}

QNetworkReply *ModListDownloader::getData() {
    return result;
}

//The interesting part
void ModListDownloader::parseModList(QNetworkReply *list) {
    bool mod_started = false;
    bool somethingDone = false;
    ModEntry tmp;
    QString currentLine = list->readLine();
    QString keywords = "start_mod modname modversion moddesc modurl end_mod";
    while(!list->atEnd()) {
        currentLine = currentLine.trimmed();
        somethingDone = false;

        //Are we inside a mod def?
        if(currentLine.contains("#start_mod", Qt::CaseInsensitive)) {
            somethingDone = true;
            tmp.clear();
            currentLine = list->readLine();
            mod_started = true;
            continue;
        } else {
            //Getting the infos
            if(!currentLine.split("=")[0].compare("#mod_name", Qt::CaseInsensitive)) {
                somethingDone = true;
                currentLine = currentLine.trimmed();
                tmp.Name = currentLine.split("=")[1];
                currentLine = list->readLine();
                while(!keywords.contains(currentLine.split("=")[0], Qt::CaseInsensitive) && !currentLine.contains("#")) {
                    tmp.Name = tmp.Name + currentLine;
                    currentLine = list->readLine();
                }
            }
            if(!currentLine.split("=")[0].compare("#mod_version", Qt::CaseInsensitive)) {
                somethingDone = true;
                currentLine = currentLine.trimmed();
                tmp.Version = currentLine.split("=")[1];
                currentLine = list->readLine();
                while(!keywords.contains(currentLine.split("=")[0], Qt::CaseInsensitive) && !currentLine.contains("#")) {
                    tmp.Version = tmp.Version + currentLine;
                    currentLine = list->readLine();
                }
            }
            if(!currentLine.split("=")[0].compare("#mod_desc", Qt::CaseInsensitive)) {
                somethingDone = true;
                currentLine = currentLine.trimmed();
                tmp.Description = currentLine.split("=")[1];
                currentLine = list->readLine();
                while(!keywords.contains(currentLine.split("=")[0], Qt::CaseInsensitive) && !currentLine.contains("#")) {
                    tmp.Description = tmp.Description + currentLine;
                    currentLine = list->readLine();
                }
            }
            if(!currentLine.split("=")[0].compare("#mod_url", Qt::CaseInsensitive)) {
                somethingDone = true;
                currentLine = currentLine.trimmed();
                tmp.Url = currentLine.split("=")[1];
                currentLine = list->readLine();
                while(!keywords.contains(currentLine.split("=")[0], Qt::CaseInsensitive) && !currentLine.contains("#")) {
                    tmp.Url = tmp.Url + currentLine;
                    currentLine = list->readLine();
                }
            }
            if(!currentLine.split("=")[0].compare("#mod_author", Qt::CaseInsensitive)) {
                somethingDone = true;
                currentLine = currentLine.trimmed();
                tmp.Author = currentLine.split("=")[1];
                currentLine = list->readLine();
                while(!keywords.contains(currentLine.split("=")[0], Qt::CaseInsensitive) && !currentLine.contains("#")) {
                    tmp.Author = tmp.Author + currentLine;
                    currentLine = list->readLine();
                }
            }
            if(currentLine.contains("#end_mod", Qt::CaseInsensitive)) {
                somethingDone = true;
                data->addToAvailableMods(tmp);
                mod_started = false;
                currentLine = list->readLine();
            }

            //If nothing was done (empty line, whatever), read the next line.
            if(!somethingDone) {
                currentLine = list->readLine();
            }
        }

    }

    emit isReady();

}
