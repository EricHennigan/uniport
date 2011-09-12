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

    void initialize(Stock stock, qreal price);
    void record(Stock stock, qreal price);
    void play();

private:
    QQueue<Tick> m_record;
};

#endif // RECORDEDTICKSTREAM_H
