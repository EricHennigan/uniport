#ifndef TICK_H
#define TICK_H

#include "Stock.h"
#include <QDateTime>

class Tick
{
public:
    Tick();
    Tick(Stock const &stock, qreal const price, QDateTime const &dateTime);

public:
    QDateTime dateTime() const;
    QDate date() const;
    QTime time() const;

    Stock stock() const;
    qreal price() const;

    //Tick& operator=(Tick const &t);

private:
    // TODO: would like to make these const
    //       but can't because we use operator= to put into hash
    QDateTime m_dateTime;
    Stock m_stock;
    qreal m_price;
};

#endif // TICK_H
