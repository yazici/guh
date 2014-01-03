#include "action.h"

Action::Action(const QUuid &deviceId, const QUuid &id) :
    m_id(id),
    m_deviceId(deviceId)
{
}

bool Action::isValid() const
{
    return !m_id.isNull();
}

QUuid Action::id() const
{
    return m_id;
}

QUuid Action::deviceId() const
{
    return m_deviceId;
}

QString Action::name() const
{
    return m_name;
}

void Action::setName(const QString &name)
{
    m_name = name;
}

QVariantMap Action::params() const
{
    return m_params;
}

void Action::setParams(const QVariantMap &params)
{
    m_params = params;
}
