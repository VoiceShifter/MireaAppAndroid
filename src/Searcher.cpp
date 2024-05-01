# include "Searcher.h"

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
    TeachersList.open("data/Teachers.txt", std::ios::in); //в будущем надо будет сделать qml/data/Teachers.txt
    CacheFile.open("data/Cache.txt", std::ios::in);
    std::string Buffer{};


    for (;std::getline(CacheFile, Buffer);)
    {
        qDebug() << Buffer.c_str();
    }
    _Cache = Buffer.c_str();
    qDebug() << _Cache;
    if (!TeachersList.is_open())
    {
        qDebug() << "File Teachers not found\n";
    }
    if (!CacheFile.is_open())
    {
        qDebug() << "File CacheFile not found \n";
    }
    CacheFile.close();

}

Searcher::~Searcher()
{

}

void Searcher::_Search(QString aInput)
{



    CacheFile.open("data/Cache.txt", std::ios::out);
    Results.clear();
    CacheFile << aInput.toStdString();

    size_t Character{1};
    std::string Buffer{}, Input{aInput.toStdString()};

    qDebug() << aInput << '\n';

    for (; std::getline(TeachersList, Buffer);)
    {
        if (Buffer[0] == Input[0])
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
    TeachersList.close();
    TeachersList.open("data/Teachers.txt", std::ios::in); //в будущем надо будет сделать qml/data/Teachers.txt
    _Items.clear();

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
