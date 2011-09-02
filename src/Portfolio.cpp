#include "Portfolio.h"

Portfolio::Portfolio()
    : m_isNormalized(false)
    , m_holdings(QHash<Stock, Portfolio::Holding>())
{
}

void Portfolio::add(Stock stock, qreal weight, qreal amount)
{
    Q_ASSERT(!m_weights.contains(stock));
    Q_ASSERT(0.0 <= weight && weight <= 1.0);
    Holding h;
    h.weight = weight;
    h.amount = amount;
    m_weights.insert(stock, h);
    m_isNormalized = false;
}

void Portfolio::normalize()
{
    qreal total = 0.0;
    foreach(Holding h, m_holdings)
        total += h.weight;

    QMutableHashIterator<Stock, Holding> i(m_holdings);
    while (i.hasNext()) {
        i.next();
        i.value().weight = i.value().weight / total;
    }
    m_isNormalized = true;
}

void Portfolio::subscribe(Market const *ts)
{
    Q_ASSERT(m_isNormalized);

    Q_ASSERT(false); // todo: implement this
    //QObject::connect( ... )
}

qreal Portfolio::value(Market const &market) const
{
    Q_ASSERT(m_isNormalized);

    qreal val = 0.0;
    QHashIterator<Stock, Holding> i(m_holdings);
    while (i.hasNext()) {
        i.next();
        val += i.value().amount * market[i.key()];
    }
    return val;
}

void Portfolio::rebalance(Market const &market)
{
    Q_ASSERT(m_isNormalized);
    Q_ASSERT(false); // todo: must test this first

    qreal value = value(market);
    QMutableHashIterator<Stock, Holding> i(m_holdings);
    while(i.hasNext()) {
        i.next();
        qreal expected = i.value().weight * market[i.key()];
        qreal actual = i.value().amount * market[i.key()];
        qreal adjust = i.value().amount - (actual - expected) / i.value().weight;
        // TODO: better threshold for rebalancing,
        //       should really be based on share increments
        if (qAbs(adjust) > .01)
            i.value().amount += adjust;
    }
}

