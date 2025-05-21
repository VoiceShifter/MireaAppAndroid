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
      std::string UserName{};
      void ProcessFile(std::string& FilePath)noexcept;

  public:
      explicit Schedule(QObject *parent = nullptr);
      QVector<DaysContentStruct*> Days;
      QVector<DaysContentStruct*> OddDays;
      QVector<DaysContentStruct*> EvenDays;

      signed int  CurrentDayInt{};
      signed int  CurrentWeekNumber{};
      std::string CurrentDayString{};

      Q_INVOKABLE void _LoadDefault();
      Q_INVOKABLE void _IncrementDay(signed int Value);
      Q_INVOKABLE bool _ChangeSchedule(QString Filename);
      bool RequestScheduleFile(std::string& Filename);

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

  signals:
      void DaysChanged();
      void OddDaysChanged();
      void EvenDaysChanged();
      void CurrentDayIntChanged();
      void CurrentWeekNumberChanged();

  private:
      Q_PROPERTY(QVector<DaysContentStruct*> _Days READ getDays WRITE setDays NOTIFY DaysChanged FINAL)
      Q_PROPERTY(QVector<DaysContentStruct*> _OddDays READ OddgetDays NOTIFY OddDaysChanged FINAL)
      Q_PROPERTY(QVector<DaysContentStruct*> _EvenDays READ EvengetDays NOTIFY EvenDaysChanged FINAL)
      Q_PROPERTY(signed int _CurrentWeekNumber READ getCurrentWeekNumber WRITE setCurrentWeekNumber NOTIFY CurrentWeekNumberChanged FINAL)
      Q_PROPERTY(signed int _CurrentDayInt READ getCurrentDayInt WRITE setCurrentDayInt NOTIFY CurrentDayIntChanged FINAL)
};

#endif // SCHEDULE_HPP
