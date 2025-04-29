#include "LoginCall.h"
# include <sstream>
# include <QNetworkDatagram>
# include <QDebug>
ServerCall::ServerCall(QObject *parent)
      : QObject{parent},  IsLoged{0}
{
      CacheFile.open("Files\\Cache.txt", std::ios::in);
      std::string Buffer{};
      CacheContent.reserve(10);
      for(;std::getline(CacheFile, Buffer);)
      {
            CacheContent.push_back(Buffer);
      }
      if (CacheContent.size() > 2)
      {
            IsLoged = 1;
      }      
      CacheFile.close();      
}

void ServerCall::WriteCache(std::string &ToWrite)
{
      CacheFile.open("Files\\Cache.txt", std::ios::out);
      CacheFile << ToWrite;
      CacheFile.close();
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
      std::string Response{Datagram.data().toStdString()};
      if ((Response[0]-48) == 1)
      {
            WriteCache(Response);
      }
      MainSocket.close();
      return int(Response[0]) - 48;
}
