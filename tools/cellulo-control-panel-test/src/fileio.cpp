#include "fileio.h"
#include <QFile>
#include <QTextStream>
#include "qdebug.h"

FileIO::FileIO(QObject *parent) : QObject(parent)
{

}

QString FileIO::read()
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QString();
    }

    QFile file(mSource);
    QString fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        do {
            line = t.readLine();
            fileContent += line;
         } while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return QString();
    }
    return fileContent;
}

void FileIO::parseData()
{
    // Open csv-file
    QFile file(mSource);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Read data from file
    QTextStream stream(&file);
    QList<QStringList> data;
    QString separator(",");
    while (stream.atEnd() == false)
    {
        QString line = stream.readLine();
        data << line.split(separator);
    }

    file.close();
    mdata = data; //set data
    print();
    //return data;  //TODO can probably remove this

}

void FileIO::print()
{
    qDebug() << "first line : " << mdata.at(0);
    for (int i = 0; i < mdata.size(); ++i)
    {
        qDebug() << mdata.at(i).join(", ");
    }
}

bool FileIO::write(const QString& data)
{
    if (mSource.isEmpty())
        return false;

    QFile file(mSource);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}
