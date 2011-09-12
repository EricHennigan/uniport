
#include "Tick.h"
#include <QtGlobal>

Tick::Tick()
    :m_dateTime()
    ,m_stock(INVALID)
    ,m_price(-0.0) // TODO: want to store NaN ?
{
}

Tick::Tick(Stock const &stock, qreal const price, QDateTime const &dateTime)
    :m_dateTime(dateTime)
    ,m_stock(stock)
    ,m_price(price)
{
}

bool Tick::isValid() const
{
    return m_dateTime.isValid() && (m_price != -0.0);
}

QDateTime Tick::dateTime() const
{
    return m_dateTime;
}

QDate Tick::date() const
{
    return m_dateTime.date();
}

QTime Tick::time() const
{
    return m_dateTime.time();
}

Stock Tick::stock() const
{
    return m_stock;
}

qreal Tick::price() const
{
    return m_price;
}

/*
Tick& Tick::operator=(Tick const &t)
{
    m_dateTime = t.m_dateTime;
    m_stock = t.m_stock;
    m_price = t.m_price;
}
*/
