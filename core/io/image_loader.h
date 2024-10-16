#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "core/image.h"
#include "core/io/resource_loader.h"
#include "core/list.h"
#include "core/os/file_access.h"
#include "core/ustring.h"

class ImageLoader;

class ImageFormatLoader {
	friend class ImageLoader;
	friend class ResourceFormatLoaderImage;

protected:
	virtual Error load_image(Ref<Image> p_image, FileAccess *p_fileaccess, bool p_force_linear, float p_scale) = 0;
	virtual void get_recognized_extensions(List<String> *p_extensions) const = 0;
	bool recognize(const String &p_extension) const;

public:
	virtual ~ImageFormatLoader() {}
};

class ImageLoader {
	static Vector<ImageFormatLoader *> loader;
	friend class ResourceFormatLoaderImage;

protected:
public:
	static Error load_image(String p_file, Ref<Image> p_image, FileAccess *p_custom = nullptr, bool p_force_linear = false, float p_scale = 1.0);
	static void get_recognized_extensions(List<String> *p_extensions);
	static ImageFormatLoader *recognize(const String &p_extension);

	static void add_image_format_loader(ImageFormatLoader *p_loader);
	static void remove_image_format_loader(ImageFormatLoader *p_loader);

	static const Vector<ImageFormatLoader *> &get_image_format_loaders();

	static void cleanup();
};

class ResourceFormatLoaderImage : public ResourceFormatLoader {
public:
	virtual RES load(const String &p_path, const String &p_original_path = "", Error *r_error = nullptr, bool p_no_subresource_cache = false);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;
};

#endif // IMAGE_LOADER_H
