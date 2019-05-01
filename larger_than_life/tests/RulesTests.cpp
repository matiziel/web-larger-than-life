#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BoardTests
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../src/Rules.h"


BOOST_AUTO_TEST_CASE( GivenRulesObject_CheckingNeighbourhood )
{
    const Rules rules = Rules(0);
    BOOST_CHECK_EQUAL(0, rules.GetN());
} 
