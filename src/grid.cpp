#include <boost/python.hpp>
#include <string>
#include "grid.h"


BOOST_PYTHON_MODULE(grid) 
{
    using namespace boost::python;

    class_<Grid>("Grid", init<int, int>())
        .def("Height", &Grid::Height)
        .def("Width", &Grid::Width)
        .def("GetPixelState", &Grid::GetPixelState)
        .def("SetRandomGrid", &Grid::SetRandomGrid)
        //.def("Update", &Grid::Update)
        //.def("Initialize", &Grid::Initialize)
        ;
}