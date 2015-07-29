#include "ftfont.h"

#include <boost/python.hpp>

#include <FTGL/ftgl.h>

class FTFontDefVisitor : public boost::python::def_visitor<FTFontDefVisitor>
{
    friend class def_visitor_access;
public:
    static FTBBox BBox(FTFont &self, const std::string &string, FTPoint position = FTPoint(), FTPoint spacing = FTPoint())
    {
        return self.BBox(string.c_str(), string.size(), position, spacing);
    }

    static FTBBox BBox(FTFont &self, const std::wstring &string, FTPoint position = FTPoint(), FTPoint spacing = FTPoint())
    {
        return self.BBox(string.c_str(), string.size(), position, spacing);
    }

    static float Advance(FTFont &self, const std::string &string, FTPoint spacing = FTPoint())
    {
        return self.Advance(string.c_str(), string.size(), spacing);
    }

    static float Advance(FTFont &self, const std::wstring &string, FTPoint spacing = FTPoint())
    {
        return self.Advance(string.c_str(), string.size(), spacing);
    }

    static FTPoint Render(FTFont &self, const std::string &string, FTPoint position = FTPoint(), FTPoint spacing = FTPoint(), int renderMode = FTGL::RENDER_ALL)
    {
        return self.Render(string.c_str(), string.size(), position, spacing, renderMode);
    }

    static FTPoint Render(FTFont &self, const std::wstring &string, FTPoint position = FTPoint(), FTPoint spacing = FTPoint(), int renderMode = FTGL::RENDER_ALL)
    {
        return self.Render(string.c_str(), string.size(), position, spacing, renderMode);
    }

    // FTFontDefVisitor overloads
    BOOST_PYTHON_FUNCTION_OVERLOADS(FTFontDefVisitor_BBox_2_4_overloads, BBox, 2, 4)
    BOOST_PYTHON_FUNCTION_OVERLOADS(FTFontDefVisitor_Advance_2_3_overloads, Advance, 2, 3)
    BOOST_PYTHON_FUNCTION_OVERLOADS(FTFontDefVisitor_Render_2_5_overloads, Render, 2, 5)

    template <class T>
    void visit(T &class_) const
    {
        class_
            .def("BBox", static_cast<FTBBox(*)(FTFont &, const std::string &, FTPoint, FTPoint)>(&BBox), FTFontDefVisitor_BBox_2_4_overloads())
            .def("BBox", static_cast<FTBBox(*)(FTFont &, const std::wstring &, FTPoint, FTPoint)>(&BBox), FTFontDefVisitor_BBox_2_4_overloads())
            .def("Advance", static_cast<float(*)(FTFont &, const std::string &, FTPoint)>(&Advance), FTFontDefVisitor_Advance_2_3_overloads())
            .def("Advance", static_cast<float(*)(FTFont &, const std::wstring &, FTPoint)>(&Advance), FTFontDefVisitor_Advance_2_3_overloads())
            .def("Render", static_cast<FTPoint(*)(FTFont &, const std::string &, FTPoint, FTPoint, int)>(&Render), FTFontDefVisitor_Render_2_5_overloads())
            .def("Render", static_cast<FTPoint(*)(FTFont &, const std::wstring &, FTPoint, FTPoint, int)>(&Render), FTFontDefVisitor_Render_2_5_overloads())
            ;
    }

};

class FTFontWrapper : public FTFont, public boost::python::wrapper<FTFont>
{
protected:
    FTGlyph *MakeGlyph(FT_GlyphSlot slot)
    {
        return this->get_override("MakeGlyph")(slot);
    }
};

template <class T>
void init(const char *name)
{
    boost::python::class_<T, boost::python::bases<FTFont>>(name, boost::python::init<const char *>())
        .def(boost::python::init<const unsigned char *, size_t>())
        ;
}

// FTFont overloads
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FTFont_FaceSize_1_2_overloads, FaceSize, 1, 2)

void FTFont_init()
{
    boost::python::class_<FTFontWrapper, boost::noncopyable>("FTFont", boost::python::no_init)
        .def(FTFontDefVisitor())
        .def("Attach", static_cast<bool(FTFont::*)(const char *)>(&FTFont::Attach))
        .def("Attach", static_cast<bool(FTFont::*)(const unsigned char *, size_t)>(&FTFont::Attach))
        .def("GlyphLoadFlags", &FTFont::GlyphLoadFlags)
        .def("CharMap", &FTFont::CharMap)
        .def("CharMapCount", &FTFont::CharMapCount)
        .def("CharMapList", &FTFont::CharMapList, boost::python::return_value_policy<boost::python::return_opaque_pointer>())
        .def("FaceSize", static_cast<bool(FTFont::*)(const unsigned int, const unsigned int)>(&FTFont::FaceSize), FTFont_FaceSize_1_2_overloads())
        .def("FaceSize", static_cast<unsigned int(FTFont::*)()const>(&FTFont::FaceSize))
        .def("Depth", &FTFont::Depth)
        .def("Outset", static_cast<void(FTFont::*)(float)>(&FTFont::Outset))
        .def("Outset", static_cast<void(FTFont::*)(float, float)>(&FTFont::Outset))
        .def("UseDisplayList", &FTFont::UseDisplayList)
        .def("Ascender", &FTFont::Ascender)
        .def("Descender", &FTFont::Descender)
        .def("LineHeight", &FTFont::LineHeight)
        .def("Error", &FTFont::Error)
        ;

    init<FTBufferFont>("FTBufferFont");   // FTBufferFont.h
    init<FTBitmapFont>("FTBitmapFont");   // FTGLBitmapFont.h
    init<FTExtrudeFont>("FTExtrudeFont"); // FTGLExtrdFont.h
    init<FTOutlineFont>("FTOutlineFont"); // FTGLOutlineFont.h
    init<FTPixmapFont>("FTPixmapFont");   // FTGLPixmapFont.h
    init<FTPolygonFont>("FTPolygonFont"); // FTGLPolygonFont.h
    init<FTTextureFont>("FTTextureFont"); // FTGLTextureFont.h
}
