#include "ftbbox.h"

#include <boost/python.hpp>

#include <FTGL/ftgl.h>

class FTBBoxDefVisitor : public boost::python::def_visitor<FTBBoxDefVisitor>
{
    friend class def_visitor_access;
public:
    template <class T>
    void visit(T &class_) const
    {
        class_
            .def("__add__", &__add__)
            .def("__or__", &__or__)
            ;
    }

    static FTBBox __add__(FTBBox &self, const FTPoint &rhs)
    {
        FTBBox result = self;
        result += rhs;
        return result;
    }

    static FTBBox __or__(FTBBox &self, const FTBBox &rhs)
    {
        FTBBox result = self;
        result |= rhs;
        return result;
    }

};

void FTBBox_init()
{
    boost::python::class_<FTBBox>("FTBBox")
        .def(FTBBoxDefVisitor())
        .def(boost::python::init<float, float, float, float, float, float>())
        .def(boost::python::init<FTPoint, FTPoint>())
        .def("Invalidate", &FTBBox::Invalidate)
        .def("IsValid", &FTBBox::IsValid)
        .def("SetDepth", &FTBBox::SetDepth)
        .def("Upper", &FTBBox::Upper)
        .def("Lower", &FTBBox::Lower)
        ;
}
