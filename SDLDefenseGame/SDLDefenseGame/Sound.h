#ifndef __SOUND_H__
#define __SOUND_H__

#include <SDL.h>
#include <SDL_mixer.h>

class BGM
{
private:
	Mix_Music * m_pMusic;

public:
	BGM( const char * _cFileName )
	{
		m_pMusic = Mix_LoadMUS( _cFileName );
		if( m_pMusic == NULL )
			printf( "SOUND LOAD ERROR\n" );
	};

	~BGM()
	{
		Mix_FreeMusic( m_pMusic );
	};

	void Play()
	{
		Mix_PlayMusic( m_pMusic, -1 );
	}

	void Pause()
	{
		Mix_PauseMusic();
	}

	void Stop()
	{
		Mix_FadeOutMusic( 3000 );
	}
};

class SFX
{
private:
	Mix_Chunk * m_pSound;

public:
	SFX( const char * _cFileName )
	{
		m_pSound = Mix_LoadWAV( _cFileName );
		if( m_pSound == NULL )
			printf( "SOUND LOAD ERROR\n" );
	};

	~SFX()
	{
		Mix_FreeChunk( m_pSound );
	};

	void Play()
	{
		Mix_PlayChannel( -1, m_pSound, 0 );
	}
};

#endif