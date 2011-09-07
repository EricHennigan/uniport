#ifndef MARKET_H
#define MARKET_H

#include <QObject>
#include <QHash>

#include "Stock.h"
#include "Tick.h"
#include "TickStream.h"

class Market : public TickStream
{
    Q_OBJECT
public:
    explicit Market(QObject *parent = 0);

    void subscribe(TickStream const *ts);
    Tick operator[](Stock const &stock) const;

signals:
    void tick(Tick const &tick);

public slots:
    void update(Tick const &tick);

private:
    QHash<Stock, Tick> m_prices;
};

#endif // MARKET_H
