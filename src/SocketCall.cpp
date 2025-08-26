#include "SocketCall.h"

QString SocketCall::getReply() const
{
      return Reply;
}

void SocketCall::setReply(const QString &newReply)
{

      emit ReplyChanged();
}

bool SocketCall::_Call(const QString &aLogin, const QString &aPassword)
{
      if (aLogin == "" || aPassword == "")
      {
            return false;
      }
      if (Ip == "000000000000")
      {
            qDebug() << "Fake ip";
            return true;
      }
      if (Ip.size() < 5)
      {
            Ip = "192.168.1.123";
      }
      MainSocket.connectToHost(Ip, 32323);
      qDebug() << MainSocket.state();
      MainSocket.waitForConnected();
      qDebug() << MainSocket.state();
      QString Request{"l\n" + aLogin + ' '+ aPassword};

      MainSocket.write(Request.toStdString().c_str());
      MainSocket.read(1);
      QEventLoop loop;
      QAbstractSocket::connect(&MainSocket, SIGNAL(disconnected()), &loop, SLOT(quit()));
      loop.exec();
      qDebug() << MainSocket.read(1).toStdString();
      Reply = MainSocket.read(1);
      if (Reply.toStdString().compare("1"))
      {
            qDebug() << "Enter succ";
            emit ReplyChanged();
            return true;
      }
      else
      {
            qDebug() << "Not succ";
            emit ReplyChanged();
            return false;
      }
      emit ReplyChanged();
      return false;
}

void SocketCall::_CheckForIp(const QString &NewIp)
{
      if (NewIp == "000000000000")
      {
            Ip = NewIp;
      }
      if (NewIp.size() < 10)
      {
            qDebug() << "No ip";
            return;
      }
      else
      {
            qDebug() << "Ip is nice";
            Ip = NewIp;
      }
}

SocketCall::SocketCall(QObject *parent)
      : QObject{parent}
{}
