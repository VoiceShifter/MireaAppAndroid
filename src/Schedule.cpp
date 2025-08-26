#include "Schedule.hpp"
# include <QtNetwork/QNetworkDatagram>
# include <fstream>
# include <filesystem>
# include <vector>
# include <string>
# include <QDate>
#include <sstream>
# include <assert.h>
QString Schedule::getUserName() const
{
      return UserName;
}

void Schedule::setUserName(const QString &newUserName)
{
      if (UserName == newUserName)
            return;
      UserName = newUserName;
      emit UserNameChanged();
}

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

int DifferentiateDayString(std::string& DayString)
{
      if (DayString == "ПОНЕДЕЛЬНИК")
      {
            return 0;
      }
      else if (DayString == "ВТОРНИК")
      {
            return 1;
      }
      else if (DayString == "СРЕДА")
      {
            return 2;
      }
      else if (DayString == "ЧЕТВЕРГ")
      {
            return 3;
      }
      else if (DayString == "ПЯТНИЦА")
      {
            return 4;
      }
      else if (DayString == "СУББОТА")
      {
            return 5;
      }
      else if (DayString == "ВОСКРЕСЕНЬЕ")
      {
            return 6;
      }
      return -1;
}

void Schedule::ProcessTeachersFile(std::string &FilePath)
{

      std::fstream ScheduleFile(FilePath, std::ios_base::in);
      std::string Buffer{}, Day{};
      signed int InnerIndex{-1}, SubjectIndex{0};
      bool IsOdd{0};
      std::vector<std::string> Times{"9-00", "10-40", "12-40", "14-20", "16-20", "18-00"};
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
                              SubjectIndex = 0;
                              break;
                        } //day
                        case 67:
                        {
                              IsNext = 2;
                              break;
                        }
                        case 69:
                        {
                              IsNext = 1;
                              break;
                        } // even
                        case 71:
                        {
                              IsNext = 7;
                              break;
                        }
                        case 79:
                        {
                              IsNext = 5;
                              break;
                        } // odd
                        case 84:
                        {
                              IsNext = 6;
                              break;
                        } // time
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
                        OddDays[DifferentiateDayString(Day)]->Day = QString::fromStdString(Day);
                        EvenDays[DifferentiateDayString(Day)]->Day = QString::fromStdString(Day);
                        break;
                  }
                  case 1:
                  {
                        if (Buffer.substr(2)=="Empty")
                        {
                              EvenDays[DifferentiateDayString(Day)]->Types.append("N/A");
                              EvenDays[DifferentiateDayString(Day)]->TeacherNames.append("N/A");
                              EvenDays[DifferentiateDayString(Day)]->Places.append("N/A");
                        }
                        IsOdd = 0;
                        EvenDays[DifferentiateDayString(Day)]->ItemNames.append(QString::fromStdString(Buffer.substr(2)));
                        break;
                  }
                  case 5:
                  {
                        if (Buffer.substr(2)=="Empty")
                        {
                              OddDays[DifferentiateDayString(Day)]->Types.append("N/A");
                              OddDays[DifferentiateDayString(Day)]->TeacherNames.append("N/A");
                              OddDays[DifferentiateDayString(Day)]->Places.append("N/A");
                        }
                        IsOdd = 1;
                        OddDays[DifferentiateDayString(Day)]->ItemNames.append(QString::fromStdString(Buffer.substr(2)));
                        break;
                  }
                  case 6: //time
                  {
                        std::string CurrentSubjectTime{Buffer.substr(2)};
                        if (CurrentSubjectTime != Times[SubjectIndex])
                        {
                              for (size_t FixIndex{0}; CurrentSubjectTime != Times[FixIndex]; ++FixIndex)
                              {
                                    if (IsOdd == 1)
                                    {
                                          OddDays[DifferentiateDayString(Day)]->ItemNames.insert(0, "Empty");
                                          OddDays[DifferentiateDayString(Day)]->Types.insert(0, "N/A");
                                          OddDays[DifferentiateDayString(Day)]->TeacherNames.insert(0, "N/A");
                                          OddDays[DifferentiateDayString(Day)]->Places.insert(0, "N/A");
                                    }
                                    else
                                    {
                                          EvenDays[DifferentiateDayString(Day)]->ItemNames.insert(0, "Empty");
                                          EvenDays[DifferentiateDayString(Day)]->Types.insert(0, "N/A");
                                          EvenDays[DifferentiateDayString(Day)]->TeacherNames.insert(0, "N/A");
                                          EvenDays[DifferentiateDayString(Day)]->Places.insert(0, "N/A");
                                    }
                              }
                        }
                        break;
                  }
                  case 2:
                  {
                        if (IsOdd)
                        {
                              OddDays[DifferentiateDayString(Day)]->Types.append(QString::fromStdString(Buffer.substr(2)));
                        }
                        else
                        {
                              EvenDays[DifferentiateDayString(Day)]->Types.append(QString::fromStdString(Buffer.substr(2)));
                        }
                        break;
                  }
                  case 3:
                  {
                        if (IsOdd)
                        {
                              OddDays[DifferentiateDayString(Day)]->TeacherNames.append(QString::fromStdString(Buffer.substr(2)));
                        }
                        else
                        {
                              EvenDays[DifferentiateDayString(Day)]->TeacherNames.append(QString::fromStdString(Buffer.substr(2)));
                        }
                        break;
                  }
                  case 4:
                  {
                        if (IsOdd)
                        {
                              OddDays[DifferentiateDayString(Day)]->Places.append(QString::fromStdString(Buffer.substr(2)));
                              ++SubjectIndex;
                        }
                        else
                        {
                              EvenDays[DifferentiateDayString(Day)]->Places.append(QString::fromStdString(Buffer.substr(2)));
                        }
                        break;
                  }
                  case 7:
                  {
                        if (IsOdd)
                        {
                              OddDays[DifferentiateDayString(Day)]->TeacherNames.append(QString::fromStdString(Buffer.substr(2)));
                        }
                        else
                        {
                              EvenDays[DifferentiateDayString(Day)]->TeacherNames.append(QString::fromStdString(Buffer.substr(2)));
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
      // for (size_t Index{0}; Index < OddDays.size(); ++Index)
      // {
      //       if (OddDays[Index]->ItemNames.size() < 1)
      //       {
      //             OddDays[Index]->ItemNames.append("Empty");
      //             OddDays[Index]->Types.append("N/A");
      //             OddDays[Index]->TeacherNames.append("N/A");
      //             OddDays[Index]->Places.append("N/A");
      //       }
      //       if (EvenDays[Index]->ItemNames.size() < 1)
      //       {
      //             EvenDays[Index]->ItemNames.append("Empty");
      //             EvenDays[Index]->Types.append("N/A");
      //             EvenDays[Index]->TeacherNames.append("N/A");
      //             EvenDays[Index]->Places.append("N/A");
      //       }
      // }
      QVector<DaysContentStruct*>* ToIterate;
      if (CurrentWeekNumber % 2 == 0)
      {
            ToIterate = &EvenDays;
      }
      else
      {
            ToIterate = &OddDays;
      }
      for (size_t Index{0}; Index < OddDays.size(); ++Index)
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

QString Schedule::getQCurrentGroup() const
{
      return QCurrentGroup;
}

void Schedule::setQCurrentGroup(const QString &newQCurrentGroup)
{
      if (QCurrentGroup == newQCurrentGroup)
            return;
      QCurrentGroup = newQCurrentGroup;
      emit QCurrentGroupChanged();
}

QString Schedule::getErrorMessage() const
{
      return ErrorMessage;
}

void Schedule::setErrorMessage(const QString &newErrorMessage)
{
      if (ErrorMessage == newErrorMessage)
            return;
      ErrorMessage = newErrorMessage;
      emit ErrorMessageChanged();
}

void Schedule::PrepareStructures()
{
      OddDays.clear();
      EvenDays.clear();
      for(signed int Index{0}; Index < 7; ++Index)
      {
            OddDays.push_back(new DaysContentStruct);
            OddDays[Index]->Day = QString::fromStdString(DaysStringArray[Index]);
            EvenDays.push_back(new DaysContentStruct);
            EvenDays[Index]->Day = QString::fromStdString(DaysStringArray[Index]);

      }
}

Schedule::Schedule(QObject *parent)
      : QObject{parent}
{
      std::fstream Cachefile("Files/Cache.txt", std::ios_base::in);
      for(;!Cachefile.is_open();)
      {
            Cachefile.open("Files/Cache.txt", std::ios_base::in);
      }
      std::vector<std::string> FileContent{};
      std::string Buffer{};
      FileContent.reserve(8);
      for (;std::getline(Cachefile, Buffer, '\n');)
      {
            FileContent.push_back(Buffer);
      }
      if (FileContent.size() > 2)
      {
            CurrentGroup = FileContent[FileContent.size()-1];
            QCurrentGroup = QString::fromStdString(CurrentGroup).toUpper();
            std::stringstream FullName{FileContent[1]};
            for (size_t Index{0};std::getline(FullName, Buffer, ' ');++Index)
            {
                  if (Index == 0)
                  {
                        UserName += Buffer + ' ';
                  }
                  else
                  {
                        QString Wtf{QString::fromUtf8(Buffer)};
                        UserName += Wtf[0] + '.';
                  }
            }
      }
      else
      {
            CurrentGroup = "ИКБО-07-21";
            UserName = "username";
            qDebug() << "How comes?";
      }

      PrepareStructures();
      Buffer = "Files/" + CurrentGroup + ".txt";
      if (std::filesystem::exists(Buffer))
      {            
            DifferentiateDay();
            if (Buffer.find(' ') == std::string::npos)
            {
                  ProcessFile(Buffer);
            }
            else
            {
                  ProcessTeachersFile(Buffer);
            }
      }
      else
      {
            qDebug() << "No default schedule";
            DifferentiateDay();

            if (!RequestScheduleFile(CurrentGroup))
            {
                  ErrorMessage = "No reply from server";
                  emit ErrorMessageChanged();
                  return;
            }
            if (Buffer.find(' ') == std::string::npos)
            {
                  ProcessFile(Buffer);
            }
            else
            {
                  ProcessTeachersFile(Buffer);
            }
      }
      Cachefile.close();
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

bool Schedule::TrySubject(std::string& SubjectName, std::string& UserName)
{
      MainSocket.bind(QHostAddress::LocalHost, 33333);
      std::string Request{"s\n" + SubjectName + '\n' + UserName};
      MainSocket.writeDatagram(Request.c_str(), QHostAddress(QHostAddress::LocalHost), 32323);
      MainSocket.waitForBytesWritten();
      MainSocket.waitForReadyRead();
      QNetworkDatagram Datagram {MainSocket.receiveDatagram()};      
      Request = "Files/Subjects/" + SubjectName + ".txt";
      std::string Reply{Datagram.data().toStdString()};
      if (Reply == "0")
      {
            ErrorMessage = "Нет доступа";
            emit ErrorMessageChanged();
            return 0;
      }
      else if (Reply == "")
      {
            ErrorMessage = "Нет доступа";
            emit ErrorMessageChanged();
            return 0;
      }
      else
      {
            std::fstream SubjectCache{"Files/Subjects/Cache.txt", std::ios_base::out};
            SubjectCache << Request << '\n' << SubjectName;
            SubjectCache.close();
            if(std::filesystem::exists(Request))
            {
                  return 1;
            }
            else
            {
                  std::fstream SubjectFile(Request, std::ios_base::out);
                  SubjectFile << Reply;
                  SubjectFile.close();
                  return 1;
            }
      }
      return 0;
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

int Schedule::_ChangeSchedule(QString Filename)
{
      QCurrentGroup = Filename.toUpper();
      emit QCurrentGroupChanged();
      std::string ConstString{Filename.toUpper().toStdString()};
      std::string PathString{"Files/" + ConstString + ".txt"};
      if (std::filesystem::exists(PathString))
      {
            PrepareStructures();
            if (PathString.find(' ') == std::string::npos)
            {
                  ProcessFile(PathString);
            }
            else
            {
                  ProcessTeachersFile(PathString);
            }
            qDebug() << "Processing was succesfull";
            return 1;
      }
      else if (RequestScheduleFile(ConstString))
      {
            OddDays.clear();
            EvenDays.clear();
            PrepareStructures();
            if (PathString.find(' ') == std::string::npos)
            {
                  ProcessFile(PathString);
            }
            else
            {
                  ProcessTeachersFile(PathString);
            }
            qDebug() << "Downloading and Processing was succesfull";
            return 1;
      }
      else
      {
            qDebug() << "Error requesting file";
            return 2;
      }
      return 0;
}

signed int Schedule::_SubjectClicked(QString SubjectName)
{
      std::fstream Cachefile("Files/Cache.txt", std::ios_base::in);
      std::vector<std::string> FileContent{};
      std::string Buffer{};

      FileContent.reserve(8);
      for (;std::getline(Cachefile, Buffer, '\n');)
      {
            FileContent.push_back(Buffer);
      }

      Buffer = SubjectName.toStdString();
      if(!TrySubject(Buffer, FileContent[1]))
      {
            return 0;
      }
      else
      {
            return 1;
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
      return OddDays;
}

QVector<DaysContentStruct *> Schedule::EvengetDays() const
{
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
      QDate Start;
      if (Today.month() < 9)
      {
            Year = Today.year() - 1;
            Start = QDate(Year, 1, 1);
      }
      else
      {
            Year = Today.year();
            Start = QDate(Year, 9, 1);
      }

      CurrentWeekNumber = Start.daysTo(Today) / 7;
      for (;CurrentWeekNumber > 16;)
      {
            CurrentWeekNumber-=16;
      }
      qDebug() << CurrentWeekNumber << " - номер недели";
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
