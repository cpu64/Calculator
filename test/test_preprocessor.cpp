#include <gtest/gtest.h>
#include "../calculator.hpp"


TEST(Test1, BasicAssertions) {
    EXPECT_NO_THROW(Calculator cal("4+3"));
}

TEST(Test2, BasicAssertions) {
    EXPECT_NO_THROW(Calculator cal("4--3"));
}

TEST(Test3, BasicAssertions) {
    EXPECT_THROW({
        try { Calculator cal("4+a3"); }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( "expression does not follow Calculator's grammar rules.", e.what() );
            throw;
        }
    }, std::invalid_argument );
}


TEST(Test4, BasicAssertions) {
    EXPECT_THROW({
        try { Calculator cal("4+*3"); }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( "expression does not follow Calculator's grammar rules.", e.what() );
            throw;
        }
    }, std::invalid_argument );
}


TEST(Test5, BasicAssertions) {
    EXPECT_THROW({
        try { Calculator cal("4+3-"); }
        catch( const std::invalid_argument& e )
        {
            EXPECT_STREQ( "expression does not follow Calculator's grammar rules.", e.what() );
            throw;
        }
    }, std::invalid_argument );
}

