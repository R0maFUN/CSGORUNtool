#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>

#include "./ViewModel/MainViewModel.h"
#include "./Model/SettingsModel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    //QCoreApplication::setOrganizationName("RomikAvatar");

    QCoreApplication::setOrganizationName("RomikAvatar");
    QCoreApplication::setApplicationName("RunTool");

    QtWebEngine::initialize();
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/View/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    MainViewModel mainViewModel(&app);
    engine.rootContext()->setContextProperty("viewModel", &mainViewModel);

    engine.load(url);

    return app.exec();
}
