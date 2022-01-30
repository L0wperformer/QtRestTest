#include "device.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QQuickView>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

  QCoreApplication::setApplicationName("QtRestTest");
  QCoreApplication::setOrganizationName("UseAtOwnRisk");

  device a;
  auto *view = new QQuickView();


  view->rootContext()->setContextProperty("device", &a);
  view->setSource(QUrl("qrc:main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->show();
  return app.exec();
}
