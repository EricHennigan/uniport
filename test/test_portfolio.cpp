#include <QString>
#include <QtTest>

#include "../src/Stock.h"
#include "../src/Portfolio.h"
#include "RecordedMarket.h"

class TestPortfolio : public QObject
{
    Q_OBJECT

public:
    TestPortfolio();

private Q_SLOTS:
    void Portfolio_correctly_initializes();
    void Portfolio_correctly_rebalances();
    void Portfolio_makes_money_on_random_stock();
};

TestPortfolio::TestPortfolio()
{
}

void TestPortfolio::Portfolio_correctly_initializes()
{
    RecordedMarket *market = new RecordedMarket();
    market->initialize(USD, 1.0);
    market->initialize(BITCOIN, 1.0);

    Portfolio *p = new Portfolio(market);
    p->add(USD, .5, 100.);
    p->add(BITCOIN, .5, 100.);
    p->normalizeWeights();

    QCOMPARE(p->value(), 200.);

    delete p;
    delete market;
}

void TestPortfolio::Portfolio_correctly_rebalances()
{
    RecordedMarket *ts = new RecordedMarket();
    ts->initialize(USD, 1.0);
    ts->initialize(BITCOIN, 1.0);
    ts->record(BITCOIN, 0.5);

    Portfolio *p = new Portfolio(ts);
    p->add(USD, .5, 200.);
    p->add(BITCOIN, .5, 0.);
    p->normalizeWeights();

    ts->play();

    QCOMPARE(p->value(), 200.);
    QCOMPARE(p->amount(USD), 100.);
    QCOMPARE(p->amount(BITCOIN), 200.);

    delete p;
    delete ts;
}

double rand_in_range(int low, int high)
{
    Q_ASSERT(high > low);
    Q_ASSERT(high > 0);
    Q_ASSERT(low > 0);

    int r = qrand();
    return low + (r / (double)RAND_MAX) * (high - low);
}

void TestPortfolio::Portfolio_makes_money_on_random_stock()
{
    // TODO: is this test actually doing what it should?
    Q_ASSERT(false);

    RecordedMarket *ts = new RecordedMarket();
    ts->initialize(USD, 1.0);
    ts->initialize(BITCOIN, 0.5);
    for(int i=0; i<10; ++i)
        ts->record(BITCOIN, rand_in_range(1, 10));

    Portfolio *p = new Portfolio(ts);
    p->add(USD, .5, 50.);
    p->add(BITCOIN, .5, 50.);
    p->normalizeWeights();

    ts->play();

    QVERIFY(p->value() > 200.);

    delete p;
    delete ts;
}

QTEST_MAIN(TestPortfolio);
#include "test_portfolio.moc"
