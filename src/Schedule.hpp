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
      void ProcessFile(std::string& FilePath, std::string& CurrentDay)noexcept;

  public:
      explicit Schedule(QObject *parent = nullptr);
      bool RequestScheduleFile(std::string& Filename);
      void ParseFileSchedule(std::string& Filename);
      QVector<DaysContentStruct*> Days;
      int CurrentDayInt{};
      std::string CurrentDayString{};
      Q_INVOKABLE void LoadDefault();
      QVector<DaysContentStruct*> getDays() const;
      void setDays(const QVector<DaysContentStruct*> &newDays);
      signed int DifferentiateDay();
  signals:
      void DaysChanged();
  private:
      Q_PROPERTY(QVector<DaysContentStruct*> _Days READ getDays WRITE setDays NOTIFY DaysChanged FINAL)
};

#endif // SCHEDULE_HPP
