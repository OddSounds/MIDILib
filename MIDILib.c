//MIDILib.c
#include "MIDILib.h"

uint8_t l_CurrentCmd = 0x00;
MIDI_STATE l_CurrentState = STATE_CMD;

void (*serial_putc)(uint8_t c);

static void l_PushQ()
{
	
}

static void l_PopQ()
{

}

void MIDILib_Background(uint8_t c)
{
	if(c & CMD_MSG)
	{
		l_CurrentCmd = c;
	}
	
	switch(l_CurrentState)
	{
		case STATE_CMD:
		break;
		
		case STATE_DATA_1:
		break;
		
		case STATE_DATA_2:
		break;
		
		case STATE_CATCHALL:
		break;
	}
	
#ifdef MIDI_PASSTHROUGH
	serial_putc(c);
#endif
}
