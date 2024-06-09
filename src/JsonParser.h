# ifndef JSONPARSER_H
# define JSONPARSER_H

# include <QObject>
# include <QtNetwork>
# include <QDateTime>
# include <fstream>
# include <utility>



class JsonParser : public QObject
{
    Q_OBJECT
public:
    explicit JsonParser(QObject *parent = nullptr);
    ~JsonParser();
    QNetworkAccessManager fManager;
    QNetworkRequest fRequest;
    QNetworkReply *fReply;
    QString fStringReply;
    QJsonArray fJson;
    QFile fJsonFile;
    QJsonDocument fJsonDoc;
    QJsonObject fJsonObject;

    std::vector<std::pair<std::string, std::string>> fVectorAttendance;
    std::fstream fAttendanceResults;


    QJsonArray getFJson() const;
    void setFJson(const QJsonArray &newFJson);
    Q_INVOKABLE void _GetReply();
    Q_INVOKABLE void _ReadJson();
    Q_INVOKABLE void _ReadValue(signed int pDay = -1);
    Q_INVOKABLE void _IncrementDay();
    Q_INVOKABLE void _DecrementDay();
    Q_INVOKABLE void _FillCurrentDayS();
    Q_INVOKABLE void _PrintAmount();
    Q_INVOKABLE void _UpdateTime();
    Q_INVOKABLE void _ChangeCurentSubject();
    Q_INVOKABLE void _StartCycle();
    Q_INVOKABLE void _IterateCycle(QString, QString);
    Q_INVOKABLE void _SaveResults();
    Q_INVOKABLE int _GetAmountStudents();
    Q_INVOKABLE void _SetGroup(QString);






    QStringList getCurrentDayItems() const;
    void setCurrentDayItems(const QStringList &newCurrentDayItems);
    int getCurrentDayInt() const;
    void setCurrentDayInt(int newCurrentDayInt);


    QStringList getCurrentDayCabs() const;
    void setCurrentDayCabs(const QStringList &newCurrentDayCabs);
    QStringList TeacherName;
    QStringList ItemName;
    QStringList Place;
    QStringList Type;
    QStringList Times;

    QStringList Students;


    signed int Week;





    QStringList getTeacherName() const;
    void setTeacherName(const QStringList &newTeacherName);

    QStringList getItemName() const;
    void setItemName(const QStringList &newItemName);

    QStringList getPlace() const;
    void setPlace(const QStringList &newPlace);

    QStringList getType() const;
    void setType(const QStringList &newType);


    signed int getWeek() const;
    Q_INVOKABLE void _GetWeekReply();
    void setWeek(signed int newWeek);

    QStringList getStudents() const;
    void setStudents(const QStringList &newStudents);

    QStringList getTimes() const;
    void setTimes(const QStringList &newTimes);

    QString getCurrentSubject() const;
    void setCurrentSubject(const QString &newCurrentSubject);

    QString getCurrentDayString() const;
    void setCurrentDayString(const QString &newCurrentDayString);

signals:
    void fJsonChanged();
    void CurrentDayItemsChanged();
    void CurrentDayIntChanged();
    void CurrentDayCabsChanged();
    void SubjectChanged();


    void TeacherNameChanged();

    void ItemNameChanged();

    void PlaceChanged();

    void TypeChanged();

    void WeekChanged();

    void StudentsChanged();

    void TimesChanged();

    void CurrentSubjectChanged();

    void CurrentDayStringChanged();

private:
    Q_PROPERTY(QJsonArray fJson READ getFJson WRITE setFJson NOTIFY fJsonChanged FINAL)
    Q_PROPERTY(QStringList CurrentDayItems READ getCurrentDayItems WRITE setCurrentDayItems NOTIFY CurrentDayItemsChanged FINAL)
    Q_PROPERTY(int CurrentDayInt READ getCurrentDayInt WRITE setCurrentDayInt NOTIFY CurrentDayIntChanged FINAL)
    Q_PROPERTY(QStringList CurrentDayCabs READ getCurrentDayCabs WRITE setCurrentDayCabs NOTIFY CurrentDayCabsChanged FINAL)


    int CurrentDayInt{};
    QString CurrentDayString{};
    QStringList CurrentDayItems{};
    QStringList CurrentDayCabs{};
    QStringList CurrentDayTimes{};
    QDateTime CurrentTime;
    QString CurrentSubject;
    QString Group;





    Q_PROPERTY(QStringList _TeacherName READ getTeacherName WRITE setTeacherName NOTIFY TeacherNameChanged FINAL)
    Q_PROPERTY(QStringList _ItemName READ getItemName WRITE setItemName NOTIFY ItemNameChanged FINAL)
    Q_PROPERTY(QStringList _Place READ getPlace WRITE setPlace NOTIFY PlaceChanged FINAL)
    Q_PROPERTY(QStringList _Type READ getType WRITE setType NOTIFY TypeChanged FINAL)
    Q_PROPERTY(QStringList _Students READ getStudents WRITE setStudents NOTIFY StudentsChanged FINAL)
    Q_PROPERTY(signed int Week READ getWeek WRITE setWeek NOTIFY WeekChanged FINAL)
    Q_PROPERTY(QStringList _Times READ getTimes WRITE setTimes NOTIFY TimesChanged FINAL)
    Q_PROPERTY(QString _CurrentSubject READ getCurrentSubject WRITE setCurrentSubject NOTIFY CurrentSubjectChanged FINAL)
    Q_PROPERTY(QString _CurrentDayString READ getCurrentDayString WRITE setCurrentDayString NOTIFY CurrentDayStringChanged FINAL)
};


#endif // JSONPARSER_H
