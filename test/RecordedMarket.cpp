#include "RecordedMarket.h"
#include <QTimer>
#include <QDateTime>
#include <QEventLoop>
#include <QTest>

RecordedMarket::RecordedMarket()
    :m_record(QQueue<Tick>())
{
}

void RecordedMarket::initialize(Stock stock, qreal price)
{
    m_prices[stock] = Tick(stock, price, QDateTime::currentDateTime());
}

void RecordedMarket::record(Stock stock, qreal price)
{
    m_record.enqueue(Tick(stock, price, QDateTime::currentDateTime()));
}

void RecordedMarket::play()
{
    while(!m_record.isEmpty()) {
        Tick t = m_record.dequeue();
        QTest::qWait(10);
        Market::update(t);
    }
}
