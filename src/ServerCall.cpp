#include "ServerCall.h"
# include <sstream>
# include <QNetworkDatagram>
# include <QDebug>
ServerCall::ServerCall(QObject *parent)
      : QObject{parent}
{
      CacheFile.open("Cache.txt", std::ios::in);
      std::string Buffer{};
      CacheContent.reserve(10);
      for(;std::getline(CacheFile, Buffer);)
      {
            CacheContent.push_back(Buffer);
      }
      if (CacheContent.size() > 0)
      {
            IsLoged = 1;
      }
}

bool ServerCall::_LoginInto(const QString &Login, const QString &Password)
{
      MainSocket.bind(QHostAddress::LocalHost, 33333);
      std::stringstream Request;
      qDebug() << Login << Password;
      Request << "l\n" << Login.toStdString() << ' ' << Password.toStdString();
      MainSocket.writeDatagram(Request.str().c_str(), QHostAddress(QHostAddress::LocalHost), 32323);
      MainSocket.waitForBytesWritten();
      MainSocket.waitForReadyRead();
      QNetworkDatagram Datagram {MainSocket.receiveDatagram()};
      qDebug() << Datagram.data().toStdString()[0];
      return int(Datagram.data().toStdString()[0]) - 48;
}
