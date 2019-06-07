#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BoardTests
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../src/Board.h"

BOOST_AUTO_TEST_CASE( GivenBoard_CheckSize )
{
    const unsigned short size = 256;
    const Board board = Board(size, size);
    BOOST_CHECK_EQUAL(board.Height(), size);
    BOOST_CHECK_EQUAL(board.Width(), size);
}

BOOST_AUTO_TEST_CASE( GivenEmptyBoard_CheckPixelState )
{
    const unsigned short size = 256;
    const Board board = Board(size, size);
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4,size/4), 0);
}

BOOST_AUTO_TEST_CASE( GivenBoard_CheckBoardOverflow )
{
    const unsigned short size = 256;
    const Board board = Board(size, size);
    BOOST_CHECK_THROW(board.GetPixelState(size+1,size+1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( GivenBoard_CheckUpdateLifeBlock)
{
    const unsigned short size = 256;
    Board board = Board(size, size);
    board.SetConstBoard();
    board.SetRules(1,0,0,2,3,3,3,0);//set Rules to be Life
    BOOST_CHECK_EQUAL(board.GetPixelState(size/2,size/2), 1);//check if a pixel of the block stays over time
    board.Update();
    BOOST_CHECK_EQUAL(board.GetPixelState(size/2,size/2), 1);
    board.Update();
    BOOST_CHECK_EQUAL(board.GetPixelState(size/2,size/2), 1);
    board.Update();
    BOOST_CHECK_EQUAL(board.GetPixelState(size/2,size/2), 1);
}

BOOST_AUTO_TEST_CASE( GivenBoard_CheckUpdateLifeBlinker)
{
    const unsigned short size = 256;
    Board board = Board(size, size);
    board.SetConstBoard();
    board.SetRules(1,0,0,2,3,3,3,0);//set Rules to be Life
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4,size/4), 1);
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 + 1,size/4), 1);//when blinker is vertical, check up == 1
    board.Update();
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 + 1,size/4), 0);//when blinker is horizontal, check up == 0
    board.Update();
    board.Update();
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 + 1,size/4), 0);//when blinker is horizontal, check up == 0
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 - 1,size/4), 0);//when blinker is horizontal, check down == 0
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4,size/4 - 1), 1);//when blinker is horizontal, check left == 1
}

BOOST_AUTO_TEST_CASE( GivenBoard_CheckUpdateLifeBlinker)
{
    const unsigned short size = 256;
    Board board = Board(size, size);
    board.SetConstBoard();
    board.SetRules(1,0,0,2,3,3,3,0);//set Rules to be Gnarl
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4,size/4), 1);
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 + 1,size/4), 1);//when blinker is vertical, check up == 1
    board.Update();
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 + 1,size/4), 0);//when blinker is horizontal, check up == 0
    board.Update();
    board.Update();
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 + 1,size/4), 0);//when blinker is horizontal, check up == 0
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4 - 1,size/4), 0);//when blinker is horizontal, check down == 0
    BOOST_CHECK_EQUAL(board.GetPixelState(size/4,size/4 - 1), 1);//when blinker is horizontal, check left == 1
}