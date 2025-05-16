#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "videoplayer.h"
#include "backgroundmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    qmlRegisterType<VideoPlayer>("VideoPlayer", 1, 0, "VideoPlayer");
    qmlRegisterType<BackgroundManager>("BackgroundManager", 1, 0, "BackgroundManager");
    
    QQmlApplicationEngine engine;

    // Create and register the BackgroundManager
    BackgroundManager backgroundManager;
    engine.rootContext()->setContextProperty("backgroundManager", &backgroundManager);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);
    
    return app.exec();
} 