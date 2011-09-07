#include <QString>
#include <QtTest/QtTest>

#include "../src/Stock.h"
#include "../src/Portfolio.h"
#include "RecordedMarket.h"

class TestPortfolio : public QObject
{
    Q_OBJECT

public:
    TestPortfolio();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void computes_value_correctly();
    //void testCase1_data();
};

TestPortfolio::TestPortfolio()
{
}

void TestPortfolio::initTestCase()
{
}

void TestPortfolio::cleanupTestCase()
{
}

void TestPortfolio::computes_value_correctly()
{
    Portfolio *p = new Portfolio();
    p->add(USD, .5);
    p->add(BITCOIN, .5);
    p->normalizeWeights();

    RecordedMarket *ts = new RecordedMarket();
    ts->record(USD, 1.0);
    ts->record(BITCOIN, 3.0);

    p->subscribe(ts);
    ts->play();

    QCOMPARE(p->value(*ts), 1.0);

    delete ts;
    delete p;
}

/*
void TestPortfolio::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void TestPortfolio::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}
*/

QTEST_APPLESS_MAIN(TestPortfolio);

#include "test_portfolio.moc"
