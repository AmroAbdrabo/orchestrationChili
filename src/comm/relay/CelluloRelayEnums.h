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
 * @file CelluloRelayEnums.h
 * @brief Header for Cellulo relay enums
 * @author Ayberk Özgür
 * @date 2018-08-30
 */

#ifndef CELLULORELAYENUMS_H
#define CELLULORELAYENUMS_H

#include <QObject>

#include "../../CelluloEnumDecl.h"

namespace Cellulo{

/**
 * @addtogroup comm-relay
 * @{
 */

/**
 * @brief Wrapper containing all the enums for Cellulo relay functionality
 * @singleton
 */
class CelluloRelayEnums : public QObject {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

public:

    /** @cond DO_NOT_DOCUMENT */

    CelluloRelayEnums(QObject* parent = 0);
    ~CelluloRelayEnums();

    /** @endcond */

    /**
     * @brief Relay connection status
     */
    enum ConnectionStatus { \
             /** Idle and not connected     */ ConnectionStatusDisconnected = 0,
             /** Actively trying to connect */ ConnectionStatusConnecting = 1,
             /** Connected                  */ ConnectionStatusConnected = 2,
             ConnectionStatusNumElements \
    };
    Q_ENUM(ConnectionStatus)
    CELLULO_ENUM_DECL(ConnectionStatus)

};

/** @} */

}

Q_DECLARE_METATYPE(Cellulo::CelluloRelayEnums::ConnectionStatus)

#endif // CELLULORELAYENUMS_H
