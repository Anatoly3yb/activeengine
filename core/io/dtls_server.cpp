#include "dtls_server.h"
#include "core/os/file_access.h"
#include "core/project_settings.h"

DTLSServer *(*DTLSServer::_create)() = nullptr;
bool DTLSServer::available = false;

DTLSServer *DTLSServer::create() {
	if (_create) {
		return _create();
	}
	return nullptr;
}

bool DTLSServer::is_available() {
	return available;
}

void DTLSServer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setup", "key", "certificate", "chain"), &DTLSServer::setup, DEFVAL(Ref<X509Certificate>()));
	ClassDB::bind_method(D_METHOD("take_connection", "udp_peer"), &DTLSServer::take_connection);
}

DTLSServer::DTLSServer() {
}
