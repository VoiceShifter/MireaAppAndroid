#include "Schedule.hpp"
# include <QtNetwork/QNetworkDatagram>
# include <fstream>
# include <filesystem>
# include <vector>
# include <string>
# include <QDate>
#include <sstream>
void Schedule::ProcessFile(std::string& FilePath, std::string& CurrentDay) noexcept
{
      std::fstream ScheduleFile(FilePath, std::ios_base::in);
      std::string Buffer{}, Day{};
      signed int InnerIndex{-1};
      for(size_t Index{}; std::getline(ScheduleFile, Buffer, '\n'); ++Index)
      {
            std::stringstream InnerBuffer{Buffer};
            signed int IsNext{-1}; //day - 0 //name - 1 //type - 2 //master - 3 //place - 4
            for(; std::getline(InnerBuffer, Buffer, ':');)
            {
                  switch(int(Buffer[0]))
                  {
                        case 68:
                        {
                              IsNext = 0;
                              ++InnerIndex;
                              break;
                        } //day
                        case 69:
                        {
                              IsNext = 1;
                              break;
                        } // even
                        case 79:
                        {
                              IsNext = 1;
                              break;
                        } // odd
                        case 84:
                        {
                              IsNext = 2;
                              break;
                        } // type
                        case 77:
                        {
                              IsNext = 3;
                              break;
                        } // master
                        case 80:
                        {
                              IsNext = 4;
                              break;
                        } //place
                        default: //value
                        {
                              break;
                              // go to another switch-case
                        }
                  };
                  // if (IsNext!=0 && CurrentDay != Day)
                  // {
                  //       goto LoopEnd;
                  // }
                  switch (IsNext)
                  {
                        case 0:
                        {
                              Day = Buffer.substr(4);
                              Days[InnerIndex]->Day = QString::fromStdString(Day);
                              break;
                        }
                        case 1:
                        {
                              Days[InnerIndex]->ItemNames.append(QString::fromStdString(Buffer.substr(2)));
                              break;
                        }
                        case 2:
                        {
                              Days[InnerIndex]->Types.append(QString::fromStdString(Buffer.substr(2)));
                              break;
                        }
                        case 3:
                        {
                              Days[InnerIndex]->TeacherNames.append(QString::fromStdString(Buffer.substr(2)));
                              break;
                        }
                        case 4:
                        {
                              Days[InnerIndex]->Places.append(QString::fromStdString(Buffer.substr(2)));
                              break;
                        }
                        default:
                        {
                              qDebug() << "Unknown type\n";
                              break;
                        }
                  }
                  IsNext = -1;                  
            }

      LoopEnd:
            continue;

      }
      for (size_t Index{0}; Index < Days.size(); ++Index)
      {
            emit Days[Index]->TeacherNamesChanged();
            emit Days[Index]->ItemNamesChanged();
            emit Days[Index]->PlacesChanged();
            emit Days[Index]->TypesChanged();
            emit Days[Index]->DayChanged();
      }

}



Schedule::Schedule(QObject *parent)
      : QObject{parent}
{
      std::fstream Cachefile("Cache.txt", std::ios_base::in);
      std::vector<std::string> FileContent{};
      std::string Buffer{};
      FileContent.reserve(8);
      for (;std::getline(Cachefile, Buffer, '\n');)
      {
            FileContent.push_back(Buffer);
      }
      if (FileContent.size() > 0)
      {
            CurrentGroup = FileContent[FileContent.size()-1];
            UserName = FileContent[1];
      }
      else
      {
            CurrentGroup = "ИКБО-07-21";
            UserName = "username";
      }

      for(signed int Index{0}; Index < 7; ++Index)
      {
            Days.push_back(new DaysContentStruct);
      }
      Buffer = "Files/" + CurrentGroup + ".txt";
      if (std::filesystem::exists(Buffer))
      {            
            DifferentiateDay();
            ProcessFile(Buffer, CurrentDayString);
      }
      else
      {
            qDebug() << "No default schedule";
            RequestScheduleFile(CurrentGroup);

            DifferentiateDay();
            ProcessFile(Buffer, CurrentDayString);
      }

}

bool Schedule::RequestScheduleFile(std::string& FileName)
{
      MainSocket.bind(QHostAddress::LocalHost, 33333);
      std::string Request{"g\n" + FileName};
      MainSocket.writeDatagram(Request.c_str(), QHostAddress(QHostAddress::LocalHost), 32323);
      MainSocket.waitForBytesWritten();
      MainSocket.waitForReadyRead();
      QNetworkDatagram Datagram {MainSocket.receiveDatagram()};
      Request = "Files/" + FileName + ".txt";
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

void Schedule::LoadDefault()
{

}

QVector<DaysContentStruct*> Schedule::getDays() const
{
      qDebug() << "Hope that doesnt get called";
      return Days;
}

void Schedule::setDays(const QVector<DaysContentStruct *> &newDays)
{

      emit DaysChanged();
}

signed int Schedule::DifferentiateDay()
{
      CurrentDayInt = QDateTime::currentDateTime().date().dayOfWeek();
      switch (CurrentDayInt) {
      case 1:
            CurrentDayString = "ПОНЕДЕЛЬНИК";
            break;
      case 2:
            CurrentDayString = "ВТОРНИК";
            break;
      case 3:
            CurrentDayString = "СРЕДА";
            break;
      case 4:
            CurrentDayString = "ЧЕТВЕРГ";
            break;
      case 5:
            CurrentDayString = "ПЯТНИЦА";
            break;
      case 6:
            CurrentDayString = "СУББОТА";
            break;
      case 7:
            CurrentDayString = "ВОСКРЕСЕНЬЕ";

            break;
      default:
            CurrentDayString = "0";
            return -1;
      }
      return 0;
}

QStringList DaysContentStruct::getItemNames() const
{
      return ItemNames;
}

void DaysContentStruct::setItemNames(const QStringList &newItemNames)
{
      if (ItemNames == newItemNames)
            return;
      ItemNames = newItemNames;
      emit DaysContentStruct::ItemNamesChanged();
}

QStringList DaysContentStruct::getPlaces() const
{
      return Places;
}

void DaysContentStruct::setPlaces(const QStringList &newPlaces)
{
      if (Places == newPlaces)
            return;
      Places = newPlaces;
      emit PlacesChanged();
}

QStringList DaysContentStruct::getTypes() const
{
      return Types;
}

void DaysContentStruct::setTypes(const QStringList &newTypes)
{
      if (Types == newTypes)
            return;
      Types = newTypes;
      emit TypesChanged();
}

QString DaysContentStruct::getDay() const
{
      return Day;
}

void DaysContentStruct::setDay(const QString &newDay)
{
      if (Day == newDay)
            return;
      Day = newDay;
      emit DayChanged();
}

QStringList DaysContentStruct::getTeacherNames() const
{
      return TeacherNames;
}

void DaysContentStruct::setTeacherNames(const QStringList &newTeacherNames)
{
      if (TeacherNames == newTeacherNames)
            return;
      TeacherNames = newTeacherNames;
      emit TeacherNamesChanged();
}
