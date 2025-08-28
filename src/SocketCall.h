#ifndef SOCKETCALL_H
#define SOCKETCALL_H

# include <QObject>
# include <QtNetwork>


class SocketCall : public QObject
{
      Q_OBJECT

      QString Reply = "0";
      QTcpSocket MainSocket;
      QString Ip = "";

public:
      explicit SocketCall(QObject *parent = nullptr);

      Q_INVOKABLE bool _Call(const QString& = "", const QString& = "");
      Q_INVOKABLE void _CheckForIp(const QString&);

      QString getReply() const;
      void setReply(const QString &newReply);

signals:
      void ReplyChanged();
private:
      Q_PROPERTY(QString Reply READ getReply WRITE setReply NOTIFY ReplyChanged FINAL)
};

#endif // SOCKETCALL_H
