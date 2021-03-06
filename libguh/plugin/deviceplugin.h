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

#ifndef DEVICEPLUGIN_H
#define DEVICEPLUGIN_H

#include "devicemanager.h"
#include "deviceclass.h"

#include "typeutils.h"
#include "types/event.h"
#include "types/action.h"
#include "types/vendor.h"
#include "types/param.h"

#include <QObject>
#include <QJsonObject>

class DeviceManager;
class Device;

class DevicePlugin: public QObject
{
    Q_OBJECT
public:
    DevicePlugin(QObject *parent = 0);
    virtual ~DevicePlugin();

    virtual void init() {}

    QString pluginName() const;
    PluginId pluginId() const;
    QList<Vendor> supportedVendors() const;
    QList<DeviceClass> supportedDevices() const;

    virtual DeviceManager::HardwareResources requiredHardware() const = 0;

    virtual void startMonitoringAutoDevices();
    virtual DeviceManager::DeviceError discoverDevices(const DeviceClassId &deviceClassId, const ParamList &params);

    virtual DeviceManager::DeviceSetupStatus setupDevice(Device *device);
    virtual void deviceRemoved(Device *device);

    virtual DeviceManager::DeviceSetupStatus confirmPairing(const PairingTransactionId &pairingTransactionId, const DeviceClassId &deviceClassId, const ParamList &params);

    // Hardware input
    virtual void radioData(const QList<int> &rawData) {Q_UNUSED(rawData)}
    virtual void guhTimer() {}

    // Configuration
    virtual QList<ParamType> configurationDescription() const;
    DeviceManager::DeviceError setConfiguration(const ParamList &configuration);
    ParamList configuration() const;
    QVariant configValue(const QString &paramName) const;
    DeviceManager::DeviceError setConfigValue(const QString &paramName, const QVariant &value);

public slots:
    virtual DeviceManager::DeviceError executeAction(Device *device, const Action &action) {
        Q_UNUSED(device) Q_UNUSED(action)
        return DeviceManager::DeviceErrorNoError;
    }

signals:
    void emitEvent(const Event &event);
    void devicesDiscovered(const DeviceClassId &deviceClassId, const QList<DeviceDescriptor> &deviceDescriptors);
    void deviceSetupFinished(Device *device, DeviceManager::DeviceSetupStatus status);
    void pairingFinished(const PairingTransactionId &pairingTransactionId, DeviceManager::DeviceSetupStatus status);
    void actionExecutionFinished(const ActionId &id, DeviceManager::DeviceError status);
    void configValueChanged(const QString &paramName, const QVariant &value);
    void autoDevicesAppeared(const DeviceClassId &deviceClassId, const QList<DeviceDescriptor> &deviceDescriptors);

protected:
    DeviceManager *deviceManager() const;
    QList<Device*> myDevices() const;
    Device* findDeviceByParams(const ParamList &params) const;

    bool transmitData(int delay, QList<int> rawData);

private:
    void initPlugin(const QJsonObject &metaData, DeviceManager *deviceManager);

    QList<ParamType> parseParamTypes(const QJsonArray &array) const;

    DeviceManager *m_deviceManager;

    ParamList m_config;

    QJsonObject m_metaData;

    friend class DeviceManager;
};
Q_DECLARE_INTERFACE(DevicePlugin, "guru.guh.DevicePlugin")

#endif
