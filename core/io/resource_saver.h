#ifndef RESOURCE_SAVER_H
#define RESOURCE_SAVER_H

#include "core/resource.h"

class ResourceFormatSaver : public Reference {
	GDCLASS(ResourceFormatSaver, Reference);

protected:
	static void _bind_methods();

public:
	virtual Error save(const String &p_path, const RES &p_resource, uint32_t p_flags = 0);
	virtual bool recognize(const RES &p_resource) const;
	virtual void get_recognized_extensions(const RES &p_resource, List<String> *p_extensions) const;

	virtual ~ResourceFormatSaver() {}
};

typedef void (*ResourceSavedCallback)(Ref<Resource> p_resource, const String &p_path);

class ResourceSaver {
	enum {
		MAX_SAVERS = 64
	};

	static Ref<ResourceFormatSaver> saver[MAX_SAVERS];
	static int saver_count;
	static bool timestamp_on_save;
	static ResourceSavedCallback save_callback;

	static Ref<ResourceFormatSaver> _find_custom_resource_format_saver(String path);

public:
	enum SaverFlags {

		FLAG_RELATIVE_PATHS = 1,
		FLAG_BUNDLE_RESOURCES = 2,
		FLAG_CHANGE_PATH = 4,
		FLAG_OMIT_EDITOR_PROPERTIES = 8,
		FLAG_SAVE_BIG_ENDIAN = 16,
		FLAG_COMPRESS = 32,
		FLAG_REPLACE_SUBRESOURCE_PATHS = 64,
	};

	static Error save(const String &p_path, const RES &p_resource, uint32_t p_flags = 0);
	static void get_recognized_extensions(const RES &p_resource, List<String> *p_extensions);
	static void add_resource_format_saver(Ref<ResourceFormatSaver> p_format_saver, bool p_at_front = false);
	static void remove_resource_format_saver(Ref<ResourceFormatSaver> p_format_saver);

	static void set_timestamp_on_save(bool p_timestamp) { timestamp_on_save = p_timestamp; }
	static bool get_timestamp_on_save() { return timestamp_on_save; }

	static void set_save_callback(ResourceSavedCallback p_callback);

	static bool add_custom_resource_format_saver(String script_path);
	static void remove_custom_resource_format_saver(String script_path);
	static void add_custom_savers();
	static void remove_custom_savers();
};

#endif // RESOURCE_SAVER_H
