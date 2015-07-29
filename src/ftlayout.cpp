#include "ftlayout.h"

#include <boost/python.hpp>

#include <FTGL/ftgl.h>

class FTLayoutWrapper : public FTLayout, public boost::python::wrapper<FTLayout>
{
public:
    FTBBox BBox(const std::string &string, FTPoint position = FTPoint())
    {
        return this->get_override("BBbox")(string, position);
    }

    FTBBox BBox(const std::wstring &string, FTPoint position = FTPoint())
    {
        return this->get_override("BBbox")(string, position);
    }

    void Render(const std::string &string, FTPoint position = FTPoint(), int renderMode = FTGL::RENDER_ALL)
    {
        this->get_override("Render")(string, position, renderMode);
    }

    void Render(const std::wstring &string, FTPoint position = FTPoint(), int renderMode = FTGL::RENDER_ALL)
    {
        this->get_override("Render")(string, position, renderMode);
    }

};

// FTLayoutWrapper overloads
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FTLayoutWrapper_BBox_1_2_overloads, BBox, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FTLayoutWrapper_Render_1_3_overloads, Render, 1, 3)

class FTSimpleLayoutDefVisitor : public boost::python::def_visitor<FTSimpleLayoutDefVisitor>
{
    friend class def_visitor_access;
public:
    static FTBBox BBox(FTSimpleLayout &self, const std::string &string, FTPoint position = FTPoint())
    {
        return self.BBox(string.c_str(), string.size(), position);
    }

    static FTBBox BBox(FTSimpleLayout &self, const std::wstring &string, FTPoint position = FTPoint())
    {
        return self.BBox(string.c_str(), string.size(), position);
    }

    static void Render(FTSimpleLayout &self, const std::string &string, FTPoint position = FTPoint(), int renderMode = FTGL::RENDER_ALL)
    {
        self.Render(string.c_str(), string.size(), position, renderMode);
    }

    static void Render(FTSimpleLayout &self, const std::wstring &string, FTPoint position = FTPoint(), int renderMode = FTGL::RENDER_ALL)
    {
        self.Render(string.c_str(), string.size(), position, renderMode);
    }

    static void SetFont(FTSimpleLayout &self, const FTFont &font)
    {
        self.SetFont(const_cast<FTFont *>(&font));
    }

    // FTSimpleLayoutDefVisitor overloads
    BOOST_PYTHON_FUNCTION_OVERLOADS(FTSimpleLayoutWrapper_BBox_2_3_overloads, BBox, 2, 3)
    BOOST_PYTHON_FUNCTION_OVERLOADS(FTSimpleLayoutWrapper_Render_2_4_overloads, Render, 2, 4)

    template <class T>
    void visit(T &class_) const
    {
        class_
            .def("BBox", static_cast<FTBBox(*)(FTSimpleLayout &, const std::string &, FTPoint)>(&BBox), FTSimpleLayoutWrapper_BBox_2_3_overloads())
            .def("BBox", static_cast<FTBBox(*)(FTSimpleLayout &, const std::wstring &, FTPoint)>(&BBox), FTSimpleLayoutWrapper_BBox_2_3_overloads())
            .def("Render", static_cast<void(*)(FTSimpleLayout &, const std::string &, FTPoint, int)>(&Render), FTSimpleLayoutWrapper_Render_2_4_overloads())
            .def("Render", static_cast<void(*)(FTSimpleLayout &, const std::wstring &, FTPoint, int)>(&Render), FTSimpleLayoutWrapper_Render_2_4_overloads())
            .def("SetFont", &SetFont)
            ;
    }

};
void FTLayout_init()
{
    boost::python::class_<FTLayoutWrapper, boost::noncopyable>("FTLayout", boost::python::no_init)
        .def("BBox", static_cast<FTBBox(FTLayoutWrapper::*)(const std::string &, FTPoint)>(&FTLayoutWrapper::BBox), FTLayoutWrapper_BBox_1_2_overloads())
        .def("BBox", static_cast<FTBBox(FTLayoutWrapper::*)(const std::wstring &, FTPoint)>(&FTLayoutWrapper::BBox), FTLayoutWrapper_BBox_1_2_overloads())
        .def("Render", static_cast<void(FTLayoutWrapper::*)(const std::string &, FTPoint, int)>(&FTLayoutWrapper::Render), FTLayoutWrapper_Render_1_3_overloads())
        .def("Render", static_cast<void(FTLayoutWrapper::*)(const std::wstring &, FTPoint, int)>(&FTLayoutWrapper::Render), FTLayoutWrapper_Render_1_3_overloads())
        .def("Error", &FTFont::Error)
        ;

    // FTSimpleLayout.h
    boost::python::class_<FTSimpleLayout, boost::python::bases<FTLayout>>("FTSimpleLayout")
        .def(FTSimpleLayoutDefVisitor())
        .def("GetFont", &FTSimpleLayout::GetFont, boost::python::return_value_policy<boost::python::reference_existing_object>())
        .def("SetLineLength", &FTSimpleLayout::SetLineLength)
        .def("GetLineLength", &FTSimpleLayout::GetLineLength)
        .def("SetAlignment", &FTSimpleLayout::SetAlignment)
        .def("GetAlignment", &FTSimpleLayout::GetAlignment)
        .def("SetLineSpacing", &FTSimpleLayout::SetLineSpacing)
        .def("GetLineSpacing", &FTSimpleLayout::GetLineSpacing)
        ;
}
