#include "fileio.h"
#include <QFile>
#include <QTextStream>
#include "qdebug.h"

FileIO::FileIO(QObject *parent) : QObject(parent)
{
    curr_line = 0;
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
    qDebug() << "first word : " << mdata.at(0).at(0);
    qDebug() << "posey : " << mdata.at(1).at(3);
    qDebug() << "posex : " << mdata.at(1).at(2);  //YAY
     //data is stored like ("2018-06-26 09:22:53.142", "1", "385.2", "177.95", "49.46", "-0.05", "0.09", "-0.03", " EIS001", "4.52", "5")
    /*for (int i = 0; i < mdata.size(); ++i)
    {   //use join to combine all string from 1 line in single string ex:
        //"2018-06-26 09:10:42.188, 1, 406.73, 58.87, 267.22, 0.05, 0.09, -0.03,  EIS001, 3.71, 2"
        qDebug() << mdata.at(i).join(", ");
    }*/
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

void FileIO::nextLine()
{
    curr_line++;
}

QString FileIO::getcurLineVal(FileIO::DataFields field)
{
    if(!mdata.isEmpty()){
      return  mdata.at(curr_line).at((int)field);
    }
    return NULL;
}
