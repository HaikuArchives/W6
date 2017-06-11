/*
classSound.cpp

By: Sean Heber (bigzaphod@legions.com)
Come and visit a cool site:  http://www.legions.com/

You are free to use this class for anything you want.  All that I ask is that
you please credit me and/or e-mail me and let me know what you're doing with it.

Also, if you are distributing source with your application, please keep this
comment and add a note with any changes you may have made to the class and how
it works.

As is standard, I take no responsibility if this causes any damage at all.  No matter what.  Forever.

(Note that this is not being released under the GPL or anything like that, so feel
 free to use it in a commercial program if you want.  I'll be honored if you do :-)

Have fun, drink lots of Dew, and never forget THE answer: 42.
*/


#include "classSound.h"

// The constructor actually loads and stores the sound file into
// memory.
classSound::classSound(const char *path)
{
	OK = false;			    // Guilty until proven inocent. (ie. broke until proven otherwise)
	AllowMultiple = false;  // By default don't allow multiple

	entry_ref ref;
	BEntry entry(path, true);

	if (entry.InitCheck() == B_OK && entry.GetRef(&ref) == B_OK)
	{
			sound = new BSound(&ref, true);  // Actually load the sound file into memory

			media_raw_audio_format fmt = sound->Format();  // Have Be figure out what the sound file is and set a type up.
			if (sound->InitCheck() == B_OK)
			{
				OK = true;
				player = new BSoundPlayer( &fmt, ref.name );  // Make a new player object with the sound type found above and the file that was loaded
				player->Start();  // Init the player object and get it all ready to go.
			}
	}
}

// Destroy the player (only if it was ever made)
classSound::~classSound( )
{
	if( OK )
	{
		player -> Stop();
		sound -> ReleaseRef();
		delete player;
	}
}

// Just plays the sound.  It also checks to make sure that it CAN and is ALLOWED to play the sound
void classSound::PlaySound( ) { 
	if( ( !OK || IsPlaying( ) ) && !( AllowMultiple && OK ) )
		return;

	player->SetVolume(1.0);  // Just setting the volume to 1.0 is probably fine.  It just means the sound plays as loud as it can according to where the user set the audio prefs.
	id = player->StartPlaying(sound);   // Actually allow Be to start playing (does NOT block!)
}


// Just check to see if the sound it playing
bool classSound::IsPlaying( )
{
	return ( OK && ( player->HasData( ) || player->IsPlaying( id ) ) );
}

// Just make sure everything went OK.  (Used so that you can simpy call this and if it's false, that means your sound file did not load correctly or something)
bool classSound::IsOK( )
{
	return OK;
}