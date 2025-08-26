#include "ServerCall.h"
# include <sstream>
# include <QNetworkDatagram>
# include <QDebug>
# include <QByteArray>
# include <QtNetwork/QUdpSocket>
# include <qudpsocket.h>
bool ServerCall::getIsLoged() const
{
      return IsLoged;
}

void ServerCall::setIsLoged(bool newIsLoged)
{
      if (IsLoged == newIsLoged)
            return;
      IsLoged = newIsLoged;
      emit IsLogedChanged();
}

ServerCall::ServerCall(QObject *parent)
      : QObject{parent},  IsLoged{0}
{
      CacheFile.open("Files/Cache.txt", std::ios::in);
      std::string Buffer{};
      CacheContent.reserve(10);
      for(;std::getline(CacheFile, Buffer, '\n');)
      {
            CacheContent.push_back(Buffer);
      }
      if (CacheContent.size() > 1)
      {
            IsLoged = 1;            
      }
      else
      {
            IsLoged = 0;
      }
      CacheFile.close();      
}

void ServerCall::WriteCache(const std::string &ToWrite)
{
      CacheFile.open("Files/Cache.txt", std::ios::out);
      CacheFile << ToWrite;
      CacheFile.close();
}


signed int ServerCall::_LoginInto(const QString &Login, const QString &Password)
{
      MainSocket.bind(QHostAddress::LocalHost, 33333);
      std::stringstream Request;
      qDebug() << Login << Password;
      Request << "l\n" << Login.toStdString() << ' ' << Password.toStdString();
      MainSocket.writeDatagram(Request.str().c_str(), QHostAddress(QHostAddress::LocalHost), 32323);
      MainSocket.waitForBytesWritten();
      MainSocket.waitForReadyRead();
      QNetworkDatagram Datagram {MainSocket.receiveDatagram()};
      MainSocket.close();
      std::string Response{Datagram.data().toStdString()};
      if ((Response[0]-48) == 1)
      {
            WriteCache(Response);
            return 1;
      }
      else if (Response.empty())
      {
            return -1;
      }
      return 0;
}
