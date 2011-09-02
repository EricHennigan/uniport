#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <QObject>
#include <QHash>

class Stock;
class Market;
class TickStream;

class Portfolio : public QObject
{
    Q_OBJECT

public:
    Portfolio();

    void add(Stock stock, qreal weight, qreal amount=0.0);
    void normalize();

    void subscribe(Market const *ts);
    qreal value(Market const &market) const;

private slots:
    void rebalance(Market const &market);

private:
    bool m_isNormalized;

    typedef struct Holding {
        qreal weight;
        qreal amount;
    } Holding;
    QHash<Stock, Holdings> m_holdings;
};

#endif // PORTFOLIO_H
