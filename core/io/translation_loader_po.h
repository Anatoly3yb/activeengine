#ifndef TRANSLATION_LOADER_PO_H
#define TRANSLATION_LOADER_PO_H

#include "core/io/resource_loader.h"
#include "core/os/file_access.h"
#include "core/translation.h"

class TranslationLoaderPO : public ResourceFormatLoader {
public:
	static RES load_translation(FileAccess *f, bool p_use_context, Error *r_error = nullptr);
	virtual RES load(const String &p_path, const String &p_original_path = "", Error *r_error = nullptr, bool p_no_subresource_cache = false);
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual bool handles_type(const String &p_type) const;
	virtual String get_resource_type(const String &p_path) const;

	TranslationLoaderPO();
};

#endif // TRANSLATION_LOADER_PO_H
