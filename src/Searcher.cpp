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
      for (const auto& Iterator: Results)
      {
            _Items << Iterator.c_str();
            qDebug() << "Appended"<< '\n';
      }
      qDebug() << "_List Populated"<< '\n';
      emit listPopulated();
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
      Results.clear();
      size_t Character{1};
      std::string Buffer{}, Input{aInput.toStdString()};

      qDebug() << aInput << '\n';

      for (; std::getline(TeachersList, Buffer);)
      {
            if (int(Buffer[0]) == int(Input[0]))
            {
                  Results.insert(Buffer);
            }
      }

      for (; Character < Input.size() && EndBit; ++Character)
      {

            Results = Iterate(Results, Input, Character);
      }
      qDebug() << "Seach complited\n";
      for (const auto& Iterator : Results)
      {
            qDebug() << Iterator.c_str();
      }
      //TeachersList.seekg(0);
      TeachersList.close(); //перенос коретки в начало
      TeachersList.open("Files/Teachers.txt", std::ios::in); // //в будущем надо будет сделать qml/data/Teachers.txt
      _Items.clear();

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
