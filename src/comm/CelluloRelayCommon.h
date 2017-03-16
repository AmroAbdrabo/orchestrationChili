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
 * @file CelluloRelayCommon.h
 * @brief Common objects used by Cellulo Relay objects
 * @author Ayberk Özgür
 * @date 2017-03-15
 */

#ifndef CELLULORELAYCOMMON_H
#define CELLULORELAYCOMMON_H

#include <QString>

class CelluloRelayCommon{

public:

    static const int DEFAULT_RELAY_PORT = 2556;         ///< Default TCP port for Cellulo relay communication
    static const QString DEFAULT_ROBOT_MAC_ADDR_PREFIX; ///< Default prefix of Cellulo robot MAC addresses

    /**
     * @brief Underlying transfer protocols supported by the relay servers and clients
     */
    enum class Protocol{
        Local = 0,   ///< Unix domain socket
        Tcp          ///< TCP socket
    };
};

#endif // CELLULORELAYCOMMON_H
