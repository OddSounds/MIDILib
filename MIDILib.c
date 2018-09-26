#include "MIDILib.h"

#include <stdlib.h>

uint8_t EnablePassthrough = 0;

uint16_t ChannelFilter = 0xFFFF;

void (*serial_midithrough_putc)(uint8_t c);
void (*serial_midiout_putc)(uint8_t c);

void (*l_HandleProgramChange)(uint8_t channel, uint8_t b1) = NULL;
void (*l_HandleChannelPressure)(uint8_t channel, uint8_t b1) = NULL;

void (*l_HandleNoteOn)(uint8_t channel, uint8_t b1, uint8_t b2) = NULL;
void (*l_HandleNoteOff)(uint8_t channel, uint8_t b1, uint8_t b2) = NULL;
void (*l_HandlePolyPressure)(uint8_t channel, uint8_t b1, uint8_t b2) = NULL;
void (*l_HandleControlChange)(uint8_t channel, uint8_t b1, uint8_t b2) = NULL;
void (*l_HandlePitchBend)(uint8_t channel, uint8_t b1, uint8_t b2) = NULL;

void MIDILib_Background(uint8_t c)
{
	static uint8_t l_CurrentCmd = 0x00;
	static MIDI_STATE l_CurrentState = STATE_CMD;
	static uint8_t l_DataByte1 = 0x00, l_DataByte2 = 0x00;
	static uint8_t l_CurrentChannel = 0x00;
	
	if(c & CMD_MSG)
		l_CurrentState = STATE_CMD;
	
	switch(l_CurrentState)
	{
		case STATE_CMD:
		l_CurrentCmd = c & CMD_MASK;
		l_CurrentChannel = c & CHNL_MASK;
		
		if(ChannelFilter & (uint16_t)(1 << l_CurrentChannel))
			l_CurrentState = STATE_DATA_1;		
		break;
		
		case STATE_DATA_1:
		l_DataByte1 = c;
		
		switch(l_CurrentCmd)
		{
			//1 data byte commands
			case PGM_CHNG:
			if(l_HandleProgramChange)
				l_HandleProgramChange(l_CurrentChannel, l_DataByte1);
				
			l_CurrentState = STATE_CATCHALL;
			break;
			
			case CHNL_PRES:
			if(l_HandleChannelPressure)
				l_HandleChannelPressure(l_CurrentChannel, l_DataByte1);
				
			l_CurrentState = STATE_CATCHALL;
			break;
			
			//2 data byte commands
			default:
			l_CurrentState = STATE_DATA_2;
			break;
		}
		break;
		
		case STATE_DATA_2:
		l_DataByte2 = c;
		
		switch(l_CurrentCmd)
		{
			case NOTE_ON:
			if(l_HandleNoteOn)
				l_HandleNoteOn(l_CurrentChannel, l_DataByte1, l_DataByte2);
			break;
			
			case NOTE_OFF:
			if(l_HandleNoteOff)
				l_HandleNoteOff(l_CurrentChannel, l_DataByte1, l_DataByte2);
			break;
			
			case POLY_PRES:
			if(l_HandlePolyPressure)
				l_HandlePolyPressure(l_CurrentChannel, l_DataByte1, l_DataByte2);
			break;
			
			case CTRL_CHNG:
			if(l_HandleControlChange)
				l_HandleControlChange(l_CurrentChannel, l_DataByte1, l_DataByte2);
			break;
			
			case PTCH_BND:
			if(l_HandlePitchBend)
				l_HandlePitchBend(l_CurrentChannel, l_DataByte1, l_DataByte2);
			break;
		}
		
		l_CurrentState = STATE_CATCHALL;
		break;
		
		case STATE_CATCHALL:
		break;
	}
	
	if(EnablePassthrough && serial_midithrough_putc)
		serial_midithrough_putc(c);
}

//RegisterProgramChangeCallback
//Arguments: callback(channel(uint8_t), program(uint8_t))
void MIDILib_RegisterProgramChangeCallback(void (*callback)(uint8_t, uint8_t))
{
	l_HandleProgramChange = callback;
}

//RegisterChannelPressureCallback
//Arguments: callback(channel(uint8_t), pressure(uint8_t))
void MIDILib_RegisterChannelPressureCallback(void (*callback)(uint8_t, uint8_t))
{
	l_HandleChannelPressure = callback;
}

//RegisterNoteOnCallback
//Arguments: callback(channel(uint8_t), note(uint8_t), velocity(uint8_t))
void MIDILib_RegisterNoteOnCallback(void (*callback)(uint8_t, uint8_t, uint8_t))
{
	l_HandleNoteOn = callback;
}

//RegisterNoteOffCallback
//Arguments: callback(channel(uint8_t), note(uint8_t), velocity(uint8_t))
void MIDILib_RegsiterNoteOffCallback(void (*callback)(uint8_t, uint8_t, uint8_t))
{
	l_HandleNoteOff = callback;
}

//RegisterPolyPressureCallback
//Arguments: callback(channel(uint8_t), note(uint8_t), pressure(uint8_t))
void MIDILib_RegisterPolyPressureCallback(void (*callback)(uint8_t, uint8_t, uint8_t))
{
	l_HandlePolyPressure = callback;
}

//RegisterControlChangeCallback
//Arguments: callback(channel(uint8_t), control(uint8_t), value(uint8_t))
void MIDILIB_RegisterControlChangeCallback(void (*callback)(uint8_t, uint8_t, uint8_t))
{
	l_HandleControlChange = callback;
}

//RegisterPitchBendCallback
//Arguments: callback(channel(uint8_t), lsb(uint8_t), msb(uint8_t))
void MIDILib_RegisterPitchBendCallback(void (*callback)(uint8_t, uint8_t, uint8_t))
{
	l_HandlePitchBend = callback;
}
