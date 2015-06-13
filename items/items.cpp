// DO NOT EDIT! 
// This file is automatically modified.

#include "items.h"
#include "../jeu.h"

#include "life/life-bonus.h"

#include "gun/gun.h"
#include "gun/gun-ammo.h"
#include "gun/gun-bullet.h"

#include "shotgun/shotgun.h"
#include "shotgun/shotgun-ammo.h"
#include "shotgun/shotgun-bullet.h"

#include "fologun/fologun.h"
#include "fologun/fologun-ammo.h"
#include "fologun/fologun-bullet.h"

#include "plasmagun/plasmagun.h"
#include "plasmagun/plasmagun-ammo.h"
#include "plasmagun/plasmagun-bullet.h"

#include "autogun/autogun.h"
#include "autogun/autogun-ammo.h"
#include "autogun/autogun-bullet.h"
#include "autogun/tracking-bullet.h"

#include "clustergun/clustergun.h"
#include "clustergun/clustergun-ammo.h"
#include "clustergun/clustergun-bullet.h"

#include "minegun/minegun.h"
#include "minegun/minegun-ammo.h"
#include "minegun/minegun-bullet.h"

// INCLUDE_ITEM_PLACEHOLDER

void initItems(Jeu* jeu)
{
    LifeBonus::gameInit(jeu);
    jeu->registerBonus(new LifeBonus());

    Gun::gameInit(jeu);
    GunAmmo::gameInit(jeu);
    GunBullet::gameInit(jeu);
    jeu->registerArme(new Gun(), new GunAmmo());
    
    Shotgun::gameInit(jeu);
    ShotgunAmmo::gameInit(jeu);
    ShotgunBullet::gameInit(jeu);
    jeu->registerArme(new Shotgun(), new ShotgunAmmo());

    Fologun::gameInit(jeu);
    FologunAmmo::gameInit(jeu);
    FologunBullet::gameInit(jeu);
    jeu->registerArme(new Fologun(), new FologunAmmo());

    Plasmagun::gameInit(jeu);
    PlasmagunAmmo::gameInit(jeu);
    PlasmagunBullet::gameInit(jeu);
    jeu->registerArme(new Plasmagun(), new PlasmagunAmmo());

    Autogun::gameInit(jeu);
    AutogunAmmo::gameInit(jeu);
    AutogunBullet::gameInit(jeu);
    TrackingBullet::gameInit(jeu);
    jeu->registerArme(new Autogun(), new AutogunAmmo());

    Clustergun::gameInit(jeu);
    ClustergunAmmo::gameInit(jeu);
    ClustergunBullet::gameInit(jeu);
    jeu->registerArme(new Clustergun(), new ClustergunAmmo());

    Minegun::gameInit(jeu);
    MinegunAmmo::gameInit(jeu);
    MinegunBullet::gameInit(jeu);
    jeu->registerArme(new Minegun(), new MinegunAmmo());

    // INIT_ITEM_PLACEHOLDER
}

void endItems(Jeu* jeu)
{
    LifeBonus::gameEnd(jeu);
        
    Gun::gameEnd(jeu);
    GunAmmo::gameEnd(jeu);
    GunBullet::gameEnd(jeu);

    Shotgun::gameEnd(jeu);
    ShotgunAmmo::gameEnd(jeu);
    ShotgunBullet::gameEnd(jeu);

    Fologun::gameEnd(jeu);
    FologunAmmo::gameEnd(jeu);
    FologunBullet::gameEnd(jeu);

    Plasmagun::gameEnd(jeu);
    PlasmagunAmmo::gameEnd(jeu);
    PlasmagunBullet::gameEnd(jeu);

    Autogun::gameEnd(jeu);
    AutogunAmmo::gameEnd(jeu);
    AutogunBullet::gameEnd(jeu);
    TrackingBullet::gameEnd(jeu);

    Clustergun::gameEnd(jeu);
    ClustergunAmmo::gameEnd(jeu);
    ClustergunBullet::gameEnd(jeu);

    Minegun::gameEnd(jeu);
    MinegunAmmo::gameEnd(jeu);
    MinegunBullet::gameEnd(jeu);

    // END_ITEM_PLACEHOLDER
}
