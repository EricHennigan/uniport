#include "RecordedMarket.h"
#include <QTimer>
#include <QDateTime>

RecordedMarket::RecordedMarket()
    :m_record(QQueue<Tick>())
    ,m_timer(new QTimer(this))
{
}

void RecordedMarket::record(Stock stock, qreal price)
{
    m_record.enqueue(Tick(stock, price, QDateTime::currentDateTime()));
}

void RecordedMarket::play()
{
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(emitNextTick()));
    m_timer->start(10);
}

void RecordedMarket::emitNextTick()
{
    if (m_record.isEmpty())
        m_timer->stop();

    Tick t = m_record.dequeue();
    Market::update(t);
    emit Market::tick(t);
}


