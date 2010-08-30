#include "soundengine.h"

namespace CommonSounds
{
	void playClickSound()
	{
		SoundEngine::playSound( "data/sound/click.ogg" );
	}
}