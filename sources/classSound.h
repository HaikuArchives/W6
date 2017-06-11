/*
classSound.h

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

#ifndef _SOUND_H_
#define _SOUND_H_

#include <Sound.h>
#include <SoundPlayer.h>
#include <Entry.h>
#include <Path.h>
#include <MediaDefs.h>

class classSound
{
	protected:
		// Pointer for the player object I need
		BSoundPlayer *player;
		// Keeps track of the player's id so we can check on it later.
		BSoundPlayer::play_id id;
		// A nice pointer to the actual sound info object
		BSound *sound;
		// The master check of everything
		bool OK;
			
	public:
		// Pass it a path to a sound file (any format that Be supports--not MIDI)
		classSound(const char *);
		~classSound( );
		// Allow this sound to be played more than once over itself
		bool AllowMultiple;
		// Actually play the sound
		void PlaySound( );
		// Check to see if the sound is playing
		bool IsPlaying( );
		// Make sure it's all OK
		bool IsOK( );
};

#endif