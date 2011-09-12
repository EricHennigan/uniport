#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <QObject>
#include <QHash>

#include "Stock.h"
#include "Tick.h"
class Market;
class TickStream;

class Portfolio : public QObject
{
    Q_OBJECT

public:
    Portfolio(Market *market);

    void add(Stock stock, qreal weight, qreal amount=0.0);
    void normalizeWeights();

    qreal value() const;
    qreal value(Stock stock) const;
    qreal amount(Stock stock) const;
    qreal weight(Stock stock) const;

    QString serialize() const;

private slots:
    void rebalance(Tick tick);

private:
    typedef struct Holding {
        QString stock;
        qreal weight;
        qreal amount;
        QString serialize() const;
    } Holding;

    bool m_isNormalized;
    QHash<Stock, Holding> m_holdings;
    Market *m_market;
};

#endif // PORTFOLIO_H
