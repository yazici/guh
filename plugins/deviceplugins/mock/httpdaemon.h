/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  This file is part of guh.                                              *
 *                                                                         *
 *  Guh is free software: you can redistribute it and/or modify            *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 2 of the License.                *
 *                                                                         *
 *  Guh is distributed in the hope that it will be useful,                 *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guh. If not, see <http://www.gnu.org/licenses/>.            *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include "typeutils.h"

#include <QTcpServer>
#include <QUuid>
#include <QDateTime>

class Device;
class DevicePlugin;

class HttpDaemon : public QTcpServer
{
    Q_OBJECT
public:
    HttpDaemon(Device *device, DevicePlugin* parent = 0);

    void incomingConnection(qintptr socket) override;

    void actionExecuted(const ActionTypeId &actionTypeId);

signals:
    void setState(const StateTypeId &stateTypeId, const QVariant &value);
    void triggerEvent(const EventTypeId &eventTypeId);

private slots:
    void readClient();
    void discardClient();

private:
    QString generateHeader();
    QString generateWebPage();

private:
    bool disabled;

    DevicePlugin *m_plugin;
    Device *m_device;

    QList<QPair<ActionTypeId, QDateTime> > m_actionList;
};

#endif // HTTPDAEMON_H
