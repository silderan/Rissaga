#include "fonts.h"
#include "../Utils/logging.h"

using namespace Ris;

bool Font::load(const String fname, int size)
{
	m_font = TTF_OpenFont(fname.c_str(), size);
	return isValid();
}

String Fonts::createFontID(const String &fname, int size)
{
	return fname + " [" + String(size) + "]";
}
FontShared Fonts::getFont(String fname, int size)
{
	String fontID = createFontID(fname, size);
	FontShared f = operator[](fontID);
	if (f->isValid() || f->load(fname, size))
		return f;
	// Error, cannot be loaded :/
	g_log.logErr("Cannot load font file " + fname);
	erase(fontID);
	return emptyFont;
}