#include "SubjectSystem.hpp"
#include "src/Searcher.h"
#include <qnetworkdatagram.h>
# include <string>
# include <iostream>
# include <fstream>
# include <filesystem>
QStringList SubjectSystem::getFileNames() const
{
      return FileNames;
}

void SubjectSystem::setFileNames(const QStringList &newFileNames)
{
      if (FileNames == newFileNames)
            return;
      FileNames = newFileNames;
      emit FileNamesChanged();
}

QString SubjectSystem::getSubjectName() const
{
      return SubjectName;
}

void SubjectSystem::setSubjectName(const QString &newSubjectName)
{
      if (SubjectName == newSubjectName)
            return;
      SubjectName = newSubjectName;
      emit SubjectNameChanged();
}

QString SubjectSystem::getUserName() const
{
      return UserName;
}

void SubjectSystem::setUserName(const QString &newUserName)
{
      if (UserName == newUserName)
            return;
      UserName = newUserName;
      emit UserNameChanged();
}

SubjectSystem::SubjectSystem(QObject *parent)
      : QObject{parent}
{
      std::fstream CacheFile("Files/Subjects/Cache.txt", std::ios_base::in);
      std::string Buffer{}, BufferName{};
      std::getline(CacheFile, Buffer);
      std::getline(CacheFile, BufferName);
      SubjectName = QString::fromStdString(BufferName);
      CacheFile.close();
      CacheFile.open(Buffer, std::ios_base::in);
      FileNames.reserve(10);
      for (;std::getline(CacheFile, Buffer, '\n');)
      {
            FileNames.push_back(QString::fromStdString(Buffer));
      }
      CacheFile.close();
      CacheFile.open("Files/Cache.txt", std::ios_base::in);
      std::getline(CacheFile, Buffer);
      std::getline(CacheFile, Buffer);
      CacheFile.close();
      char* ToCut = const_cast<char*>(Buffer.c_str());
      char* Token{std::strtok(ToCut, " ")};
      for(short Index{};Token;++Index)
      {
            if (Index == 0)
            {
                  UserName += Token;
                  UserName += " ";
            }
            else
            {
                  QString Wtf{QString::fromUtf8(Token)};
                  UserName += Wtf[0] + '.';
            }
            Token = std::strtok(nullptr, " ");
      }
}

bool SubjectSystem::AccessFiles(QString& FileName, QString& SubjectName)
{
      MainSocket.bind(QHostAddress::LocalHost, 33333);
      std::string Request{"f\n" + SubjectName.toStdString() + '\n' + FileName.toStdString()};
      MainSocket.writeDatagram(Request.c_str(), QHostAddress(QHostAddress::LocalHost), 32323);
      MainSocket.waitForBytesWritten();
      MainSocket.waitForReadyRead();
      Request = "Files/Subjects/File";
      QFile FileContent(Request.c_str());
      QNetworkDatagram Datagram {MainSocket.receiveDatagram()};
      if (!FileContent.open(QIODevice::ReadWrite))
      {
            std::cout << "File is nto open\n";
            return 1;
      }
      FileContent.write(Datagram.data());
      if (FileContent.size() <= 0)
      {
            FileContent.close();
            return 1;
      }
      else
      {
            FileContent.close();
            return 0;
      }



}

void SubjectSystem::_ItemPressed(QString FileName)
{

      AccessFiles(FileName, this->SubjectName);
      qDebug() << "Item pressed";
      MainSocket.waitForDisconnected();
      MainSocket.close();
}
