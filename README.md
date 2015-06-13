# flatwars
A 2D frag'em all game

_Horrible graphics!_ _Unbearable sound FX!_ _No introduction, no conclusion!_
(but so much fun to play!)

![Screenshot](img/screenshots/screenshot1.png)

## Install, Compile and Run
On Ubuntu and other distributions, you will need to install a few libraries:
```shell
$ sudo apt-get install libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev
```
and maybe other dependencies.

Then clone the repository:
```shell
$ git clone https://github.com/Metaxal/flatwars.git
```
Compile (sorry, no makefile):
```shell
$ cd flatwars
$ ./compile
```
Now it's ready to run:
```shell
$ ./flatwars
```

## How to play

You can use either the mouse or the keyboard, or both.
The some parameters such as screen resolution, keyboard configuration, board size, number of bots, etc. can be configured in the configuration file in the `cfg` directory.
By default, the `cfg/board.cfg` and `cfg/game.cfg` files are loaded. This can be changed on the command line with
```shell
$ ./flatwars -b <my-board-config-file> -g <my-game-config-file>
```


