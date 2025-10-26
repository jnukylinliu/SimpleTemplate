#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QString>
#include <QVariant>
#include <QMap>
#include <QDebug>

class GlobalManager
{
public:
    // 获取单例
    static GlobalManager& instance();

    // 设置变量（新增或修改）
    void setVar(const QString& key, const QVariant& value);

    // 获取变量
    QVariant getVar(const QString& key) const;

    // 删除变量
    void removeVar(const QString& key);

    // 检查变量是否存在
    bool hasVar(const QString& key) const;

    // 打印所有变量（调试用）
    void printAll() const;

private:
    GlobalManager() = default;                     // 构造私有化
    ~GlobalManager() = default;
    GlobalManager(const GlobalManager&) = delete; // 禁止拷贝
    GlobalManager& operator=(const GlobalManager&) = delete;

    QMap<QString, QVariant> vars; // 存储全局变量
};

#endif // GLOBALMANAGER_H
