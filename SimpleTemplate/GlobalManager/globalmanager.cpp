#include "GlobalManager.h"

// 单例获取
GlobalManager& GlobalManager::instance()
{
    static GlobalManager inst;
    return inst;
}

// 设置变量
void GlobalManager::setVar(const QString& key, const QVariant& value)
{
    vars[key] = value;
}

// 获取变量
QVariant GlobalManager::getVar(const QString& key) const
{
    return vars.value(key, QVariant());
}

// 删除变量
void GlobalManager::removeVar(const QString& key)
{
    vars.remove(key);
}

// 检查变量是否存在
bool GlobalManager::hasVar(const QString& key) const
{
    return vars.contains(key);
}

// 打印所有变量
void GlobalManager::printAll() const
{
    qDebug() << "Global variables:";
    for (auto it = vars.begin(); it != vars.end(); ++it) {
        qDebug() << it.key() << "=" << it.value();
    }
}
