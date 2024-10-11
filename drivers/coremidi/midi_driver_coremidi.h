#ifndef MIDI_DRIVER_COREMIDI_H
#define MIDI_DRIVER_COREMIDI_H

#ifdef COREMIDI_ENABLED

#include "core/os/midi_driver.h"
#include "core/vector.h"

#include <CoreMIDI/CoreMIDI.h>
#include <stdio.h>

class MIDIDriverCoreMidi : public MIDIDriver {
	MIDIClientRef client;
	MIDIPortRef port_in;

	Vector<MIDIEndpointRef> connected_sources;

	static void read(const MIDIPacketList *packet_list, void *read_proc_ref_con, void *src_conn_ref_con);

public:
	virtual Error open();
	virtual void close();

	PoolStringArray get_connected_inputs();

	MIDIDriverCoreMidi();
	virtual ~MIDIDriverCoreMidi();
};

#endif // COREMIDI_ENABLED

#endif // MIDI_DRIVER_COREMIDI_H
