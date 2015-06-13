#include "@weapon@-bullet.h"
#include "../../jeubot.h"

SDL_Surface* @Weapon@Bullet::_surface = NULL;

@Weapon@Bullet::@Weapon@Bullet() : Bullet()
{
}

void @Weapon@Bullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/@weapon@/bullet.bmp", 255, 0, 255); // transparency color
}

void @Weapon@Bullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

