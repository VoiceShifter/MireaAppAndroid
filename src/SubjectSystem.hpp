#ifndef SUBJECTSYSTEM_HPP
#define SUBJECTSYSTEM_HPP

# include <QObject>
# include <QtNetwork/QTcpSocket>
#include <qudpsocket.h>

class SubjectSystem : public QObject
{
      Q_OBJECT
      QStringList FileNames{};
      QString SubjectName{};
      QString UserName{};
public:
      explicit SubjectSystem(QObject *parent = nullptr);
      QUdpSocket  MainSocket;
      bool AccessFiles(QString &FileName, QString &SubjectName);
      Q_INVOKABLE void _ItemPressed(QString FileName);

      QStringList getFileNames() const;
      void setFileNames(const QStringList &newFileNames);

      QString getSubjectName() const;
      void setSubjectName(const QString &newSubjectName);

      QString getUserName() const;
      void setUserName(const QString &newUserName);

signals:
      void FileNamesChanged();
      void SubjectNameChanged();

      void UserNameChanged();

private:
      Q_PROPERTY(QStringList _FileNames READ getFileNames WRITE setFileNames NOTIFY FileNamesChanged FINAL)
      Q_PROPERTY(QString _SubjectName READ getSubjectName WRITE setSubjectName NOTIFY SubjectNameChanged FINAL)
      Q_PROPERTY(QString _UserName READ getUserName WRITE setUserName NOTIFY UserNameChanged FINAL)
};

#endif // SUBJECTSYSTEM_HPP
