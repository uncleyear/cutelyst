#ifndef DISPATCHERTEST_H
#define DISPATCHERTEST_H

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "headers.h"
#include "coverageobject.h"

#include <Cutelyst/application.h>
#include <Cutelyst/controller.h>
#include <Cutelyst/headers.h>

using namespace Cutelyst;

class TestDispatcher : public CoverageObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();

    void testController_data();
    void testController() {
        doTest();
    }

    void cleanupTestCase();

private:
    TestEngine *m_engine;

    TestEngine* getEngine();

    void doTest();

};

void TestDispatcher::initTestCase()
{
    m_engine = getEngine();
    QVERIFY(m_engine);
}

TestEngine* TestDispatcher::getEngine()
{
    TestEngine *engine = new TestEngine(QVariantMap(), this);
    if (!engine->initApplication(new TestApplication, true)) {
        return nullptr;
    }
    return engine;
}


void TestDispatcher::cleanupTestCase()
{
    delete m_engine;
}

void TestDispatcher::doTest()
{
    QFETCH(QString, url);
    QFETCH(QByteArray, output);

    QUrl urlAux(url.mid(1));

    QByteArray result = m_engine->createRequest(QStringLiteral("GET"),
                                                urlAux.path(),
                                                urlAux.query(QUrl::FullyEncoded).toLatin1(),
                                                Headers(),
                                                nullptr);

    QCOMPARE( result, output );
}

void TestDispatcher::testController_data()
{
    QTest::addColumn<QString>("url");
    QTest::addColumn<QByteArray>("output");

    // Chained dispatcher
    QTest::newRow("chained-test00") << QStringLiteral("/root") << QByteArrayLiteral("/root");
    QTest::newRow("chained-test01") << QStringLiteral("/root/") << QByteArrayLiteral("/root");
    QTest::newRow("chained-test02") << QStringLiteral("/root////") << QByteArrayLiteral("/root");
    QTest::newRow("chained-test03") << QStringLiteral("/root/item") << QByteArrayLiteral("/root");
    QTest::newRow("chained-test04") << QStringLiteral("/root/item/") << QByteArrayLiteral("/root");

    QTest::newRow("chained-test05") << QStringLiteral("/chain/item") << QByteArrayLiteral("/chain/item[MANY]/");
    QTest::newRow("chained-test06") << QStringLiteral("/chain/item/") << QByteArrayLiteral("/chain/item[MANY]/");
    QTest::newRow("chained-test07") << QStringLiteral("/chain/item/foo") << QByteArrayLiteral("/chain/item[ONE]/foo");
    QTest::newRow("chained-test08") << QStringLiteral("/chain/item/foo/bar") << QByteArrayLiteral("/chain/item[MANY]/foo/bar");

    QTest::newRow("chained-test09") << QStringLiteral("/chain/midle/one/two/end") << QByteArrayLiteral("/chain/midle/one/two/end");
    QTest::newRow("chained-test10") << QStringLiteral("/chain/midle/TWO/ONE/end") << QByteArrayLiteral("/chain/midle/TWO/ONE/end");
    QTest::newRow("chained-test11") << QStringLiteral("/chain/midle/one/two/end/") << QByteArrayLiteral("/chain/midle/one/two/end");
    QTest::newRow("chained-test12") << QStringLiteral("/chain/midle/TWO/ONE/end/1/2/3/4/5") << QByteArrayLiteral("/chain/midle/TWO/ONE/end/1/2/3/4/5");
}

QTEST_MAIN(TestDispatcher)

#include "testdispatcherchained.moc"

#endif
