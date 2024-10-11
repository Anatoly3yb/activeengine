#ifndef AES_CONTEXT_H
#define AES_CONTEXT_H

#include "core/crypto/crypto_core.h"
#include "core/reference.h"

class AESContext : public Reference {
	GDCLASS(AESContext, Reference);

public:
	enum Mode {
		MODE_ECB_ENCRYPT,
		MODE_ECB_DECRYPT,
		MODE_CBC_ENCRYPT,
		MODE_CBC_DECRYPT,
		MODE_MAX
	};

private:
	Mode mode;
	CryptoCore::AESContext ctx;
	PoolByteArray iv;

protected:
	static void _bind_methods();

public:
	Error start(Mode p_mode, PoolByteArray p_key, PoolByteArray p_iv = PoolByteArray());
	PoolByteArray update(PoolByteArray p_src);
	PoolByteArray get_iv_state();
	void finish();

	AESContext();
};

VARIANT_ENUM_CAST(AESContext::Mode);

#endif // AES_CONTEXT_H
