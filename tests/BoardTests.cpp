#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BoardTests
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../src/Board.h"

BOOST_AUTO_TEST_CASE( GivenBoard_CheckingSize )
{
    const unsigned short size = 256;
    const Board board = Board(size, size);
    BOOST_CHECK_EQUAL(board.Height(), size);
    BOOST_CHECK_EQUAL(board.Width(), size);
}

BOOST_AUTO_TEST_CASE( GivenEmptyBoard_ChechPixelState )
{
    const unsigned short size = 256;
    const Board board = Board(size, size);
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4,size/4), 0);
}

BOOST_AUTO_TEST_CASE( GivenBoard_CheckingBoardOverflow )
{
    const unsigned short size = 256;
    const Board board = Board(size, size);
    BOOST_CHECK_THROW(board.GetPixelState(size+1,size+1), std::out_of_range);
}




