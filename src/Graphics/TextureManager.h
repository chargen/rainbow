#ifndef GRAPHICS_TEXTUREMANAGER_H_
#define GRAPHICS_TEXTUREMANAGER_H_

#include "Common/Vector.h"

namespace Renderer
{
	bool init();
	void release();
}

/// Manages texture resources.
///
/// Generates and reuses texture ids whenever possible. This should eliminate
/// problems caused by drivers that return deleted ids before they are actually
/// deleted. This causes black textures.
///
/// Deleted textures are shelved until they are needed again. In order to
/// minimize memory use, they are resized to a minimal texture dimension. Of
/// course, it is also possible to purge this storage by issuing \c purge(). To
/// avoid problems, this should only occur when you're done loading textures
/// for a while.
///
/// Copyright 2012-13 Bifrost Entertainment. All rights reserved.
/// \author Tommy Nguyen
class TextureManager : private NonCopyable<TextureManager>
{
	friend bool Renderer::init();
	friend void Renderer::release();

public:
	static TextureManager* Instance;

	/// Makes texture active on current rendering target.
	/// \param id  Texture id to bind. If omitted, bind the default texture.
	void bind(const unsigned int id = 0);

	/// Creates a texture.
	/// \param internal_format  Preferred renderer's internal format.
	/// \param width            Width of the texture.
	/// \param height           Height of the texture.
	/// \param format           Format of the bitmap data.
	/// \param data             Bitmap data.
	/// \return Texture id.
	unsigned int create(const unsigned int internal_format,
	                    const unsigned int width,
	                    const unsigned int height,
	                    const unsigned int format,
	                    const void *data);

	/// Creates texture from a compressed format.
	/// \param format  Compression format.
	/// \param width   Width of the texture.
	/// \param height  Height of the texture.
	/// \param size    Data size.
	/// \param data    Compressed bitmap data.
	/// \return Texture id.
	unsigned int create_compressed(const unsigned int format,
	                               const unsigned int width,
	                               const unsigned int height,
	                               const size_t size,
	                               const void *data);

	/// Returns total video memory used (and unused) by textures.
	void get_usage(double &used, double &unused, double &peak) const;

	/// Purges unused texture memory.
	inline void purge();

	/// Deletes texture. In reality, the texture is put in a recycle bin and may
	/// be reused unless purged.
	/// \param id  Texture to delete.
	void remove(const unsigned int id);

	void set_filter(const int filter);

private:
	/// Structure storing a texture's id and area.
	struct TextureId
	{
		unsigned int id;  ///< Texture id.
		unsigned int sz;  ///< Texture area.

		inline bool operator==(const TextureId &tex);
		inline bool operator>(const TextureId &tex);
	};

	unsigned int active;
	int mag_filter;
	int min_filter;
	double mem_peak;
	double mem_used;
	Vector<TextureId> recycled;  ///< Stores reusable texture ids.
	Vector<TextureId> textures;  ///< Stores texture ids currently in use.

	TextureManager();
	~TextureManager();

	/// Prints total video memory used by textures.
	void print_usage() const;

	/// Clears and deletes textures.
	void purge(Vector<TextureId> &textures);
};

void TextureManager::purge()
{
	this->purge(this->recycled);
}

bool TextureManager::TextureId::operator==(const TextureId &tex)
{
	return tex.id == this->id;
}

bool TextureManager::TextureId::operator>(const TextureId &tex)
{
	return this->sz > tex.sz;
}

#endif
