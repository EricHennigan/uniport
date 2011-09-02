#ifndef MARKET_H
#define MARKET_H

#include <QObject>
#include <QHash>

class Tick;
class Stock;
class TickStream;

class Market : public QObject
{
    Q_OBJECT
public:
    explicit Market(QObject *parent = 0);

    void subscribe(TickStream const *ts);

signals:
    void tick(Tick const &tick);

public slots:
    void update(Tick const &tick);

private:
    QHash<Stock, Tick> m_prices;
};

#endif // MARKET_H
