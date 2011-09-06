#ifndef TICKSTREAM_H
#define TICKSTREAM_H

#include <QObject>
class Tick;

class TickStream : public QObject
{
    Q_OBJECT
public:
    TickStream();

signals:
    void tick(Tick const &tick);

};

#endif
