#ifndef RESOURCE_IMPORTER_TEXTURE_H
#define RESOURCE_IMPORTER_TEXTURE_H

#include "core/image.h"
#include "core/io/resource_importer.h"

class StreamTexture;

class ResourceImporterTexture : public ResourceImporter {
	GDCLASS(ResourceImporterTexture, ResourceImporter);

protected:
	enum {
		MAKE_3D_FLAG = 1,
		MAKE_SRGB_FLAG = 2,
		MAKE_NORMAL_FLAG = 4
	};

	Mutex mutex;
	Map<StringName, int> make_flags;

	static void _texture_reimport_srgb(const Ref<StreamTexture> &p_tex);
	static void _texture_reimport_3d(const Ref<StreamTexture> &p_tex);
	static void _texture_reimport_normal(const Ref<StreamTexture> &p_tex);

	static ResourceImporterTexture *singleton;
	static const char *compression_formats[];

public:
	static ResourceImporterTexture *get_singleton() { return singleton; }
	virtual String get_importer_name() const;
	virtual String get_visible_name() const;
	virtual void get_recognized_extensions(List<String> *p_extensions) const;
	virtual String get_save_extension() const;
	virtual String get_resource_type() const;

	enum Preset {
		PRESET_DETECT,
		PRESET_2D,
		PRESET_2D_PIXEL,
		PRESET_3D,
	};

	enum CompressMode {
		COMPRESS_LOSSLESS,
		COMPRESS_LOSSY,
		COMPRESS_VIDEO_RAM,
		COMPRESS_UNCOMPRESSED
	};

	virtual int get_preset_count() const;
	virtual String get_preset_name(int p_idx) const;

	virtual void get_import_options(List<ImportOption> *r_options, int p_preset = 0) const;
	virtual bool get_option_visibility(const String &p_option, const Map<StringName, Variant> &p_options) const;

	void _save_stex(const Ref<Image> &p_image, const String &p_to_path, int p_compress_mode, float p_lossy_quality, Image::CompressMode p_vram_compression, bool p_mipmaps, int p_texture_flags, bool p_streamable, bool p_detect_3d, bool p_detect_srgb, bool p_force_rgbe, bool p_detect_normal, bool p_force_normal, bool p_force_po2_for_compressed);

	virtual Error import(const String &p_source_file, const String &p_save_path, const Map<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files = nullptr, Variant *r_metadata = nullptr);

	void update_imports();

	virtual bool are_import_settings_valid(const String &p_path) const;
	virtual String get_import_settings_string() const;

	ResourceImporterTexture();
};

#endif // RESOURCE_IMPORTER_TEXTURE_H
