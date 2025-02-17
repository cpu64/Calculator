#include <gtest/gtest.h>
#include "../calculator.hpp"


TEST(Test1, BasicAssertions) {
    Calculator cal("4+3");
    EXPECT_STRCASEEQ(cal.print().c_str(), "(4+3)");
    EXPECT_EQ(cal.solve(), 7);
}


TEST(Test2, BasicAssertions) {
    Calculator cal("4+5*15-(45)*(-89/5)");
    EXPECT_STRCASEEQ(cal.print().c_str(), "((4+(5*15))-(45*((-89)/5)))");
    EXPECT_EQ(cal.solve(), 880);
}


TEST(Test3, BasicAssertions) {
    Calculator cal("(5 - 3) *  10 * -2 / 5");
    EXPECT_STRCASEEQ(cal.print().c_str(), "((((5-3)*10)*(-2))/5)");
    EXPECT_EQ(cal.solve(), -8);
}


TEST(Test4, BasicAssertions) {
    Calculator cal("4+5*15-(45)*7-5*(5/55)*(846-495-4--1)");
    EXPECT_STRCASEEQ(cal.print().c_str(), "(((4+(5*15))-(45*7))-((5*(5/55))*(((846-495)-4)-(-1))))");
    EXPECT_EQ(cal.solve(), -394.18181818181818181818);
}

TEST(Test5, BasicAssertions) {
    Calculator cal("(-495*-4--1)");
    EXPECT_STRCASEEQ(cal.print().c_str(), "(((-495)*(-4))-(-1))");
    EXPECT_EQ(cal.solve(), 1981);
}
