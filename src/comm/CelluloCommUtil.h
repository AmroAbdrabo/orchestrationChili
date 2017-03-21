/*
 * Copyright (C) 2016 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file CelluloCommUtil.h
 * @brief Common objects used by Cellulo communication objects
 * @author Ayberk Özgür
 * @date 2017-03-15
 */

#ifndef CELLULOCOMMUTIL_H
#define CELLULOCOMMUTIL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDebug>

class CelluloCommUtil : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    CelluloCommUtil(QObject* parent = 0);
    virtual ~CelluloCommUtil();

    static const int DEFAULT_RELAY_PORT = 2556;         ///< Default TCP port for Cellulo relay communication
    static const QString DEFAULT_ROBOT_MAC_ADDR_PREFIX; ///< Default prefix of Cellulo robot MAC addresses

    /**
     * @brief Underlying transfer protocols supported by the relay servers and clients
     */
    enum class RelayProtocol{
        Local = 0,   ///< Unix domain socket
        Tcp          ///< TCP socket
    };

    /**
     * @brief Gets the octets of a given MAC address
     *
     * @param macAddr Bluetooth MAC address in the form of XX:XX:XX:XX:XX:XX
     * @return 6 octets from left to right
     */
    static QList<quint8> getOctets(QString const& macAddr);

    /**
     * @brief Gets the MAC address made of the given octets
     *
     * @param octets 6 octets from left to right
     * @return Bluetooth MAC address in the form of "XX:XX:XX:XX:XX:XX"; returns empty string if octets not valid or the address is 00:00:00:00:00:00
     */
    static QString getMacAddr(QList<quint8> const& octets);

    /**
     * @brief Gets the MAC address suffix made of the last two octets
     *
     * @param fifthOctet Fifth octet
     * @param sixthOctet Sixth octet
     * @return Bluetooth MAC address suffix in the form of "XX:XX"
     */
    static QString getMacAddrSuffix(quint8 fifthOctet, quint8 sixthOctet);

    /**
     * @brief Tests whether cellulorobotpoold is installed
     *
     * @return Whether cellulorobotpoold is installed
     */
    Q_INVOKABLE static bool testRobotPoolDaemon();

    /**
     * @brief Attempts to launch a cellulorobotpoold
     *
     * @return Whether successfully launched
     */
    Q_INVOKABLE static bool startRobotPoolDaemon();

    /**
     * @brief Attempts to stop the already existing cellulorobotpoold
     *
     * @return Whether successfully stopped
     */
    Q_INVOKABLE static bool stopRobotPoolDaemon();

};

#endif // CELLULOCOMMUTIL_H
