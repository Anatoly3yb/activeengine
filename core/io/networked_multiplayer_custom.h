#ifndef NETWORKED_MULTIPLAYER_CUSTOM_H
#define NETWORKED_MULTIPLAYER_CUSTOM_H

#include "core/io/networked_multiplayer_peer.h"

class NetworkedMultiplayerCustom : public NetworkedMultiplayerPeer {
	GDCLASS(NetworkedMultiplayerCustom, NetworkedMultiplayerPeer);

protected:
	int self_id;
	TransferMode transfer_mode;
	ConnectionStatus connection_status;
	bool refusing_new_connections;
	int target_id;
	int max_packet_size;

	struct Packet {
		PoolVector<uint8_t> data;
		int from;
	};

	List<Packet> incoming_packets;

	Packet current_packet;

	static void _bind_methods();

public:
	NetworkedMultiplayerCustom();
	~NetworkedMultiplayerCustom();

	// PacketPeer.
	Error get_packet(const uint8_t **r_buffer, int &r_buffer_size);
	Error put_packet(const uint8_t *p_buffer, int p_buffer_size);
	int get_available_packet_count() const;
	int get_max_packet_size() const;

	// NetworkedMultiplayerPeer.
	void set_transfer_mode(TransferMode p_mode);
	TransferMode get_transfer_mode() const;
	void set_target_peer(int p_peer);
	int get_packet_peer() const;
	bool is_server() const;
	void poll();
	int get_unique_id() const;
	void set_refuse_new_connections(bool p_enable);
	bool is_refusing_new_connections() const;
	ConnectionStatus get_connection_status() const;

	// Custom methods.
	void initialize(int p_self_id);
	void set_max_packet_size(int p_max_packet_size);
	void set_connection_status(ConnectionStatus p_connection_status);
	void deliver_packet(const PoolByteArray &p_data, int p_from_peer_id);
};

#endif // NETWORKED_MULTIPLAYER_CUSTOM_H
