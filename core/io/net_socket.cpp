#include "net_socket.h"

NetSocket *(*NetSocket::_create)() = nullptr;

NetSocket *NetSocket::create() {
	if (_create) {
		return _create();
	}

	ERR_PRINT("Unable to create network socket, platform not supported");
	return nullptr;
}
