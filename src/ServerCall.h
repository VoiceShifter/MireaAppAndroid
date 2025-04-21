#ifndef SERVERCALL_H
#define SERVERCALL_H

# include <QObject>
# include <QtNetwork/QUdpSocket>
# include <QString>
# include <fstream>
# include <vector>
# include <string>

class ServerCall : public QObject
{
      Q_OBJECT
      QUdpSocket MainSocket;
      std::fstream CacheFile;
      std::vector<std::string> CacheContent;
      bool IsLoged;
  public:
      ServerCall(QObject *parent = nullptr);
      Q_INVOKABLE bool _LoginInto(const QString& Login, const QString& Password); //debug Change from local Ip
};

#endif // SERVERCALL_H
