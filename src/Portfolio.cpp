
#include "Portfolio.h"
#include "Stock.h"
#include "Market.h"
#include "Tick.h"

#include <QString>
//#include <QDebug>

Portfolio::Portfolio(Market *market)
    :m_isNormalized(false)
    ,m_holdings(QHash<Stock, Portfolio::Holding>())
    ,m_market(market)
{
    Q_ASSERT(market);
    connect(market, SIGNAL(tick(Tick)), this, SLOT(rebalance(Tick)));
}

void Portfolio::add(Stock stock, qreal weight, qreal amount)
{
    Q_ASSERT(!m_holdings.contains(stock));
    Q_ASSERT(0.0 <= weight && weight <= 1.0);
    Holding holding;
    holding.weight = weight;
    holding.amount = amount;
    m_holdings.insert(stock, holding);
    m_isNormalized = false;
}

void Portfolio::normalizeWeights()
{
    Q_ASSERT(!m_isNormalized);

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

qreal Portfolio::value() const
{
    Q_ASSERT(m_isNormalized);

    qreal val = 0.0;
    QHashIterator<Stock, Holding> i(m_holdings);
    while (i.hasNext()) {
        i.next();
        val += i.value().amount * m_market->lookup(i.key()).price();
    }
    return val;
}

qreal Portfolio::value(Stock stock) const
{
    Q_ASSERT(m_isNormalized);
    Q_ASSERT(m_holdings.contains(stock));

    qreal amount = m_holdings[stock].amount;
    qreal value = m_market->lookup(stock).price();
    return amount * value;
}

qreal Portfolio::amount(Stock stock) const
{
    Q_ASSERT(m_isNormalized);
    Q_ASSERT(m_holdings.contains(stock));

    return m_holdings[stock].amount;
}

qreal Portfolio::weight(Stock stock) const
{
    Q_ASSERT(m_isNormalized);
    Q_ASSERT(m_holdings.contains(stock));

    return m_holdings[stock].weight;
}

void Portfolio::rebalance(Tick tick)
{
    // TODO: will have to work out a discrete rebalance algorithm
    //       should really be based on share increments
    //       and take into account the discrete distance from ideal investment
    //qDebug() << "am rebalancing the portfolio";
    Q_ASSERT(m_isNormalized);

    qreal totalValue = value();
    //qDebug() << " total holdings at:\t" << totalValue << "dollars";
    QMutableHashIterator<Stock, Holding> i(m_holdings);
    while(i.hasNext()) {
        i.next();
        Stock stock = i.key();
        //qDebug() << " adjusting stock " << stock;
        qreal expected = totalValue * weight(stock);
        //qDebug() << "  expected to have:\t" << expected << "dollars";
        qreal actual = amount(stock) * m_market->lookup(stock).price();
        //qDebug() << "  actually have:\t" << actual << "dollars";
        qreal adjust = (expected - actual) / m_market->lookup(stock).price();
        //qDebug() << "  will have to adjust:\t" << adjust << "shares";

        if (qAbs(adjust) > .01)
            i.value().amount += adjust;
    }
}

QString Portfolio::serialize() const
{
    QString str;
    str += "(Portfolio";
    QHashIterator<Stock, Holding> i(m_holdings);
    while(i.hasNext()) {
        i.next();
        str += i.key() + ": ";
        str += i.value().serialize();
    }
    str += ")";

    return str;
}

QString Portfolio::Holding::serialize() const
{
    return QString("(Holding (weight %2) (amount %3))")
            .arg(weight)
            .arg(amount);
}
