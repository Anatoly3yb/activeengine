#ifndef MIDI_DRIVER_WINMIDI_H
#define MIDI_DRIVER_WINMIDI_H

#ifdef WINMIDI_ENABLED

#include "core/os/midi_driver.h"
#include "core/vector.h"

#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <mmsystem.h>

class MIDIDriverWinMidi : public MIDIDriver {
	Vector<HMIDIIN> connected_sources;

	static void CALLBACK read(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

public:
	virtual Error open();
	virtual void close();

	virtual PoolStringArray get_connected_inputs();

	MIDIDriverWinMidi();
	virtual ~MIDIDriverWinMidi();
};

#endif // WINMIDI_ENABLED

#endif // MIDI_DRIVER_WINMIDI_H
