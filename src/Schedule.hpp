#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

# include <QtNetwork/QUdpSocket>
# include <QObject>
# include <vector>
# include <QStringList>
struct DaysContentStruct : public QObject
{
      Q_OBJECT

  public:
      QStringList TeacherNames{};
      QStringList ItemNames{};
      QStringList Places{};
      QStringList Types{};
      QString     Day{};
      QStringList getTeacherNames() const;
      void setTeacherNames(const QStringList &newTeacherNames);
      QStringList getItemNames() const;
      void setItemNames(const QStringList &newItemNames);
      QStringList getPlaces() const;
      void setPlaces(const QStringList &newPlaces);
      QStringList getTypes() const;
      void setTypes(const QStringList &newTypes);
      QString getDay() const;
      void setDay(const QString &newDay);

  signals:
      void TeacherNamesChanged();
      void ItemNamesChanged();
      void PlacesChanged();
      void TypesChanged();
      void DayChanged();

  private:
      Q_PROPERTY(QStringList _TeacherNames READ getTeacherNames WRITE setTeacherNames NOTIFY TeacherNamesChanged)
      Q_PROPERTY(QStringList _ItemNames    READ getItemNames    WRITE setItemNames    NOTIFY ItemNamesChanged   )
      Q_PROPERTY(QStringList _Places       READ getPlaces       WRITE setPlaces       NOTIFY PlacesChanged      )
      Q_PROPERTY(QStringList _Types        READ getTypes        WRITE setTypes        NOTIFY TypesChanged       )
      Q_PROPERTY(QString     _Day          READ getDay          WRITE setDay          NOTIFY DayChanged         )
};

class Schedule : public QObject
{
      Q_OBJECT
      QUdpSocket  MainSocket;
      std::string CurrentGroup{};
      QString UserName{};
      void ProcessFile(std::string& FilePath)noexcept;
      void ProcessTeachersFile(std::string& FilePath);      
      QString ErrorMessage{};
      QString QCurrentGroup{};
  public:
      explicit Schedule(QObject *parent = nullptr);
      QVector<DaysContentStruct*> Days;
      QVector<DaysContentStruct*> OddDays;
      QVector<DaysContentStruct*> EvenDays;
      void PrepareStructures();
      std::vector<std::string> DaysStringArray{"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", "ЧЕТВЕРГ", "ПЯТНИЦА",
                                                "СУББОТА", "ВОСКРЕСЕНЬЕ"};
      signed int  CurrentDayInt{};
      signed int  CurrentWeekNumber{};
      std::string CurrentDayString{};


      Q_INVOKABLE void _LoadDefault();
      Q_INVOKABLE void _IncrementDay(signed int Value);
      Q_INVOKABLE int _ChangeSchedule(QString Filename);
      Q_INVOKABLE signed int _SubjectClicked(QString SubjectName);
      bool RequestScheduleFile(std::string& Filename);
      bool TrySubject(std::string &SubjectName, std::string &UserName);

      signed int       DifferentiateDay();
      void ParseFileSchedule(std::string& Filename);

      QVector<DaysContentStruct*> getDays() const;
      QVector<DaysContentStruct*> OddgetDays() const;
      QVector<DaysContentStruct*> EvengetDays() const;

      void setDays(const QVector<DaysContentStruct*> &newDays);
      void setCurrentDayInt(int newCurrentDayInt);
      int getCurrentDayInt() const;

      signed int getCurrentWeekNumber() const;
      void setCurrentWeekNumber(signed int newCurrentWeekNumber);

      QString getUserName() const;
      void setUserName(const QString &newUserName);

      QString getErrorMessage() const;
      void setErrorMessage(const QString &newErrorMessage);

      QString getQCurrentGroup() const;
      void setQCurrentGroup(const QString &newQCurrentGroup);

  signals:
      void DaysChanged();
      void OddDaysChanged();
      void EvenDaysChanged();
      void CurrentDayIntChanged();
      void CurrentWeekNumberChanged();

      void UserNameChanged();

      void ErrorMessageChanged();

      void QCurrentGroupChanged();

  private:
      Q_PROPERTY(QVector<DaysContentStruct*> _Days READ getDays WRITE setDays NOTIFY DaysChanged FINAL)
      Q_PROPERTY(QVector<DaysContentStruct*> _OddDays READ OddgetDays NOTIFY OddDaysChanged FINAL)
      Q_PROPERTY(QVector<DaysContentStruct*> _EvenDays READ EvengetDays NOTIFY EvenDaysChanged FINAL)
      Q_PROPERTY(signed int _CurrentWeekNumber READ getCurrentWeekNumber WRITE setCurrentWeekNumber NOTIFY CurrentWeekNumberChanged FINAL)
      Q_PROPERTY(signed int _CurrentDayInt READ getCurrentDayInt WRITE setCurrentDayInt NOTIFY CurrentDayIntChanged FINAL)
      Q_PROPERTY(QString _UserName READ getUserName WRITE setUserName NOTIFY UserNameChanged FINAL)
      Q_PROPERTY(QString _ErrorMessage READ getErrorMessage WRITE setErrorMessage NOTIFY ErrorMessageChanged FINAL)
      Q_PROPERTY(QString _QCurrentGroup READ getQCurrentGroup WRITE setQCurrentGroup NOTIFY QCurrentGroupChanged FINAL)
};

#endif // SCHEDULE_HPP
