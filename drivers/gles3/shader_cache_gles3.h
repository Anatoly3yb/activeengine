#ifndef SHADER_CACHE_GLES3_H
#define SHADER_CACHE_GLES3_H

#include "core/local_vector.h"
#include "core/reference.h"

class DirAccess;
class String;

class ShaderCacheGLES3 {
	DirAccess *storage_da;
	String storage_path;
	uint64_t storage_size = 0;

	void _purge_excess();

public:
	static String hash_program(const char *const *p_platform_strings, const LocalVector<const char *> &p_vertex_strings, const LocalVector<const char *> &p_fragment_strings);

	bool retrieve(const String &p_program_hash, uint32_t *r_format, PoolByteArray *r_data);
	void store(const String &p_program_hash, uint32_t p_program_format, const PoolByteArray &p_program_data);
	void remove(const String &p_program_hash);

	ShaderCacheGLES3();
	~ShaderCacheGLES3();
};

#endif // SHADER_CACHE_GLES3_H
