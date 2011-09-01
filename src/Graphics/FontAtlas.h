#ifndef FONTATLAS_H_
#define FONTATLAS_H_
#define FONTATLAS_KERNING

#include "Platform.h"
#ifndef RAINBOW_IOS
#	include <cassert>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "Common/Data.h"
#include "Graphics/FontGlyph.h"
#include "OpenGL.h"

/// Uses FreeType to load OpenType and TrueType fonts.
///
/// Creates textures from font glyphs for symbols 32 through 126. Copies bitmap
/// data into a larger buffer which is then used as texture.
///
/// Features:
/// - Anti-aliasing
/// - Kerning
///
/// FIXME: Optimise texture size by sorting glyphs.
///
/// \see http://iphone-3d-programming.labs.oreilly.com/ch07.html
/// \see http://www.alfredrossi.com/?p=73
/// \see http://musingsofninjarat.wordpress.com/opengl-freetype-texture-fonts/
/// \see http://ftgl.sourceforge.net/docs/html/ftgl-tutorial.html
/// \see Beginning OpenGL Game Programming 2nd Edition (2009)
///
/// Copyright 2010-11 Bifrost Games. All rights reserved.
/// \author Tommy Nguyen
class FontAtlas
{
public:
	const float pt;

	FontAtlas(const float pt);

	void bind() const;

	const FontGlyph& get_glyph(const char c) const;

	/// Load font and create a texture atlas.
	void load(const Data &font);

	/// Print text at (x,y).
	void print(const char *text, const int x = 0, const int y = 0) const;

	/// Set font color.
	void set_color(const unsigned char r,
	               const unsigned char g,
	               const unsigned char b,
	               const unsigned char a = 0xff);

protected:
	static const unsigned char ascii_offset = 32;  ///< Start loading from character 32
	static const unsigned char chars = 95;         ///< Load characters through 126 from the ASCII table
	static const unsigned short int margin = 2;    ///< Drawn margin around font glyph
	static const unsigned short int padding = 3;   ///< Padding around font glyph texture

private:
	GLuint texture;            ///< GL texture id
	Colorb color;              ///< Font colour
	FontGlyph charset[chars];  ///< Character set

	/// Intentionally left undefined.
	FontAtlas(const FontAtlas &);

	/// Find the next power of 2 greater than given number.
	/// \return Power of 2, greater than 16 (minimum GL texture size)
	int next_pow2(const int a);

	/// Intentionally left undefined.
	FontAtlas& operator=(const FontAtlas &);
};

inline void FontAtlas::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

inline const FontGlyph& FontAtlas::get_glyph(const char c) const
{
	return this->charset[static_cast<unsigned int>(c - ascii_offset)];
}

inline int FontAtlas::next_pow2(const int a)
{
	int p = 16;
	for (; p < a; p <<= 1);
	return p;
}

#endif