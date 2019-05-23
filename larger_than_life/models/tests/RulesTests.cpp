#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BoardTests
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../src/Rules.h"

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingRange )
{
    const Rules rules = Rules(1, 1, 1, 1, 1, 1, 1, 1);
    BOOST_CHECK_EQUAL(1, rules.GetRange());
} 

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingStates )
{
    const Rules rules = Rules(1, 1, 1, 1, 1, 1, 1, 1);
    BOOST_CHECK_EQUAL(1, rules.GetStates());
} 

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingMiddle )
{
    const Rules rules = Rules(1, 1, 1, 1, 1, 1, 1, 1);
    BOOST_CHECK_EQUAL(1, rules.GetMiddle());
} 

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingSMin )
{
    const Rules rules = Rules(1, 1, 1, 1, 1, 1, 1, 1);
    BOOST_CHECK_EQUAL(1, rules.GetSMin());
} 

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingSMax )
{
    const Rules rules = Rules(1, 1, 1, 1, 1, 1, 1, 1);
    BOOST_CHECK_EQUAL(1, rules.GetSMax());
} 

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingBMin )
{
    const Rules rules = Rules(1, 1, 1, 1, 1, 1, 1, 1);
    BOOST_CHECK_EQUAL(1, rules.GetBMin());
} 

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingBMax )
{
    const Rules rules = Rules(1, 1, 1, 1, 1, 1, 1, 1);
    BOOST_CHECK_EQUAL(1, rules.GetBMax());
}

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingNeighbourhood)
{
    const Rules rules = Rules(0);
    BOOST_CHECK_EQUAL(0, rules.GetN());
}

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingThrow_WhenInvalidRange)
{
    Rules rules = Rules();
    int checkingValue1 = 0, checkingValue2 = 501;
    BOOST_CHECK_THROW(rules.SetRules(checkingValue1,1,true,1,1,1,1,1), std::invalid_argument);
    BOOST_CHECK_THROW(rules.SetRules(checkingValue2,1,true,1,1,1,1,1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingThrow_WhenInvalidNumberOfStates)
{
    Rules rules = Rules();
    int checkingValue1 = -1, checkingValue2 = 256;
    BOOST_CHECK_THROW(rules.SetRules(1,checkingValue1,true,1,1,1,1,1), std::invalid_argument);
    BOOST_CHECK_THROW(rules.SetRules(11,checkingValue2,true,1,1,1,1,1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingThrow_WhenInvalidSurvival)
{
    Rules rules = Rules();
    int checkingValue1 = -1, checkingValue2 = 5;
    BOOST_CHECK_THROW(rules.SetRules(1,1,true,checkingValue1,1,1,1,1), std::invalid_argument);
    BOOST_CHECK_THROW(rules.SetRules(1,1,true,checkingValue2,1,1,1,1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingThrow_WhenInvalidBirth)
{
    Rules rules = Rules();
    int checkingValue1 = 0, checkingValue2 = 5;
    BOOST_CHECK_THROW(rules.SetRules(1,1,true,1,1,checkingValue1,1,1), std::invalid_argument);
    BOOST_CHECK_THROW(rules.SetRules(1,1,true,1,1,checkingValue2,1,1), std::invalid_argument);
}





