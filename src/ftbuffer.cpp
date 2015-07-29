#include "ftbuffer.h"

#include <boost/python.hpp>

#include <FTGL/ftgl.h>

class FTBufferDefVisitor : public boost::python::def_visitor<FTBufferDefVisitor>
{
    friend class def_visitor_access;
public:
    template <class T>
    void visit(T class_) const
    {
        class_
            .add_property("Pixels", &get_pixels, &set_pixels)
            ;
    }

    static std::string get_pixels(FTBuffer &self)
    {
        int size = self.Width()*self.Height();
        std::string result(size, 0);
        memcpy(&result[0], self.Pixels(), size);
        return result;
    }

    static void set_pixels(FTBuffer &self, const std::string &data)
    {
        int size = std::min(self.Width()*self.Height(), static_cast<int>(data.size()));
        memcpy(self.Pixels(), &data[0], size);
    }

};

void FTBuffer_init()
{
    boost::python::class_<FTBuffer>("FTBuffer")
        .def(FTBufferDefVisitor())
        .add_property("Pos",
            static_cast<FTPoint(FTBuffer::*)()const>(&FTBuffer::Pos),
            static_cast<void(FTBuffer::*)(FTPoint)>(&FTBuffer::Pos))
        .def("Size", &FTBuffer::Size)
        .def("Width", &FTBuffer::Width)
        .def("Height", &FTBuffer::Height)
        ;
}
