#include "ftglyph.h"

#include <boost/python.hpp>

#include <FTGL/ftgl.h>

void FTGlyph_init()
{
    boost::python::class_<FTGlyph, boost::noncopyable>("FTGlyph", boost::python::no_init)
        .def("Render", boost::python::pure_virtual(&FTGlyph::Render), boost::python::return_value_policy<boost::python::copy_const_reference>())
        .def("Advance", &FTGlyph::Advance)
        .def("BBox", &FTGlyph::BBox, boost::python::return_value_policy<boost::python::copy_const_reference>())
        .def("Error", &FTGlyph::Error)
        ;

    // FTBitmapGlyph.h
    boost::python::class_<FTBitmapGlyph, boost::python::bases<FTGlyph>>("FTBitmapGlyph", boost::python::init<FT_GlyphSlot>());

    // FTBufferGlyph.h
    boost::python::class_<FTBufferGlyph, boost::python::bases<FTGlyph>>("FTBufferGlyph", boost::python::init<FT_GlyphSlot, FTBuffer *>());

    // FTExtrdGlyph.h
    boost::python::class_<FTExtrudeGlyph, boost::python::bases<FTGlyph>>("FTExtrudeGlyph", boost::python::init<FT_GlyphSlot, float, float, float, bool>());

    // FTOutlineGlyph.h
    boost::python::class_<FTOutlineGlyph, boost::python::bases<FTGlyph>>("FTOutlineGlyph", boost::python::init<FT_GlyphSlot, float, bool>());

    // FTPixmapGlyph.h
    boost::python::class_<FTPixmapGlyph, boost::python::bases<FTGlyph>>("FTPixmapGlyph", boost::python::init<FT_GlyphSlot>());

    // FTPolylyph.h
    boost::python::class_<FTPolygonGlyph, boost::python::bases<FTGlyph>>("FTPolygonGlyph", boost::python::init<FT_GlyphSlot, float, bool>());

    // FTTextureGlyph.h
    boost::python::class_<FTTextureGlyph, boost::python::bases<FTGlyph>>("FTTextureGlyph", boost::python::init<FT_GlyphSlot, int, int, int, int, int>());
}
