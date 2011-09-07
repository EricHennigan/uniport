#ifndef RECORDEDTICKSTREAM_H
#define RECORDEDTICKSTREAM_H

#include "../src/Market.h"
#include <QTimer>
#include <QQueue>

class RecordedMarket : public Market
{
    Q_OBJECT
public:
    RecordedMarket();

    void record(Stock, qreal price);
    void play();

private slots:
    void emitNextTick();

private:
    QQueue<Tick> m_record;
    QTimer *m_timer;
};

#endif // RECORDEDTICKSTREAM_H
