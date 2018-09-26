#ifndef MIDILIB_H_
#define MIDILIB_H_

#include <stdint-gcc.h>

typedef enum
{
	STATE_CMD = 0,
	STATE_DATA_1,
	STATE_DATA_2,
	STATE_CATCHALL
}MIDI_STATE;

#define CHNL_MASK	0x0F
#define CMD_MASK	0xF0

#define CMD_MSG		0x80
#define NOTE_ON		(CMD_MSG + 0x00)
#define NOTE_OFF	(CMD_MSG + 0x10)
#define POLY_PRES	(CMD_MSG + 0x20)
#define CTRL_CHNG	(CMD_MSG + 0x30)
#define PGM_CHNG	(CMD_MSG + 0x40)
#define CHNL_PRES	(CMD_MSG + 0x60)
#define PTCH_BND	(CMD_MSG + 0x70)

void MIDILib_Background(uint8_t c);

void MIDILib_RegisterProgramChangeCallback(void (*callback)(uint8_t, uint8_t));
void MIDILib_RegisterChannelPressureCallback(void (*callback)(uint8_t, uint8_t));
void MIDILib_RegisterNoteOnCallback(void (*callback)(uint8_t, uint8_t, uint8_t));
void MIDILib_RegsiterNoteOffCallback(void (*callback)(uint8_t, uint8_t, uint8_t));
void MIDILib_RegisterPolyPressureCallback(void (*callback)(uint8_t, uint8_t, uint8_t));
void MIDILIB_RegisterControlChangeCallback(void (*callback)(uint8_t, uint8_t, uint8_t));
void MIDILib_RegisterPitchBendCallback(void (*callback)(uint8_t, uint8_t, uint8_t));

void MIDILib_SendProgramChange(uint8_t channel, uint8_t program);
void MIDILib_SendChannelPressure(uint8_t channel, uint8_t pressure);
void MIDILib_SendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
void MIDILib_SendNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
void MIDILib_SendPolyPressure(uint8_t channel, uint8_t note, uint8_t pressure);
void MIDILib_SendControlChange(uint8_t channel, uint8_t control, uint8_t value);
void MIDILib_SendPitchBend(uint8_t channel, uint16_t value);

void MIDILib_EnableMIDIPassthrough();
void MIDILib_DisableMIDIPassthrough();

void MIDILib_AllowChannel(uint8_t channel);
void MIDILib_BlockChannel(uint8_t channel);
void MIDILib_SetChannelFilter(uint16_t filter);

#endif /* MIDILIB_H_ */