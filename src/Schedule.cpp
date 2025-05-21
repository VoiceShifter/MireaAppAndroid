#include "Schedule.hpp"
# include <QtNetwork/QNetworkDatagram>
# include <fstream>
# include <filesystem>
# include <vector>
# include <string>
# include <QDate>
#include <sstream>
void Schedule::ProcessFile(std::string& FilePath) noexcept
{
      std::fstream ScheduleFile(FilePath, std::ios_base::in);
      std::string Buffer{}, Day{};
      signed int InnerIndex{-1};
      bool IsOdd{0};
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
                              IsNext = 5;
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
                              OddDays[InnerIndex]->Day = QString::fromStdString(Day);
                              EvenDays[InnerIndex]->Day = QString::fromStdString(Day);
                              break;
                        }
                        case 1:
                        {
                              if (Buffer.substr(2)=="Empty")
                              {
                                    EvenDays[InnerIndex]->Types.append("N/A");
                                    EvenDays[InnerIndex]->TeacherNames.append("N/A");
                                    EvenDays[InnerIndex]->Places.append("N/A");
                              }
                              IsOdd = 0;
                              EvenDays[InnerIndex]->ItemNames.append(QString::fromStdString(Buffer.substr(2)));
                              break;
                        }
                        case 5:
                        {
                              if (Buffer.substr(2)=="Empty")
                              {
                                    OddDays[InnerIndex]->Types.append("N/A");
                                    OddDays[InnerIndex]->TeacherNames.append("N/A");
                                    OddDays[InnerIndex]->Places.append("N/A");
                              }
                              IsOdd = 1;
                              OddDays[InnerIndex]->ItemNames.append(QString::fromStdString(Buffer.substr(2)));
                              break;
                        }
                        case 2:
                        {
                              if (IsOdd)
                              {
                                    OddDays[InnerIndex]->Types.append(QString::fromStdString(Buffer.substr(2)));
                              }
                              else
                              {
                                    EvenDays[InnerIndex]->Types.append(QString::fromStdString(Buffer.substr(2)));
                              }
                              break;
                        }
                        case 3:
                        {
                              if (IsOdd)
                              {
                                    OddDays[InnerIndex]->TeacherNames.append(QString::fromStdString(Buffer.substr(2)));
                              }
                              else
                              {
                                    EvenDays[InnerIndex]->TeacherNames.append(QString::fromStdString(Buffer.substr(2)));
                              }
                              break;
                        }
                        case 4:
                        {
                              if (IsOdd)
                              {
                                    OddDays[InnerIndex]->Places.append(QString::fromStdString(Buffer.substr(2)));
                              }
                              else
                              {
                                    EvenDays[InnerIndex]->Places.append(QString::fromStdString(Buffer.substr(2)));
                              }
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
      // emit OddDays[CurrentDayInt]->TeacherNamesChanged();
      // emit EvenDays[CurrentDayInt]->TeacherNamesChanged();
      // emit OddDays[CurrentDayInt]->ItemNamesChanged();
      // emit EvenDays[CurrentDayInt]->ItemNamesChanged();
      // emit EvenDays[CurrentDayInt]->PlacesChanged();
      // emit OddDays[CurrentDayInt]->PlacesChanged();
      // emit EvenDays[CurrentDayInt]->TypesChanged();
      // emit OddDays[CurrentDayInt]->TypesChanged();
      // emit EvenDays[CurrentDayInt]->DayChanged();
      // emit OddDays[CurrentDayInt]->DayChanged();
      QVector<DaysContentStruct*>* ToIterate;
      if (CurrentWeekNumber % 2 == 0)
      {
            ToIterate = &EvenDays;
      }
      else
      {
            ToIterate = &OddDays;
      }
      for (size_t Index{0}; Index < Days.size(); ++Index)
      {
            emit (*ToIterate)[Index]->TeacherNamesChanged();
            emit (*ToIterate)[Index]->ItemNamesChanged();
            emit (*ToIterate)[Index]->PlacesChanged();
            emit (*ToIterate)[Index]->TypesChanged();
            emit (*ToIterate)[Index]->DayChanged();
      }
      emit OddDaysChanged();
      emit EvenDaysChanged();

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
            OddDays.push_back(new DaysContentStruct);
            EvenDays.push_back(new DaysContentStruct);
      }
      Buffer = "Files/" + CurrentGroup + ".txt";
      if (std::filesystem::exists(Buffer))
      {            
            DifferentiateDay();
            ProcessFile(Buffer);
      }
      else
      {
            qDebug() << "No default schedule";
            RequestScheduleFile(CurrentGroup);
            DifferentiateDay();
            ProcessFile(Buffer);
      }

}

signed int Schedule::getCurrentWeekNumber() const
{
      return CurrentWeekNumber;
}

void Schedule::setCurrentWeekNumber(signed int newCurrentWeekNumber)
{
      if (CurrentWeekNumber == newCurrentWeekNumber)
            return;
      CurrentWeekNumber = newCurrentWeekNumber;
      emit CurrentWeekNumberChanged();
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

int Schedule::getCurrentDayInt() const
{
      return CurrentDayInt;
}

void Schedule::setCurrentDayInt(int newCurrentDayInt)
{
      if (CurrentDayInt == newCurrentDayInt)
            return;
      CurrentDayInt = newCurrentDayInt;
      emit CurrentDayIntChanged();
}

void Schedule::_LoadDefault()
{

}

void Schedule::_IncrementDay(signed int Value)
{
      CurrentDayInt += Value;
      if (CurrentDayInt > 5)
      {
            CurrentDayInt = CurrentDayInt - 6;
            ++CurrentWeekNumber;
      }
      else if (CurrentDayInt < 0)
      {
            CurrentDayInt = 5;
            --CurrentWeekNumber;
      }
      emit CurrentDayIntChanged();
      emit CurrentWeekNumberChanged();
}

bool Schedule::_ChangeSchedule(QString Filename)
{
      std::string ConstString{Filename.toUpper().toStdString()};
      std::string PathString{"Files/" + ConstString + ".txt"};
      if (std::filesystem::exists(PathString))
      {
            OddDays.clear();
            EvenDays.clear();
            for(signed int Index{0}; Index < 7; ++Index)
            {
                  OddDays.push_back(new DaysContentStruct);
                  EvenDays.push_back(new DaysContentStruct);
            }
            ProcessFile(PathString);
            qDebug() << "Processing was succesfull";
            return 1;
      }
      else if (RequestScheduleFile(ConstString))
      {
            OddDays.clear();
            EvenDays.clear();
            for(signed int Index{0}; Index < 7; ++Index)
            {
                  OddDays.push_back(new DaysContentStruct);
                  EvenDays.push_back(new DaysContentStruct);
            }
            ProcessFile(PathString);
            qDebug() << "Downloading and Processing was succesfull";
            return 1;
      }
      else
      {
            qDebug() << "Error requesting file";
            return 0;
      }
      return 0;
}

QVector<DaysContentStruct*> Schedule::getDays() const
{
      qDebug() << "Hope that doesnt get called";
      return Days;
}

QVector<DaysContentStruct *> Schedule::OddgetDays() const
{
      qDebug() << "OddDays called";
      return OddDays;
}

QVector<DaysContentStruct *> Schedule::EvengetDays() const
{
      qDebug() << "EvenDays called";
      return EvenDays;
}

void Schedule::setDays(const QVector<DaysContentStruct *> &newDays)
{

      emit DaysChanged();
}

signed int Schedule::DifferentiateDay()
{
      CurrentDayInt = QDateTime::currentDateTime().date().dayOfWeek() - 1;
      QDate Today{QDate::currentDate()};
      int Year{};
      if (Today.month() < 9)
      {
            Year = Today.year() - 1;
      }
      else
      {
            Year = Today.year();
      }
      QDate Start{Year, 9, 1};
      CurrentWeekNumber = Start.daysTo(Today);
      emit CurrentWeekNumberChanged();
      switch (CurrentDayInt) {
      case 0:
            CurrentDayString = "ПОНЕДЕЛЬНИК";
            break;
      case 1:
            CurrentDayString = "ВТОРНИК";
            break;
      case 2:
            CurrentDayString = "СРЕДА";
            break;
      case 3:
            CurrentDayString = "ЧЕТВЕРГ";
            break;
      case 4:
            CurrentDayString = "ПЯТНИЦА";
            break;
      case 5:
            CurrentDayString = "СУББОТА";
            break;
      case 6:
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
