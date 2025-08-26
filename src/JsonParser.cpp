# include "JsonParser.h"
# include <QDate>

# include <QStandardPaths>
# include <QtGlobal>
# include <QFile>
# include <QDir>
JsonParser::JsonParser(QObject *parent)
      : QObject{parent}, fJsonFile("Schedule.json"), Students{"Student1", "Student2", "Student3",
                     "Student4", "Student5", "Student6",
                     "Student7", "Student8", "Student9"}
{
      QFile Dynamic("NewSchedule.json");
      Dynamic.open(QIODevice::ReadWrite);
      fJsonFile.open(QIODevice::ReadWrite);
      Dynamic.close();

      _GetWeekReply();

      CurrentTime = QDateTime::currentDateTime();
      //CurrentTime = date.toString("hh:mm");
      qDebug() << "Это неделя" << Week;
      switch (CurrentTime.date().dayOfWeek()) {
      case 1:
            CurrentDayString = "Понедельник";
            CurrentDayInt = 0;
            break;
      case 2:
            CurrentDayString = "Вторник";
            CurrentDayInt = 1;
            break;
      case 3:
            CurrentDayString = "Среда";
            CurrentDayInt = 2;
            break;
      case 4:
            CurrentDayString = "Четверг";
            CurrentDayInt = 3;
            break;
      case 5:
            CurrentDayString = "Пятница";
            CurrentDayInt = 4;
            break;
      case 6:
            CurrentDayString = "Суббота";
            CurrentDayInt = 5;
            break;
      case 7:
            CurrentDayString = "Воскресенье";
            CurrentDayInt = 6;
            break;

      default:
            break;
      }

}

JsonParser::~JsonParser()
{
      fJsonFile.close();
      qDebug() << "Destructor called";
}

QJsonArray JsonParser::getFJson() const
{
      return fJson;
}

void JsonParser::setFJson(const QJsonArray &newFJson)
{
      if (fJson == newFJson)
            return;
      fJson = newFJson;
      emit fJsonChanged();
}

void JsonParser::_GetReply()
{

      QString Url{"https://mirea.xyz/api/v1.3/groups/certain?name="};
      Url.append(Group);
      qDebug() << "New URL" << Url;
      fRequest.setUrl(QUrl(Url)); // //https://mirea.xyz/api/v1.3/groups/certain?name=ИКБО-07-21
      fReply = fManager.get(fRequest);
      QEventLoop loop;
      QAbstractSocket::connect(fReply, SIGNAL(finished()), &loop, SLOT(quit()));

      loop.exec();
      emit fJsonChanged();

      QString FormattedString{QString::fromUtf8(fReply->readAll())};
      qDebug() << FormattedString;
      fJsonFile.resize(0);
      qDebug() << "That supposed to be json";

      fJsonFile.write(FormattedString.toUtf8());
      fJsonFile.close();
      fJsonFile.open(QIODevice::ReadWrite);

}

void JsonParser::_ReadJson()
{
      qDebug() << fJsonFile.readAll();
}

QStringList JsonParser::getCurrentDayItems() const
{
      return CurrentDayItems;
}

void JsonParser::setCurrentDayItems(const QStringList &newCurrentDayItems)
{
      if (CurrentDayItems == newCurrentDayItems)
            return;
      CurrentDayItems = newCurrentDayItems;
      emit CurrentDayItemsChanged();
}

int JsonParser::getCurrentDayInt() const
{
      return CurrentDayInt;
}

void JsonParser::setCurrentDayInt(int newCurrentDayInt)
{
      if (CurrentDayInt == newCurrentDayInt)
            return;
      CurrentDayInt = newCurrentDayInt;
      emit CurrentDayIntChanged();
}

QStringList JsonParser::getCurrentDayCabs() const
{
      return CurrentDayCabs;
}

void JsonParser::setCurrentDayCabs(const QStringList &newCurrentDayCabs)
{
      if (CurrentDayCabs == newCurrentDayCabs)
            return;
      CurrentDayCabs = newCurrentDayCabs;
      emit CurrentDayCabsChanged();
}

QStringList JsonParser::getTimes() const
{
      return Times;
}

void JsonParser::setTimes(const QStringList &newTimes)
{
      if (Times == newTimes)
            return;
      Times = newTimes;
      emit TimesChanged();
}

QString JsonParser::getCurrentSubject() const
{
      return CurrentSubject;
}

void JsonParser::setCurrentSubject(const QString &newCurrentSubject)
{
      if (CurrentSubject == newCurrentSubject)
            return;
      CurrentSubject = newCurrentSubject;
      emit CurrentSubjectChanged();
}

QString JsonParser::getCurrentDayString() const
{
      return CurrentDayString;
}

void JsonParser::setCurrentDayString(const QString &newCurrentDayString)
{
      if (CurrentDayString == newCurrentDayString)
            return;
      CurrentDayString = newCurrentDayString;
      emit CurrentDayStringChanged();
}

QStringList JsonParser::getStudents() const
{
      return Students;
}

void JsonParser::setStudents(const QStringList &newStudents)
{
      if (Students == newStudents)
            return;
      Students = newStudents;
      emit StudentsChanged();
}

signed int JsonParser::getWeek() const
{
      return Week;
}

void JsonParser::_GetWeekReply()
{
      QString Url{"https://mirea.xyz/api/v1.3/time/week"};
      fRequest.setUrl(QUrl(Url)); // //https://mirea.xyz/api/v1.3/groups/certain?name=ИКБО-07-21
      fReply = fManager.get(fRequest);
      QEventLoop loop;
      QAbstractSocket::connect(fReply, SIGNAL(finished()), &loop, SLOT(quit()));

      loop.exec();
      QString FormattedString{QString::fromUtf8(fReply->readAll())};
      qDebug() << FormattedString;
      Week = FormattedString.toInt();
      qDebug() << Week;
}

void JsonParser::setWeek(signed int newWeek)
{
      if (Week == newWeek)
            return;
      Week = newWeek;
      emit WeekChanged();
}

QStringList JsonParser::getType() const
{
      return Type;
}

void JsonParser::setType(const QStringList &newType)
{
      if (Type == newType)
            return;
      Type = newType;
      emit TypeChanged();
}

QStringList JsonParser::getPlace() const
{
      return Place;
}

void JsonParser::setPlace(const QStringList &newPlace)
{
      if (Place == newPlace)
            return;
      Place = newPlace;
      emit PlaceChanged();
}

QStringList JsonParser::getItemName() const
{
      return ItemName;
}

void JsonParser::setItemName(const QStringList &newItemName)
{
      if (ItemName == newItemName)
            return;
      ItemName = newItemName;
      emit ItemNameChanged();
}

QStringList JsonParser::getTeacherName() const
{
      return TeacherName;
}

void JsonParser::setTeacherName(const QStringList &newTeacherName)
{
      if (TeacherName == newTeacherName)
            return;
      TeacherName = newTeacherName;
      emit TeacherNameChanged();
}


void JsonParser::_IncrementDay()
{
      if (Group == "")
      {
            qDebug() << "Group is empty";
            return;
      }
      switch (this->CurrentDayInt) {
      case 0:
            CurrentDayString = "Вторник";
            CurrentDayInt = 1;
            break;
      case 1:
            CurrentDayString = "Среда";
            CurrentDayInt = 2;
            break;
      case 2:
            CurrentDayString = "Четверг";
            CurrentDayInt = 3;
            break;
      case 3:
            CurrentDayString = "Пятница";
            CurrentDayInt = 4;
            break;
      case 4:
            CurrentDayString = "Суббота";
            CurrentDayInt = 5;
            break;
      case 5:
            CurrentDayString = "Воскресенье";
            CurrentDayInt = 6;
            break;
      case 6:
            CurrentDayString = "Понедельник";
            CurrentDayInt = 0;
            Week++;
            break;

      default:
            break;
      }
      qDebug() << CurrentDayString;
      emit CurrentDayStringChanged();
      emit CurrentDayIntChanged();
}

void JsonParser::_DecrementDay()
{

      if (Group == "")
      {
            qDebug() << "Group is empty";
            return;
      }
      switch (this->CurrentDayInt) {
      case 0:
            CurrentDayString = "Воскресенье";
            CurrentDayInt = 6;
            Week--;
            break;
      case 1:
            CurrentDayString = "Понедельник";
            CurrentDayInt = 0;
            break;
      case 2:
            CurrentDayString = "Вторник";
            CurrentDayInt = 1;
            break;
      case 3:
            CurrentDayString = "Среда";
            CurrentDayInt = 2;
            break;
      case 4:
            CurrentDayString = "Четверг";
            CurrentDayInt = 3;
            break;
      case 5:
            CurrentDayString = "Пятница";
            CurrentDayInt = 4;
            break;
      case 6:
            CurrentDayString = "Суббота";
            CurrentDayInt = 5;
            break;

      default:
            break;
      }

      qDebug() << CurrentDayString;
      emit CurrentDayIntChanged();
      emit CurrentDayStringChanged();
}


void JsonParser::_ReadValue(signed int pDay) //deprecated
{


      QString Buffer {fJsonFile.readAll()};
      QJsonParseError error;

      fJsonDoc = QJsonDocument::fromJson(Buffer.toUtf8(), &error);
      if (error.error != QJsonParseError::NoError) {
            qDebug() << "JSON parsing error:" << error.errorString();
      } else {
            qDebug() << "JSON parsing successful!";
      }
      QJsonArray rootArray = fJsonDoc.array();
      QJsonValue ScheduleArray{rootArray[0]};

      QString FormattedString {ScheduleArray["schedule"][pDay].toObject()["day"].toString()}; //day
      //QObject
      QJsonArray Subjects{ScheduleArray["schedule"][pDay]["even"].toArray()};
      qDebug() << "\n день" << FormattedString;
      qDebug() << "\n предметы" << Subjects;
            //                               |*- массив массивов предметов   | массив из предметов | - объект предмета
      qDebug() << "\nКонкретный" << Subjects[0]                                           [1]                           [0]["name"]  ;   //qDebug() << "\nКонкретный" << Subjects[0][3]; - сис админ


      fJsonFile.close();
      fJsonFile.open(QIODevice::ReadWrite);
      emit SubjectChanged();
}





void JsonParser::_FillCurrentDayS()
{
      //delete later
      //CurrentDayInt = 5;

      if (Group == "")
      {
            qDebug() << "Group is empty";
            return;
      }
      QString Buffer {fJsonFile.readAll()};
      QJsonParseError error;
      fJsonDoc = QJsonDocument::fromJson(Buffer.toUtf8(), &error);
      if (error.error != QJsonParseError::NoError) {
            qDebug() << "JSON parsing error:" << error.errorString();
            qDebug() << Buffer;
            return;
      } else {
            qDebug() << "JSON parsing successful!";
      }


      ItemName.clear();
      TeacherName.clear();
      Place.clear();
      Type.clear();



      std::string OddEven{};
      if (Week % 2 == 0)
      {
            OddEven = "even";
      }
      else
      {
            OddEven = "odd";
      }


      QJsonArray rootArray = fJsonDoc.array();
      QJsonValue ScheduleArray{rootArray[0]};


      for (size_t Iterator{}; Iterator < 7; ++Iterator)
      {
            if (ScheduleArray["schedule"][CurrentDayInt][OddEven.c_str()][Iterator][0]["name"].toString() == "")
            {
                  continue;
            }
            else
            {
                  this->ItemName.push_back(ScheduleArray["schedule"][CurrentDayInt][OddEven.c_str()][Iterator][0]["name"].toString()); //todo put in one item and just "name" "tutor" etc
                  this->TeacherName.push_back(ScheduleArray["schedule"][CurrentDayInt][OddEven.c_str()][Iterator][0]["tutor"].toString());
                  this->Place.push_back(ScheduleArray["schedule"][CurrentDayInt][OddEven.c_str()][Iterator][0]["place"].toString());
                  this->Type.push_back(ScheduleArray["schedule"][CurrentDayInt][OddEven.c_str()][Iterator][0]["type"].toString());
                  this->Times.push_back(ScheduleArray["lessonsTimes"][CurrentDayInt][Iterator].toString());
                  qDebug() << Times[Iterator];
            }
            // qDebug() << ScheduleArray["schedule"][CurrentDayInt]["odd"][Iterator][0]["name"].toString();
            // qDebug() << ScheduleArray["schedule"][CurrentDayInt]["odd"][Iterator][0]["tutor"];
            // qDebug() << ScheduleArray["schedule"][CurrentDayInt]["odd"][Iterator][0]["place"];
            // qDebug() << ScheduleArray["schedule"][CurrentDayInt]["odd"][Iterator][0]["type"];
            // Subjects[Iterator].TeacherName = ScheduleArray["schedule"][CurrentDayInt]["odd"][Iterator][0]["tutor"].toString();
            // Subjects[Iterator].Place = ScheduleArray["schedule"][CurrentDayInt]["odd"][Iterator][0]["place"].toString();
            // Subjects[Iterator].Type = ScheduleArray["schedule"][CurrentDayInt]["odd"][Iterator][0]["type"].toString();

      }
      qDebug() << Week;
      // for (size_t Iterator{}; Iterator < Subjects.size(); ++Iterator)
      // {
      //       qDebug() << ItemName[Iterator] + " " << TeacherName[Iterator] + " " << Place[Iterator] + " " << Type[Iterator];
      // }
      emit ItemNameChanged();
      emit TeacherNameChanged();
      emit PlaceChanged();
      emit TypeChanged();
      fJsonFile.close();
      fJsonFile.open(QIODevice::ReadWrite);
}

void JsonParser::_PrintAmount()
{
      qDebug() << ItemName.size();
}

void JsonParser::_UpdateTime()
{
      CurrentTime = QDateTime::currentDateTime();

      qDebug() << CurrentTime.toString("hh:mm");;
}

void JsonParser::_ChangeCurentSubject()
{

      //CurrentTime = QDateTime::fromString("10:20", "hh:mm"); //delete later
      qDebug() << CurrentTime;
      qDebug() << "_GetCurentSubject called";
      for (size_t Iterator{}; Iterator < Times.size(); ++Iterator)
      {
            char *Token{std::strtok(const_cast<char*>(Times[Iterator].toStdString().c_str()), " -")};
            std::vector <std::string> tTimes{};

            for(;Token != nullptr;)
            {
                  tTimes.push_back(Token);
                  qDebug() << Token;
                  Token = std::strtok(nullptr, " ");
            }
            if (CurrentTime <= QDateTime::fromString(tTimes[0].c_str(), "hh:mm") && Iterator == 0)
            {
                  CurrentSubject = "Its not time yet";
                  qDebug() << "Its not time yet";
                  emit CurrentSubjectChanged();
                  return;
            }
            else if (CurrentTime >= QDateTime::fromString(tTimes[0].c_str(), "hh:mm") && CurrentTime <= QDateTime::fromString(tTimes[2].c_str(), "hh:mm"))
            {
                  CurrentSubject = ItemName[Iterator];
                  qDebug() << CurrentSubject;
                  emit CurrentSubjectChanged();
                  return;
            }
            else
            {
                  qDebug() << (CurrentTime >= QDateTime::fromString(tTimes[0].c_str(), "hh:mm"));
                  qDebug() << (CurrentTime <= QDateTime::fromString(tTimes[2].c_str(), "hh:mm"));
                  qDebug() << "Not this cycle " << tTimes[0] << tTimes[2];
            }
      }
      CurrentSubject = "How?";
      qDebug() << "How?";
      emit CurrentSubjectChanged();
      return;

}

void JsonParser::_StartCycle()
{
      fAttendanceResults.open("Attendance.txt", std::ios::out);
      fVectorAttendance.clear();
      if (!fAttendanceResults)
      {
            qDebug() << "error opening file";
      }

}

void JsonParser::_IterateCycle(QString pStudent, QString pState)
{
      if (pStudent == "" || pState == "")
      {
            return;
      }
      else
      {
            fVectorAttendance.push_back(std::make_pair(pStudent.toStdString(), pState.toStdString()));
            //fAttendanceResults << pStudent.toStdString() << ' ' << pState.toStdString() << '\n';
      }

}

void JsonParser::_SaveResults()
{
      size_t StaticIterator{};
      bool SizeExceeded{!(fVectorAttendance.size() > 0)};
      for (size_t Iterator{0}; Iterator < Students.size(); ++Iterator)
      {
            if (!SizeExceeded && fVectorAttendance[StaticIterator].first != Students[Iterator].toStdString())
            {
                  fVectorAttendance.push_back(std::make_pair(Students[Iterator].toStdString(), "-"));
            }
            else if (SizeExceeded)
            {
                  fVectorAttendance.push_back(std::make_pair(Students[Iterator].toStdString(), "-"));
            }
            else
            {
                  ++StaticIterator;
                  if (StaticIterator == fVectorAttendance.size())
                  {
                        SizeExceeded = true;
                  }
            }
      }
      for (size_t Iterator{}; Iterator < fVectorAttendance.size(); ++Iterator)
      {
            fAttendanceResults << fVectorAttendance[Iterator].first << " " << fVectorAttendance[Iterator].second << '\n';
            qDebug() << fVectorAttendance[Iterator].first << " " << fVectorAttendance[Iterator].second;
      }
      fAttendanceResults.close();
      qDebug() << "File endnd";
}

int JsonParser::_GetAmountStudents()
{
      return Students.size();
}

void JsonParser::_SetGroup(QString pGroup)
{
      this->Group = pGroup;
}
