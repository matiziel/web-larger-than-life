#include <boost/python.hpp>
#include <string>
#include "Board.h"


BOOST_PYTHON_MODULE(board) 
{
    using namespace boost::python;

    class_<Board>("Board", init<int, int>())
        .def("Height", &Board::Height)
        .def("Width", &Board::Width)
        .def("GetPixelState", &Board::GetPixelState)
        .def("SetRandomBoard", &Board::SetRandomBoard)
        .def("Update", &Board::Update)
        ;
}