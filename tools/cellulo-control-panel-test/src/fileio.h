#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>

class FileIO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

public:
    /**
     * @brief FileIO constructor
     * @param parent
     */
    explicit FileIO(QObject *parent = 0);

    /**
     * @brief prints content of mdata
     */
    Q_INVOKABLE void print(); //print contents of mdata
    /**
     * @brief parses csv data into attribute mdata, MUST CALL THIS FUNCTION TO INITIALIZE mdata
     */
    Q_INVOKABLE void parseData(); //parse data into mdata //MUST CALL BEFORE ANYTHING ELSE
   // Q_INVOKABLE QString readLine();
    /**
     * @brief returns QString with contents of file in mSource
     * @return
     */
    Q_INVOKABLE QString read();
    /**
     * @brief overwrittes contents of mSource with given data
     * @param data
     * @return
     */
    Q_INVOKABLE bool write(const QString& data);

    QString source() { return mSource; };

public slots:
    void setSource(const QString& source) { mSource = source; };

signals:
    void sourceChanged(const QString& source);
    void error(const QString& msg);

private:
    QList<QStringList> mdata; ///<buffer the data so can then read it line by line
    QString mSource;          ///< contains path to source file
};

#endif // FILEIO_H
