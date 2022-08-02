#ifndef TEST_MOD_H
#define TEST_MOD_H

#include "Test_log_pas.h"
#include <QObject>
#include <QTest>

class Test_log_pas:public QObject{
    Q_OBJECT
public:
    Test_log_pas(){};   // Конструктор класса
private slots:
    void test(){
        Log_pas lp;
        // Проведение тестов
        QCOMPARE(lp.Reg("19d039", "123"), true);
        QCOMPARE(lp.Reg("10d112", "Querty"), true);
        QCOMPARE(lp.Reg("11d167", "Qwery*56"), true);
        QCOMPARE(lp.Reg("1", "abcd"), true);
        QCOMPARE(lp.Reg("9090", "qt*7"), true);
        QCOMPARE(lp.Reg("11d16", "13"), true);
        QCOMPARE(lp.Reg("aaaa", "abcabc"), true);
    }
};



#endif // TEST_MOD_H
