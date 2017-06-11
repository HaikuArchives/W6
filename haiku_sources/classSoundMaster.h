/*
classSoundMaster.h

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

#ifndef _SOUND_MASTER_H_
#define _SOUND_MASTER_H_

#include "classSound.h"

struct sounds
{
	classSound	*Sound;
	int			Id;
	bool		AllowMultiple;
	bool		Enabled;
	sounds*		Next;

	~sounds() { delete Sound; }
};

class classSoundMaster
{
	protected:
		// Stores the sound objects and IDs, etc.
		
		// The start of the list
		sounds* sndList;
		// A pointer I use to move around in the list
		sounds* sndPtr;
			
		// Internal function to find records (sets sndPtr)
		bool FindRecord( int );
		// The master switch that stores the status of the whole object
		bool AllSoundsOn;

	public:
		classSoundMaster( bool = true );  // Call with (false) if you want sounds disabled at first
		~classSoundMaster( );
		void AddSound( int,const char *, bool = false, bool = true );  // ( Sound_ID, Path to sound file, allow multiple, enabled)
		void DelSound( int );  // ( Sound_ID )
		void AllowMultiple( int, bool );  // ( Sound_ID, allow multiple )
		void PlaySound( int );  // ( Sound_ID )
		bool IsPlaying( int );  // ( Sound_ID )
		void SetEnabled( int, bool );  // ( Sound_ID, enable or not )
		bool IsEnabled( int );	//( Sound_ID ) returns if it's enabled or not
		void SetEnabled( bool );  // ( Enable or disable all sounds )
		bool IsEnabled( );	// returns if all sounds are enabled or not
};

#endif