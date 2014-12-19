#include <SDL.h>
#include <SDL_image.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "Texture.h"
#include "Sound.h"
#include "manager_game.h"

int main( int argc, char * argv[] )
{
	// 초기화
	if( GameManager::Instance()->Initialize() == false )
		printf( "에러로 인해 실행할 수 없습니다. 쟌넨\n" );
	
	while( (( GameManager * )GameManager::Instance())->IsGameRunning() )
	{
		(( GameManager * )GameManager::Instance())->Work();

		(( GameManager * )GameManager::Instance())->GetCurrentScene()->Render( (( GameManager * )GameManager::Instance())->GetGlobalRenderer() );
	}

	GameManager::Instance()->Destroy();

	return 0;
}