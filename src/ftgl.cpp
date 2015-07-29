#include <boost/python.hpp>

#include <FTGL/ftgl.h>

#include "ftfont.h"
#include "ftglyph.h"
#include "ftlayout.h"

#include "ftbuffer.h"
#include "ftpoint.h"
#include "ftbbox.h"

BOOST_PYTHON_MODULE(__ftgl)
{
    FTFont_init();
    FTGlyph_init();
    FTLayout_init();

    FTBuffer_init();
    FTPoint_init();
    FTBBox_init();

    boost::python::enum_<FTGL::RenderMode>("RenderMode")
        .value("RENDER_FRONT", FTGL::RENDER_FRONT)
        .value("RENDER_BACK", FTGL::RENDER_BACK)
        .value("RENDER_SIDE", FTGL::RENDER_SIDE)
        .value("RENDER_ALL", FTGL::RENDER_ALL)
        .export_values()
        ;

    boost::python::enum_<FTGL::TextAlignment>("TextAlignment")
        .value("ALIGN_FRONT", FTGL::ALIGN_LEFT)
        .value("ALIGN_CENTER", FTGL::ALIGN_CENTER)
        .value("ALIGN_RIGHT", FTGL::ALIGN_RIGHT)
        .value("ALIGN_JUSTIFY", FTGL::ALIGN_JUSTIFY)
        .export_values()
        ;
}
