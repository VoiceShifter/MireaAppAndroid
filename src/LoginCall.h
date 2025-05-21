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
      QString Username;
  public:
      ServerCall(QObject *parent = nullptr);
      void WriteCache(std::string& ToWrite);
      Q_INVOKABLE bool _LoginInto(const QString& Login, const QString& Password); //debug Change from local Ip

      bool getIsLoged() const;
      void setIsLoged(bool newIsLoged);
      QString getUsername() const;
      void setUsername(const QString &newUsername);

  signals:
      void IsLogedChanged();
      void UsernameChanged();

  private:
      Q_PROPERTY(bool _IsLoged READ getIsLoged WRITE setIsLoged NOTIFY IsLogedChanged FINAL)
      Q_PROPERTY(QString _Username READ getUsername WRITE setUsername NOTIFY UsernameChanged FINAL)
};

#endif // SERVERCALL_H
