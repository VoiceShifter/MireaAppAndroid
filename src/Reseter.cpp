#include "Reseter.hpp"
#include <ios>
# include <fstream>
Reseter::Reseter(QObject *parent)
      : QObject{parent}
{}

void Reseter::_Reset()
{
      std::fstream CacheFile;
      CacheFile.open("Files/Cache.txt", std::ios_base::out);
      CacheFile.close();
}
