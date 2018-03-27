/*
 * Copyright (C) 2017 EPFL
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

#include <QCoreApplication>
#if defined(Q_OS_ANDROID)
    #include <QAndroidJniObject>
    #include <QtAndroid>
#endif

#include <CelluloTcpRelayServer.h>
#include <CelluloTcpRelayClient.h>
#include <CelluloLocalRelayServer.h>
#include <CelluloLocalRelayClient.h>

using namespace Cellulo;

int main(int argc, char** argv){
    QCoreApplication app(argc, argv);


    if (QCoreApplication::arguments().count() > 1){
        qDebug() << "I am the service";
        qInfo() << "Starting...";



        qDebug() << "CELLULO SERVICE LAUNCHED";
    }
    else{
        qDebug() << "I am the app";
        qDebug() << "CELLULO APP LAUNCHED";

        /*QAndroidJniObject::callStaticMethod<void>(
                    "ch/epfl/chili/cellulo/cellulorobotpoold/CelluloRobotPoolService",
                    "startCelluloRobotPoolService",
                    "(Landroid/content/Context;)V",
                    QtAndroid::androidActivity().object()
                );*/

        CelluloLocalRelayServer server;
        server.setListening(true);

        //CelluloLocalRelayClient client;
        //client.connectToServer();


    }

    return app.exec();
}
