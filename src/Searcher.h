#ifndef SEARCHER_H
#define SEARCHER_H
# include <QObject>
# include <QDebug>
# include <QString>
# include <QFile>

# include <fstream>
# include <string>
# include <unordered_set>
# include <QStringList>

class Searcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList _Items READ _GetItems WRITE _PopulateItems NOTIFY listPopulated) /*WRITE _SetItems
               NOTIFY _ItemsChanged*/
    QStringList _Items;
    std::fstream TeachersList;
    std::fstream CacheFile;
    std::unordered_set<std::string> Results;

    bool EndBit{ 1 };

    Q_PROPERTY(QString Cache READ Cache)

    QString _Cache;
public:
    QStringList _GetItems();
    void _PopulateItems(QStringList&);
    Q_INVOKABLE void _PrintItems();
    Q_INVOKABLE void _Search(QString Input);




    explicit Searcher(QObject *parent = nullptr);
    ~Searcher();
    std::unordered_set<std::string> Iterate(std::unordered_set<std::string>& aSet, std::string& Input, size_t Character);


    const QString &Cache() const;

signals:
    void listPopulated();
    void constructed();
};

#endif // SEARCHER_H
