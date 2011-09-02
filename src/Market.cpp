#include "Market.h"

Market::Market(QObject *parent)
    : QObject(parent)
    , m_prices(QHash<Stock,Tick>())
{
}

void Market::update(Tick const &t)
{
    m_prices[t.stock()] = t;
    emit tick(t;
}

void Market::subscribe(TickStream const *ts)
{
    connect(ts, SIGNAL(tick(Tick const &tick)),
            this, SLOT(update(Tick const &tick)));
}
