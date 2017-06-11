/*
classSoundMaster.cpp

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

#include "classSoundMaster.h"
#include "classSound.h"

// Set up the defaults.
classSoundMaster::classSoundMaster( bool soundson )
{
	sndList = NULL;
	AllSoundsOn = soundson;
}

// Destroy the objects in the list.
classSoundMaster::~classSoundMaster( )
{
	while( sndList != NULL )
		DelSound( sndList -> Id );
}

// Add the sound into the linked list and load the sound file into memory
void classSoundMaster::AddSound( int id,const char *path, bool allow, bool enabled )
{
	DelSound( id );  // If in the list, delete the sound and re-add it.  (The path may have changed or something)
	
	if( sndList == NULL )
	{
		sndList = new sounds;
		sndPtr = sndList;
	}
	else
	{

		sndPtr = sndList;
		while( sndPtr -> Next != NULL )
			sndPtr = sndPtr -> Next;
		sndPtr -> Next = new sounds;
		sndPtr = sndPtr -> Next;
	}

	sndPtr -> Next = NULL;
	sndPtr -> Sound = new classSound( path );
	sndPtr -> AllowMultiple = allow;
	sndPtr -> Enabled = enabled;
	sndPtr -> Id = id;
	
	if( !sndPtr -> Sound -> IsOK() )
		DelSound( id );
}

// Trash the sound and free some mem and stuff
void classSoundMaster::DelSound( int id )
{
	if( !FindRecord( id ) )
		return;

	sounds *Temp = NULL;
	
	sndPtr = sndList;

	while( sndPtr -> Id != id )
	{
		Temp = sndPtr;
		sndPtr = sndPtr -> Next;
	}
	
	
	if( Temp == NULL )
	{
		sndList = sndList -> Next;
 		delete sndPtr;
 	}
	else
	{

		Temp -> Next = sndPtr -> Next;
		delete sndPtr;
	}

}

// Internal function to find the sound in the linked list
// It sets the sndPtr pointer.  It doesn't return a pointer like it should
// because I was lazy and figured that it doesn't really matter anyway.
// Change it if you want.  (This is free, after all)
bool classSoundMaster::FindRecord( int id )
{
	bool Looking = true;
	
	sndPtr = sndList;
	while( sndPtr != NULL && Looking )
	{
		if( sndPtr -> Id != id )
			sndPtr = sndPtr -> Next;
		else
			Looking = false;
	}
 	
	if( Looking )
		return false;
	
	return true;
}

// Simply set a flag to (dis)allow a sound to be played more than
// one time at a time.  (In other words, if you call PlaySound( id )
// again before the sound is played, setting AllowMultiple to false
// will not play the sound over itself.  It just ignores PlaySound calls.)
void classSoundMaster::AllowMultiple( int id, bool allow )
{
	if( FindRecord( id ) )
		sndPtr -> Sound -> AllowMultiple = allow;
}

// Just plays the sound.  (Unless of course sounds are disabled)
void classSoundMaster::PlaySound( int id )
{
	if( FindRecord( id ) )
 		if( sndPtr -> Enabled && AllSoundsOn )
			sndPtr -> Sound -> PlaySound();	
}

// This one will set an individual sound enabled or disabled.
void classSoundMaster::SetEnabled( int id, bool enable )
{
	if( FindRecord( id ) )
		sndPtr -> Enabled = enable;	
}

// This one will enable or disable the entire set of sounds in this
// object.
void classSoundMaster::SetEnabled( bool enable )
{
	AllSoundsOn = enable;
}

// This one will return an individual sound's enabled or disabled status.
bool classSoundMaster::IsEnabled( int id )
{
	if( FindRecord( id ) )
		return sndPtr -> Enabled;
	else
		return false;  // Not found, just return false
}

// This one will return the entire object's enable or disable status
bool classSoundMaster::IsEnabled( )
{
	return AllSoundsOn;
}

// Just checks to see if the sound is playing.
bool classSoundMaster::IsPlaying( int id )
{
	if( FindRecord( id ) )
		return sndPtr -> Sound -> IsPlaying();
	else
		return false;
}