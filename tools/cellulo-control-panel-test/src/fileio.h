#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    // Qt 4
    #include <QDeclarativeEngine>
#else
    // Qt 5
    #include <QQmlEngine>
#endif

class FileIO : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)


public:
    /**
     * @brief enum to enumrate the columns in the csv file
     */
    enum DataFields
    {
        TIMESTAMP = 0,
        INDEX = 1,
        POSEX = 2,
        POSEY = 3,
        POSETHETA = 4,
        VELOCITYX = 5,
        VELOCITYY = 6,
        ANGULARVEL = 7,
        PARTICIPANTID = 8,
        MINDIST = 9,
        CONFIGID = 10

    };
    Q_ENUMS(DataFields)

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

    /**
     * @brief increments cur_line
     */
    Q_INVOKABLE void nextLine();

    /**
     * @brief prints content of mdata
     */
    Q_INVOKABLE QString getcurLineVal(DataFields field);

    /**
     * @brief set source
     * @return
     */
    QString source() { return mSource; };

public slots:
    void setSource(const QString& source) { mSource = source; };

signals:
    void sourceChanged(const QString& source);
    void error(const QString& msg);

private:
    int curr_line;
    QList<QStringList> mdata; ///<buffer the data so can then read it line by line
    QString mSource;          ///< contains path to source file
};

#endif // FILEIO_H
