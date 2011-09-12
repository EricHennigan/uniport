#include "Market.h"
#include "Tick.h"
#include "TickStream.h"

Market::Market(QObject *parent)
    : TickStream(parent)
    , m_prices(QHash<Stock,Tick>())
{
}

void Market::update(Tick const &t)
{
    m_prices[t.stock()] = t;
    emit tick(t);
}

void Market::subscribe(TickStream const *ts)
{
    connect(ts, SIGNAL(tick(Tick const &tick)),
            this, SLOT(update(Tick const &tick)));
}

Tick Market::lookup(Stock const &stock) const
{
    Q_ASSERT(m_prices.contains(stock));
    Tick const &t = m_prices[stock];
    Q_ASSERT(t.isValid());
    return t;
}
