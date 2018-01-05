## Space Game NX
This is a port of [Space Game](https://github.com/vgmoose/space) to the Switch, using libtransistor.

The game is currently fully playable, but there's no music, enemy count is limited to compared to the Wii U version, and some Switch-specific features are planned.

### Compiling
#### For Switch
Clone and setup libtransistor, for more detail [see this post](https://reswitchedweekly.github.io/Development-Setup/). 
```
git clone --recursive -b graphics-experimental-fs https://github.com/reswitched/libtransistor.git
cd libtransistor
make
cd ..
```

Then export an environment variable pointing to your libtransistor build, and run `make switch`:
```
export LIBTRANSISTOR_HOME=./libtransistor
make switch
```

A `spacenx.nro` file will be produced, which can be sent to the Switch with ace_loader.

#### For PC
This version of Space Game is ported to libsdl2, so the same code can be compiled on the computer as well. Just running `make` creates a binary file that can be executed. THe sdl2 library is required to compile it.

### License
This program is licensed under [the MIT license](https://opensource.org/licenses/MIT), see the original repo for more information.

