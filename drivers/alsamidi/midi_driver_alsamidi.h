#ifndef MIDI_DRIVER_ALSAMIDI_H
#define MIDI_DRIVER_ALSAMIDI_H

#ifdef ALSAMIDI_ENABLED

#include "core/os/midi_driver.h"
#include "core/os/mutex.h"
#include "core/os/thread.h"
#include "core/safe_refcount.h"
#include "core/vector.h"

#include "../alsa/asound-so_wrap.h"
#include <stdio.h>

class MIDIDriverALSAMidi : public MIDIDriver {
	Thread thread;
	Mutex mutex;

	class InputConnection {
	public:
		InputConnection() = default;
		InputConnection(snd_rawmidi_t *midi_in) :
				rawmidi_ptr{ midi_in } {}

		// Read in and parse available data, forwarding any complete messages through the driver.
		int read_in(MIDIDriverALSAMidi &driver, uint64_t timestamp);

		snd_rawmidi_t *rawmidi_ptr = nullptr;

	private:
		static const size_t MSG_BUFFER_SIZE = 3;
		uint8_t buffer[MSG_BUFFER_SIZE] = { 0 };
		size_t expected_data = 0;
		size_t received_data = 0;
		bool skipping_sys_ex = false;
		void parse_byte(uint8_t byte, MIDIDriverALSAMidi &driver, uint64_t timestamp);
	};

	Vector<InputConnection> connected_inputs;

	SafeFlag exit_thread;

	static void thread_func(void *p_udata);

	enum class MessageCategory {
		Data,
		Voice,
		SysExBegin,
		SystemCommon, // excluding System Exclusive Begin/End
		SysExEnd,
		RealTime,
	};

	// If the passed byte is a status byte, return the associated message category,
	// else return MessageCategory::Data.
	static MessageCategory msg_category(uint8_t msg_part);

	// Return the number of data bytes expected for the provided status byte.
	static size_t msg_expected_data(uint8_t status_byte);

	void lock() const;
	void unlock() const;

public:
	virtual Error open();
	virtual void close();

	virtual PoolStringArray get_connected_inputs();

	MIDIDriverALSAMidi();
	virtual ~MIDIDriverALSAMidi();
};

#endif // ALSAMIDI_ENABLED

#endif // MIDI_DRIVER_ALSAMIDI_H
