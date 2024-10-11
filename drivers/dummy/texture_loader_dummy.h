#ifndef TEXTURE_LOADER_DUMMY_H
#define TEXTURE_LOADER_DUMMY_H

#include "core/io/resource_loader.h"
#include "scene/resources/texture.h"

class ResourceFormatDummyTexture : public ResourceFormatLoader {
public:
	virtual RES load(const String &p_path, const String &p_original_path = "", Error *r_error = NULL, bool p_no_subresource_cache = false);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;

	virtual ~ResourceFormatDummyTexture() {}
};

#endif // TEXTURE_LOADER_DUMMY_H
