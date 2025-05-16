#include "backgroundmanager.h"
#include <QFileInfo>
#include <QDebug>

BackgroundManager::BackgroundManager(QObject *parent)
    : QObject(parent)
{
    // Set the path to the backgrounds directory
    m_backgroundsPath = "D:/SideProjects/CanvasExperiment/assets/backgrounds";
    qDebug() << "BackgroundManager: Initializing with path:" << m_backgroundsPath;
    loadBackgroundFiles();
}

QStringList BackgroundManager::backgroundFiles() const
{
    qDebug() << "BackgroundManager: Getting background files:" << m_backgroundFiles;
    return m_backgroundFiles;
}

QString BackgroundManager::getFullPath(const QString &filename) const
{
    QString fullPath = "file:///" + m_backgroundsPath + "/" + filename;
    qDebug() << "BackgroundManager: Getting full path:" << fullPath;
    return fullPath;
}

void BackgroundManager::loadBackgroundFiles()
{
    QDir dir(m_backgroundsPath);
    QStringList filters;
    filters << "*.mp4" << "*.avi" << "*.mkv" << "*.mov";  // Add more video formats if needed
    
    m_backgroundFiles = dir.entryList(filters, QDir::Files);
    qDebug() << "BackgroundManager: Loaded background files:" << m_backgroundFiles;
    emit backgroundFilesChanged();
} 