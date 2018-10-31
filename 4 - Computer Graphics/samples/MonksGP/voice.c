#include "voice.h"

void InitFMOD(){
	FSOUND_SetOutput ( FSOUND_OUTPUT_DSOUND );      // DirectSound
	FSOUND_SetDriver ( 0 );                         // Sound Driver (default 0)
	FSOUND_SetMixer ( FSOUND_MIXER_AUTODETECT );    // Mixer
	FSOUND_Init ( 44100, 1, 0 );                    // 44.1 kHz and 32 channels
}

void ShutdownFMOD(){
	FSOUND_Close ( );
}

void playSound (char a, char b, unsigned char c) {
    //01 a 50 = numeros
    //99 = Bingo! We Have a Winner!
    //98 = New Round!
    //97 = New Game!
	char numero[] = "sound/correndo1.wav";
	FSOUND_SAMPLE * son = NULL;                     // NULL is significant
	if (c == '0')
		numero[6]='e';
	else
		numero[6]='p';
	numero[8] = a;
	numero[9] = b;
	son = FSOUND_Sample_Load ( FSOUND_FREE, numero,  FSOUND_HW2D, 0, 0);
	FSOUND_PlaySoundEx ( FSOUND_FREE, son, NULL, 0 );
}
