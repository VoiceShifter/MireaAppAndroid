# include "Searcher.h"
# include <filesystem>
#include <qnetworkdatagram.h>
const QString &Searcher::Cache() const
{
      qDebug() << "_Cache"<< '\n';

      return _Cache;
}

QStringList Searcher::_GetItems()
{
      qDebug() << "_GetItems"<< '\n';

      return _Items;
}

void Searcher::_PopulateItems(QStringList&)
{
}

bool Searcher::RequestScheduleFile(std::string& Filename)
{
      MainSocket.bind(QHostAddress::LocalHost, 33333);
      std::string Request{"g\n" + Filename};
      MainSocket.writeDatagram(Request.c_str(), QHostAddress(QHostAddress::LocalHost), 32323);
      MainSocket.waitForBytesWritten();
      MainSocket.waitForReadyRead();
      QNetworkDatagram Datagram {MainSocket.receiveDatagram()};
      Request = "Files/" + Filename + ".txt";
      std::string FileContent{Datagram.data().toStdString()};
      if (FileContent.size() > 1)
      {
            std::fstream ScheduleFile(Request, std::ios_base::out);
            ScheduleFile << FileContent;
            ScheduleFile.close();
            return 1;
      }
      else
      {            
            return 0;
      }
}

void Searcher::_PrintItems()
{
      for (const auto& Iterator : _Items)
      {
            qDebug() << Iterator << '\n';
      }
      qDebug() << "Ended printing" << '\n';
}



Searcher::Searcher(QObject *parent) : QObject(parent)
{

      std::string Filename{"Teachers"};
      if (!std::filesystem::exists("Files/" + Filename + ".txt"))
      {
            if (!RequestScheduleFile(Filename))
            {
                  return;
            }
      }

      TeachersList.open("Files/Teachers.txt", std::ios::in); //в будущем надо будет сделать qml/data/Teachers.txt
      std::string Buffer{};
      if (!TeachersList.is_open())
      {
            qDebug() << "File Teachers not found\n";
      }

}

Searcher::~Searcher()
{

}

void Searcher::_Search(QString aInput)
{
      _Items.clear();
      Results.clear();
      Results.reserve(100);
      size_t Character{1};
      std::string Buffer{}, Input{aInput.toStdString()};
      std::vector<QString> FileContent{};
      FileContent.reserve(60);
      for (; std::getline(TeachersList, Buffer);)
      {
            if (QString::fromStdString(Buffer)[0] != aInput[0])
            {
                  continue;
            }
            qDebug() << int(Buffer[0]) << int(Input[0]);
            FileContent.push_back(QString::fromStdString(Buffer));
      }
      bool IsOdd{1};
      for (short Index{1}; Index < Input.size() - 1; ++Index)
      {

            if (IsOdd)
            {
                  if (FileContent.size() <= 1)
                  {
                        Results.clear();
                        break;
                  }
                  Results.clear();
                  for (short Inner{}; Inner < FileContent.size();++Inner)
                  {
                        if (FileContent[Inner][Index] != aInput[Index])
                        {
                              continue;
                        }
                        Results.push_back(FileContent[Inner]);
                  }
                  IsOdd = 0;
            }
            else
            {
                  if (Results.size() <= 1)
                  {
                        FileContent.clear();
                        break;
                  }
                  FileContent.clear();
                  for (short Inner{}; Inner < Results.size();++Inner)
                  {
                        if (Results[Inner][Index] != aInput[Index])
                        {
                              continue;
                        }
                        FileContent.push_back(QString::fromStdString(Buffer));
                  }
                  IsOdd = 1;
            }
      }
      if (Results.empty())
      {
            for (short Index{}; Index < FileContent.size(); ++Index)
            {
                  _Items.append(FileContent[Index]);
            }
      }
      else
      {
            for (short Index{}; Index < Results.size(); ++Index)
            {
                  _Items.append(Results[Index]);
            }
      }
      emit listPopulated();



      // Results.clear();
      // size_t Character{1};
      // std::string Buffer{}, Input{aInput.toStdString()};

      // qDebug() << aInput << '\n';

      // for (; std::getline(TeachersList, Buffer);)
      // {
      //       if (int(Buffer[0]) == int(Input[0]))
      //       {
      //             Results.insert(Buffer);
      //       }
      // }

      // for (; Character < Input.size() && EndBit; ++Character)
      // {

      //       Results = Iterate(Results, Input, Character);
      // }
      // qDebug() << "Seach complited\n";
      // for (const auto& Iterator : Results)
      // {
      //       qDebug() << Iterator.c_str();
      // }
      // //TeachersList.seekg(0);
       TeachersList.close(); //перенос коретки в начало
       TeachersList.open("Files/Teachers.txt", std::ios::in); // //в будущем надо будет сделать qml/data/Teachers.txt
      // _Items.clear();

}

bool Searcher::_ResultClicked(QString Input)
{
      CacheFile.open("Files/Cache.txt", std::ios_base::in);
      if (!CacheFile.is_open())
      {
            qDebug() << "Couldnt open cache file";
            return 0;
      }
      std::vector<std::string> FileContent{};
      std::string Buffer{};
      FileContent.reserve(8);
      for (;std::getline(CacheFile, Buffer, '\n');)
      {
            FileContent.push_back(Buffer);
      }
      FileContent[FileContent.size() - 1] = Input.toStdString();
      CacheFile.close();
      CacheFile.open("Files/Cache.txt", std::ios_base::out);
      if (!CacheFile.is_open())
      {
            qDebug() << "Couldnt open cache file";
            CacheFile.close();
            return 0;
      }
      for (size_t Index{}; Index<FileContent.size(); ++Index)
      {
            CacheFile << FileContent[Index] << '\n';

      }
      CacheFile.close();
      return 1;
}

std::unordered_set<std::string> Searcher::Iterate(std::unordered_set<std::string> &aSet, std::string &Input, size_t Character)
{
      if (aSet.size() == 1 && Input.substr(Character, Input.size()-Character) == aSet.begin()->substr(Character, Input.size() - Character))
      {
            EndBit = 0;
            return aSet;
      }
      std::unordered_set<std::string> NewResults{};
      for (const auto& Iterator : aSet)
      {
            if (Iterator[Character] == Input[Character])
            {
                  NewResults.insert(Iterator);
            }
      }
      return NewResults;
}
