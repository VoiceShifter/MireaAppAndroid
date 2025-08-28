#ifndef RESETER_HPP
#define RESETER_HPP

#include <QObject>

class Reseter : public QObject
{
      Q_OBJECT
public:
      explicit Reseter(QObject *parent = nullptr);
      Q_INVOKABLE void _Reset();
signals:
};

#endif // RESETER_HPP
