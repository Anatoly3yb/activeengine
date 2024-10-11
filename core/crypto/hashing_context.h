#ifndef HASHING_CONTEXT_H
#define HASHING_CONTEXT_H

#include "core/reference.h"

class HashingContext : public Reference {
	GDCLASS(HashingContext, Reference);

public:
	enum HashType {
		HASH_MD5,
		HASH_SHA1,
		HASH_SHA256
	};

private:
	void *ctx;
	HashType type;

protected:
	static void _bind_methods();
	void _create_ctx(HashType p_type);
	void _delete_ctx();

public:
	Error start(HashType p_type);
	Error update(PoolByteArray p_chunk);
	PoolByteArray finish();

	HashingContext();
	~HashingContext();
};

VARIANT_ENUM_CAST(HashingContext::HashType);

#endif // HASHING_CONTEXT_H
