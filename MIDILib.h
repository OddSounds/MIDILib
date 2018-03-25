#ifndef MIDILIB_H_
#define MIDILIB_H_

#include <stdint-gcc.h>

#ifndef MIDI_EVT_RX_BUFFER_SIZE
#define MIDI_EVT_RX_BUFFER_SIZE		32
#endif

#ifndef MIDI_EVT_TX_BUFFER_SIZE
#define MIDI_EVT_TX_BUFFER_SIZE		32
#endif

typedef enum
{
	STATE_CMD = 0,
	STATE_DATA_1,
	STATE_DATA_2,
	STATE_CATCHALL
}MIDI_STATE;

typedef struct 
{
	uint8_t cmd;
	uint8_t data[2];
}MIDI_EVT;

#define CMD_MSG		0x80
#define NOTE_ON		(CMD_MSG + 0x00)
#define NOTE_OFF	(CMD_MSG + 0x10)
#define POLY_PRES	(CMD_MSG + 0x20)
#define CTRL_CHNG	(CMD_MSG + 0x30)
#define PGM_CHNG	(CMD_MSG + 0x40)
#define CHNL_CHNG	(CMD_MSG + 0x50)
#define CHNL_PRES	(CMD_MSG + 0x60)
#define PTCH_BND	(CMD_MSG + 0x70)
#define SYS_MSG		(CMD_MSG + 0x80)

void MIDILib_Background(uint8_t c);

#endif /* MIDILIB_H_ */