#include <QGuiApplication>
#include <QQmlApplicationEngine>
# include <QtNetwork>
# include "SocketCall.h"
# include "Searcher.h"
# include "Schedule.hpp"
# include "LoginCall.h"
# include "SubjectSystem.hpp"
# include "Reseter.hpp"
# include "AttendanceSystem.hpp"
int main(int argc, char *argv[])
{
      QGuiApplication app(argc, argv);

      // QNetworkAccessManager *manager = new QNetworkAccessManager();
      // QNetworkRequest request;
      // request.setUrl(QUrl("https://mirea.xyz/api/v1.3/groups/all"));

      // QNetworkReply *reply = manager->get(request);
      // QEventLoop loop;
      // QAbstractSocket::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
      // loop.exec();
      // qDebug() << reply->readAll(); //debug
      qmlRegisterType<SocketCall>("com.SocketCall", 1, 0, "Socket");
      qmlRegisterType<Searcher>("com.Searcher", 1, 0, "Searcher");
      qmlRegisterType<Schedule>("com.Schedule", 1, 0, "Schedule");
      qmlRegisterType<ServerCall>("com.ServerCall", 1, 0, "ServerCall");
      qmlRegisterType<DaysContentStruct>("ScheduleStruct", 1, 0, "ScheduleStruct");
      qmlRegisterType<SubjectSystem>("com.SubjectSystem", 1, 0, "SubjectSystem");
      qmlRegisterType<Reseter>("com.Reseter", 1, 0, "Reseter");
      qmlRegisterType<AttendanceSystem>("com.Attendance", 1, 0, "Attendance");
      QQmlApplicationEngine engine;

      const QUrl url(QStringLiteral("qrc:/MireaApp/qml/Main.qml"));
      QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreationFailed,
            &app,
            []() { QCoreApplication::exit(-1); },
            Qt::QueuedConnection);
      engine.load(url);

      return app.exec();
}
