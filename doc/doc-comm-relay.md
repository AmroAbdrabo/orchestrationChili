# group `comm-relay` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Cellulo::CelluloLocalRelayClient`](doc/doc-comm-relay.md#classCellulo_1_1CelluloLocalRelayClient) | Relays packets between a server and virtual robot objects over a Unix domain socket. Connects to a `[CelluloLocalRelayServer](doc/doc-comm-relay.md#classCellulo_1_1CelluloLocalRelayServer)`.
`class `[`Cellulo::CelluloLocalRelayServer`](doc/doc-comm-relay.md#classCellulo_1_1CelluloLocalRelayServer) | Relays packets between a client and physical robots over a Unix domain socket. Accepts connections from a `[CelluloLocalRelayClient](doc/doc-comm-relay.md#classCellulo_1_1CelluloLocalRelayClient)`.
`class `[`Cellulo::CelluloRelayClient`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient) | Object that relays packets between a `[CelluloRelayServer](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer)` and virtual robot objects.
`class `[`Cellulo::CelluloRelayServer`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer) | Object that relays packets between a `[CelluloRelayClient](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient)` and physical robots.
`class `[`Cellulo::CelluloRobotPoolClient`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRobotPoolClient) | Object that uses the robots connected to a `cellulorobotpoold`.
`class `[`Cellulo::CelluloTcpRelayClient`](doc/doc-comm-relay.md#classCellulo_1_1CelluloTcpRelayClient) | Relays packets between a server and virtual robot objects over a TCP socket. Connects to a `[CelluloTcpRelayServer](doc/doc-comm-relay.md#classCellulo_1_1CelluloTcpRelayServer)`.
`class `[`Cellulo::CelluloTcpRelayServer`](doc/doc-comm-relay.md#classCellulo_1_1CelluloTcpRelayServer) | Relays packets between a client and physical robots over a TCP socket. Accepts connections from a `[CelluloTcpRelayClient](doc/doc-comm-relay.md#classCellulo_1_1CelluloTcpRelayClient)`.

# class `Cellulo::CelluloLocalRelayClient` 

```
class Cellulo::CelluloLocalRelayClient
  : public Cellulo::CelluloRelayClient
```  

Relays packets between a server and virtual robot objects over a Unix domain socket. Connects to a `[CelluloLocalRelayServer](#classCellulo_1_1CelluloLocalRelayServer)`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{slot} public bool `[`cleanSocket`](#classCellulo_1_1CelluloLocalRelayClient_1aa1afa3b89e0d6a0d40bdf8e1629764f1)`()` | Removes the local socket file, i.e calls QLocalServer::removeServer()

## Members

#### `{slot} public bool `[`cleanSocket`](#classCellulo_1_1CelluloLocalRelayClient_1aa1afa3b89e0d6a0d40bdf8e1629764f1)`()` 

Removes the local socket file, i.e calls QLocalServer::removeServer()

#### Returns
Whether the socket file was successfully cleaned

# class `Cellulo::CelluloLocalRelayServer` 

```
class Cellulo::CelluloLocalRelayServer
  : public Cellulo::CelluloRelayServer
```  

Relays packets between a client and physical robots over a Unix domain socket. Accepts connections from a `[CelluloLocalRelayClient](#classCellulo_1_1CelluloLocalRelayClient)`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{slot} public bool `[`cleanSocket`](#classCellulo_1_1CelluloLocalRelayServer_1a08701a8f3a2a115665f46087f6347510)`()` | Removes the local socket file, i.e calls QLocalServer::removeServer()

## Members

#### `{slot} public bool `[`cleanSocket`](#classCellulo_1_1CelluloLocalRelayServer_1a08701a8f3a2a115665f46087f6347510)`()` 

Removes the local socket file, i.e calls QLocalServer::removeServer()

#### Returns
Whether the socket file was successfully cleaned

# class `Cellulo::CelluloRelayClient` 

```
class Cellulo::CelluloRelayClient
  : public QQuickItem
```  

Object that relays packets between a `[CelluloRelayServer](#classCellulo_1_1CelluloRelayServer)` and virtual robot objects.

The robots that are connected to this object (i.e having their relay client set as this object) have all their commands routed to the `[CelluloRelayServer](#classCellulo_1_1CelluloRelayServer)` that is connected to this client, effectively making the `[CelluloBluetooth](#classCellulo_1_1CelluloBluetooth)`s under control of this client to become virtual robots that represent the physical robots connected to the server side.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} bool `[`connected`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1a8425b7761ae0c840c8e34dc741c162f0) | Whether currently connected to the server, read-only.
`{property} QString `[`serverAddress`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1a61a164f2a1ff8077854253ccade0ebfa) | Address to connect to, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")
`{property} int `[`port`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1a6bf83800ed227b6c5e2e33f1de5d0702) | Port to connect to in TCP (default is 2556), unused in local sockets.
`{property} int `[`autoConnect`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1ac03d0024c5c1656d1e6308b8461e3190) | Whether to try to reconnect when the connection drops or in the beginning, default is true.
`{property} QVariantList `[`robots`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1ae88af0add6b8a6ecfa0e04ee5d34a53c) | List of virtual robots currently under control of this client, read-only.
`{signal} public void `[`connected`](#classCellulo_1_1CelluloRelayClient_1a7d5937c7d07a5a07f471f4e956a0b9a4)`()` | Emitted when the server socket is connected.
`{signal} public void `[`disconnected`](#classCellulo_1_1CelluloRelayClient_1a10cfb3ae0feb9843741af7cfa4125196)`()` | Emitted when the server socket is disconected.
`{signal} public void `[`unknownRobotAtServer`](#classCellulo_1_1CelluloRelayClient_1a8744b4de8ab1164e8b4e1659f56281ff)`(QString macAddr)` | Emitted when the server has a robot already connected that is not in the robots list covered by this client.
`{slot} public void `[`connectToServer`](#classCellulo_1_1CelluloRelayClient_1a53b79491108537bf602cadfe75fc026f)`()` | Initiates a connection to the service on the server.
`{slot} public void `[`disconnectFromServer`](#classCellulo_1_1CelluloRelayClient_1a70b239ca558b93c6993ba92b0d6f6649)`()` | Starts closing the socket.
`{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayClient_1a1180cd38870c8856aef7b816db9a47c3)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot,bool select)` | Adds the robot to the robots list, sets the robot's relay client to this object.
`{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayClient_1a7eccd090383468345b0de682ca98368a)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` | Removes the robot from the robots list.

## Members

#### `{property} bool `[`connected`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1a8425b7761ae0c840c8e34dc741c162f0) 

Whether currently connected to the server, read-only.

#### `{property} QString `[`serverAddress`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1a61a164f2a1ff8077854253ccade0ebfa) 

Address to connect to, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")

Server's address, e.g "127.0.0.1".

#### `{property} int `[`port`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1a6bf83800ed227b6c5e2e33f1de5d0702) 

Port to connect to in TCP (default is 2556), unused in local sockets.

#### `{property} int `[`autoConnect`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1ac03d0024c5c1656d1e6308b8461e3190) 

Whether to try to reconnect when the connection drops or in the beginning, default is true.

#### `{property} QVariantList `[`robots`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayClient_1ae88af0add6b8a6ecfa0e04ee5d34a53c) 

List of virtual robots currently under control of this client, read-only.

#### `{signal} public void `[`connected`](#classCellulo_1_1CelluloRelayClient_1a7d5937c7d07a5a07f471f4e956a0b9a4)`()` 

Emitted when the server socket is connected.

#### `{signal} public void `[`disconnected`](#classCellulo_1_1CelluloRelayClient_1a10cfb3ae0feb9843741af7cfa4125196)`()` 

Emitted when the server socket is disconected.

#### `{signal} public void `[`unknownRobotAtServer`](#classCellulo_1_1CelluloRelayClient_1a8744b4de8ab1164e8b4e1659f56281ff)`(QString macAddr)` 

Emitted when the server has a robot already connected that is not in the robots list covered by this client.

#### Parameters
* `macAddr` MAC address of the unknown robot

#### `{slot} public void `[`connectToServer`](#classCellulo_1_1CelluloRelayClient_1a53b79491108537bf602cadfe75fc026f)`()` 

Initiates a connection to the service on the server.

#### `{slot} public void `[`disconnectFromServer`](#classCellulo_1_1CelluloRelayClient_1a70b239ca558b93c6993ba92b0d6f6649)`()` 

Starts closing the socket.

#### `{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayClient_1a1180cd38870c8856aef7b816db9a47c3)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot,bool select)` 

Adds the robot to the robots list, sets the robot's relay client to this object.

#### Parameters
* `robot` New robot 

* `select` Selects the newly added robot as current; pass true if robot is added as a result of an [unknownRobotAtServer()](#classCellulo_1_1CelluloRelayClient_1a8744b4de8ab1164e8b4e1659f56281ff) signal

#### `{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayClient_1a7eccd090383468345b0de682ca98368a)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Robot to remove

# class `Cellulo::CelluloRelayServer` 

```
class Cellulo::CelluloRelayServer
  : public QQuickItem
```  

Object that relays packets between a `[CelluloRelayClient](#classCellulo_1_1CelluloRelayClient)` and physical robots.

The robots that are connected to this object (i.e having their relay server set as this object) have all their events routed to the `[CelluloRelayClient](#classCellulo_1_1CelluloRelayClient)` that is connected to this server. Does not listen for incoming connections from a client upon creation, must be enabled explicitly.

This class is **abstract**, you cannot instantiate it directly. Refer to classes derived from it.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QString `[`address`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer_1ac4e8d3e0f576133076f78c24e283a8fe) | Host address, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")
`{property} int `[`port`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer_1aa6697416fd80d8f80bb3c9c6eba60535) | Port to listen to in TCP (default is 2556), unused in local sockets.
`{property} bool `[`listen`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer_1a501f390e6c5c9c88e92c8dee8550e14f) | Whether to listen to incoming connections, disabled on construction.
`{signal} public void `[`listenError`](#classCellulo_1_1CelluloRelayServer_1af2e77447b8d331edcd1156cc378ecb43)`()` | Emitted when listening fails.
`{signal} public void `[`clientConnected`](#classCellulo_1_1CelluloRelayServer_1a0c177f69d6a00e9c46627a6350c2d2b0)`()` | Emitted when a new client connects.
`{signal} public void `[`clientDisconnected`](#classCellulo_1_1CelluloRelayServer_1a131a26e03a7f7bfd03cd63c196092be6)`()` | Emitted when the client disconnects.
`{signal} public void `[`robotAdded`](#classCellulo_1_1CelluloRelayServer_1a6f4ac79e3ce85bdf24ba05f1b71495ba)`(QString macAddr)` | Emitted when a new robot is added to the server.
`{signal} public void `[`robotRemoved`](#classCellulo_1_1CelluloRelayServer_1ac9a0a3c6db06a0e11b6f01910774295f)`(QString macAddr)` | Emitted when a robot is removed from the server.
`{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayServer_1aec94e96d4af0384e275266a423b65fe1)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` | Adds robot to the robots list, sets the robot's relay server to this object.
`{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayServer_1a2d3f4984486ccfd6f775071138fd94b2)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` | Removes the robot from the robots list.
`{slot} public void `[`disconnectClient`](#classCellulo_1_1CelluloRelayServer_1af945c9a03a454a34dad636fa8f3eda1f)`()` | Closes the client's socket.

## Members

#### `{property} QString `[`address`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer_1ac4e8d3e0f576133076f78c24e283a8fe) 

Host address, i.e name of the domain socket (default is "cellulo_relay") or the IP address of the TCP socket (default is "localhost")

Host address, e.g "127.0.0.1" for TCP.

#### `{property} int `[`port`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer_1aa6697416fd80d8f80bb3c9c6eba60535) 

Port to listen to in TCP (default is 2556), unused in local sockets.

#### `{property} bool `[`listen`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRelayServer_1a501f390e6c5c9c88e92c8dee8550e14f) 

Whether to listen to incoming connections, disabled on construction.

#### `{signal} public void `[`listenError`](#classCellulo_1_1CelluloRelayServer_1af2e77447b8d331edcd1156cc378ecb43)`()` 

Emitted when listening fails.

#### `{signal} public void `[`clientConnected`](#classCellulo_1_1CelluloRelayServer_1a0c177f69d6a00e9c46627a6350c2d2b0)`()` 

Emitted when a new client connects.

#### `{signal} public void `[`clientDisconnected`](#classCellulo_1_1CelluloRelayServer_1a131a26e03a7f7bfd03cd63c196092be6)`()` 

Emitted when the client disconnects.

#### `{signal} public void `[`robotAdded`](#classCellulo_1_1CelluloRelayServer_1a6f4ac79e3ce85bdf24ba05f1b71495ba)`(QString macAddr)` 

Emitted when a new robot is added to the server.

#### Parameters
* `macAddr` MAC address of the added robot

#### `{signal} public void `[`robotRemoved`](#classCellulo_1_1CelluloRelayServer_1ac9a0a3c6db06a0e11b6f01910774295f)`(QString macAddr)` 

Emitted when a robot is removed from the server.

#### Parameters
* `macAddr` MAC address of the removed robot

#### `{slot} public void `[`addRobot`](#classCellulo_1_1CelluloRelayServer_1aec94e96d4af0384e275266a423b65fe1)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` 

Adds robot to the robots list, sets the robot's relay server to this object.

#### Parameters
* `robot` New robot

#### `{slot} public void `[`removeRobot`](#classCellulo_1_1CelluloRelayServer_1a2d3f4984486ccfd6f775071138fd94b2)`(`[`Cellulo::CelluloBluetooth`](#classCellulo_1_1CelluloBluetooth)` * robot)` 

Removes the robot from the robots list.

#### Parameters
* `robot` Existing robot

#### `{slot} public void `[`disconnectClient`](#classCellulo_1_1CelluloRelayServer_1af945c9a03a454a34dad636fa8f3eda1f)`()` 

Closes the client's socket.

# class `Cellulo::CelluloRobotPoolClient` 

```
class Cellulo::CelluloRobotPoolClient
  : public Cellulo::CelluloLocalRelayClient
```  

Object that uses the robots connected to a `cellulorobotpoold`.

Inherits from `[CelluloLocalRelayClient](#classCellulo_1_1CelluloLocalRelayClient)`, which in turn inherits from `[CelluloRelayClient](#classCellulo_1_1CelluloRelayClient)`, which means that their properties, signals and slots can be used. The most useful among these is the `robots` property that exposes the list of currently available robots in this pool.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`{property} QJSValue `[`createRobot`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRobotPoolClient_1a54e7e3a28f5ca7902b2834f836e1b6f2) | Must be set to a user-defined javascript function that takes the MAC address (string) of an already connected robot and returns a [CelluloBluetooth](doc/doc-comm.md#classCellulo_1_1CelluloBluetooth) object or CelluloBluetooth-derived object.

## Members

#### `{property} QJSValue `[`createRobot`](doc/doc-comm-relay.md#classCellulo_1_1CelluloRobotPoolClient_1a54e7e3a28f5ca7902b2834f836e1b6f2) 

Must be set to a user-defined javascript function that takes the MAC address (string) of an already connected robot and returns a [CelluloBluetooth](#classCellulo_1_1CelluloBluetooth) object or CelluloBluetooth-derived object.

# class `Cellulo::CelluloTcpRelayClient` 

```
class Cellulo::CelluloTcpRelayClient
  : public Cellulo::CelluloRelayClient
```  

Relays packets between a server and virtual robot objects over a TCP socket. Connects to a `[CelluloTcpRelayServer](#classCellulo_1_1CelluloTcpRelayServer)`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

# class `Cellulo::CelluloTcpRelayServer` 

```
class Cellulo::CelluloTcpRelayServer
  : public Cellulo::CelluloRelayServer
```  

Relays packets between a client and physical robots over a TCP socket. Accepts connections from a `[CelluloTcpRelayClient](#classCellulo_1_1CelluloTcpRelayClient)`.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

## Members

