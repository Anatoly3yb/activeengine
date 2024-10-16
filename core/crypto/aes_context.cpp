#include "core/crypto/aes_context.h"

Error AESContext::start(Mode p_mode, PoolByteArray p_key, PoolByteArray p_iv) {
	ERR_FAIL_COND_V_MSG(mode != MODE_MAX, ERR_ALREADY_IN_USE, "AESContext already started. Call 'finish' before starting a new one.");
	ERR_FAIL_COND_V_MSG(p_mode < 0 || p_mode >= MODE_MAX, ERR_INVALID_PARAMETER, "Invalid mode requested.");
	// Key check.
	int key_bits = p_key.size() << 3;
	ERR_FAIL_COND_V_MSG(key_bits != 128 && key_bits != 256, ERR_INVALID_PARAMETER, "AES key must be either 16 or 32 bytes");
	// Initialization vector.
	if (p_mode == MODE_CBC_ENCRYPT || p_mode == MODE_CBC_DECRYPT) {
		ERR_FAIL_COND_V_MSG(p_iv.size() != 16, ERR_INVALID_PARAMETER, "The initialization vector (IV) must be exactly 16 bytes.");
		iv.resize(0);
		iv.append_array(p_iv);
	}
	// Encryption/decryption key.
	if (p_mode == MODE_CBC_ENCRYPT || p_mode == MODE_ECB_ENCRYPT) {
		ctx.set_encode_key(p_key.read().ptr(), key_bits);
	} else {
		ctx.set_decode_key(p_key.read().ptr(), key_bits);
	}
	mode = p_mode;
	return OK;
}

PoolByteArray AESContext::update(PoolByteArray p_src) {
	ERR_FAIL_COND_V_MSG(mode < 0 || mode >= MODE_MAX, PoolByteArray(), "AESContext not started. Call 'start' before calling 'update'.");
	int len = p_src.size();
	ERR_FAIL_COND_V_MSG(len % 16, PoolByteArray(), "The number of bytes to be encrypted must be multiple of 16. Add padding if needed");
	PoolByteArray out;
	out.resize(len);
	const uint8_t *src_ptr = p_src.read().ptr();
	uint8_t *out_ptr = out.write().ptr();
	switch (mode) {
		case MODE_ECB_ENCRYPT: {
			for (int i = 0; i < len; i += 16) {
				Error err = ctx.encrypt_ecb(src_ptr + i, out_ptr + i);
				ERR_FAIL_COND_V(err != OK, PoolByteArray());
			}
		} break;
		case MODE_ECB_DECRYPT: {
			for (int i = 0; i < len; i += 16) {
				Error err = ctx.decrypt_ecb(src_ptr + i, out_ptr + i);
				ERR_FAIL_COND_V(err != OK, PoolByteArray());
			}
		} break;
		case MODE_CBC_ENCRYPT: {
			Error err = ctx.encrypt_cbc(len, iv.write().ptr(), p_src.read().ptr(), out.write().ptr());
			ERR_FAIL_COND_V(err != OK, PoolByteArray());
		} break;
		case MODE_CBC_DECRYPT: {
			Error err = ctx.decrypt_cbc(len, iv.write().ptr(), p_src.read().ptr(), out.write().ptr());
			ERR_FAIL_COND_V(err != OK, PoolByteArray());
		} break;
		default:
			ERR_FAIL_V_MSG(PoolByteArray(), "Bug!");
	}
	return out;
}

PoolByteArray AESContext::get_iv_state() {
	ERR_FAIL_COND_V_MSG(mode != MODE_CBC_ENCRYPT && mode != MODE_CBC_DECRYPT, PoolByteArray(), "Calling 'get_iv_state' only makes sense when the context is started in CBC mode.");
	PoolByteArray out;
	out.append_array(iv);
	return out;
}

void AESContext::finish() {
	mode = MODE_MAX;
	iv.resize(0);
}

void AESContext::_bind_methods() {
	ClassDB::bind_method(D_METHOD("start", "mode", "key", "iv"), &AESContext::start, DEFVAL(PoolByteArray()));
	ClassDB::bind_method(D_METHOD("update", "src"), &AESContext::update);
	ClassDB::bind_method(D_METHOD("get_iv_state"), &AESContext::get_iv_state);
	ClassDB::bind_method(D_METHOD("finish"), &AESContext::finish);
	BIND_ENUM_CONSTANT(MODE_ECB_ENCRYPT);
	BIND_ENUM_CONSTANT(MODE_ECB_DECRYPT);
	BIND_ENUM_CONSTANT(MODE_CBC_ENCRYPT);
	BIND_ENUM_CONSTANT(MODE_CBC_DECRYPT);
	BIND_ENUM_CONSTANT(MODE_MAX);
}

AESContext::AESContext() {
	mode = MODE_MAX;
}
