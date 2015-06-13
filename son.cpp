#include "son.h"

#include "SDL/SDL_mixer.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

#define NB_BUF        5


//The music that will be played
Mix_Music *music = NULL;

vector<Mix_Chunk*> sons;

bool InitSon()
{
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024/*4096*/ ) == -1 )
        return false;

    //Mix_ReserveChannels(8);
    Mix_AllocateChannels(8);

    return true;
}

void FinSons()
{
    for(unsigned int i = 0; i < sons.size(); i++)
        Mix_FreeChunk(sons[i]);

    //Quit SDL_mixer
    Mix_CloseAudio();
}

//int NouveauSon(char fichier[])
int NouveauSon(const char fichier[])
{
    Mix_Chunk* son = Mix_LoadWAV( fichier );

    if( !son ) 
    {
        cout << "Cannot load sound " << fichier << endl <<
            SDL_GetError() << endl;
        
        return -1;
    }

    sons.push_back(son);

    return sons.size()-1;
}

void JouerSon(int s)
{
    Mix_PlayChannel( -1, sons[s], 0 );
}

void JouerSon(int s, int vol)
{
    // PAS BON !!! voir doc SDL_mixer
    Mix_Volume(-1, vol);
    Mix_PlayChannel( -1, sons[s], 0 );
}

