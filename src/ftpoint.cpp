#include "ftpoint.h"

#include <boost/python.hpp>

#include <FTGL/ftgl.h>

class FTPointDefVisitor : public boost::python::def_visitor<FTPointDefVisitor>
{
    friend class def_visitor_access;
public:
    template <class T>
    void visit(T &class_) const
    {
        class_
            .def("__eq__", &__eq__)
            ;
    }

    static bool __eq__(FTPoint &self, const FTPoint &rhs)
    {
        return self == rhs;
    }

};

void FTPoint_init()
{
    boost::python::class_<FTPoint>("FTPoint")
        .def(boost::python::init<double, double, boost::python::optional<double>>())
        .def("Normalise", &FTPoint::Normalise)
        .def("__add__", &FTPoint::operator +)
        .def("__sub__", &FTPoint::operator -)
        .def("__mul__", static_cast<FTPoint(FTPoint::*)(double)const>(&FTPoint::operator *))
        .def("__pow__", &FTPoint::operator ^)
        .add_property("X",
            static_cast<FTGL_DOUBLE(FTPoint::*)()const>(&FTPoint::X),
            static_cast<void(FTPoint::*)(FTGL_DOUBLE)>(&FTPoint::X))
        .add_property("Y",
            static_cast<FTGL_DOUBLE(FTPoint::*)()const>(&FTPoint::Y),
            static_cast<void(FTPoint::*)(FTGL_DOUBLE)>(&FTPoint::Y))
        .add_property("Z",
            static_cast<FTGL_DOUBLE(FTPoint::*)()const>(&FTPoint::Z),
            static_cast<void(FTPoint::*)(FTGL_DOUBLE)>(&FTPoint::Z))
        ;
}
