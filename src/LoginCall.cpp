#include "LoginCall.h"
# include <sstream>
# include <QNetworkDatagram>
# include <QDebug>
# include <QByteArray>
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

QString ServerCall::getUsername() const
{
      return Username;
}

void ServerCall::setUsername(const QString &newUsername)
{
      if (Username == newUsername)
            return;
      Username = newUsername;
      emit UsernameChanged();
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
      if (CacheContent.size() > 2)
      {
            IsLoged = 1;
            std::stringstream FullName{CacheContent[1]};
            for (size_t Index{0};std::getline(FullName, Buffer, ' ');++Index)
            {
                  if (Index == 0)
                  {
                        Username += Buffer + ' ';
                  }
                  else
                  {
                        QString Wtf{QString::fromUtf8(Buffer)};
                        Username += Wtf[0] + '.';
                  }
            }

      }
      else
      {
            IsLoged = 0;
      }
      CacheFile.close();      
}

void ServerCall::WriteCache(std::string &ToWrite)
{
      CacheFile.open("Files/Cache.txt", std::ios::out);
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
      MainSocket.close();
      std::string Response{Datagram.data().toStdString()};
      if ((Response[0]-48) == 1)
      {
            WriteCache(Response);
            return 1;
      }
      return 0;
}
