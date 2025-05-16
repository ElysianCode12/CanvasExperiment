#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include <QObject>
#include <QDir>
#include <QStringList>

class BackgroundManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList backgroundFiles READ backgroundFiles NOTIFY backgroundFilesChanged)

public:
    explicit BackgroundManager(QObject *parent = nullptr);

    QStringList backgroundFiles() const;
    Q_INVOKABLE QString getFullPath(const QString &filename) const;

private:
    QStringList m_backgroundFiles;
    QString m_backgroundsPath;

    void loadBackgroundFiles();

signals:
    void backgroundFilesChanged();
};

#endif // BACKGROUNDMANAGER_H 