# galileo-projects
Some personal projects made for studying purposes, during the microcontrollers class at UFRGS.

## Requirements
The cross-compiler must be configured before running make, and the default compilation command stored on the env  variable CC.

The correspondent init file for the examples may be found under ./inid.d/ and must be properly set up for the executables to work

## Running Examples
To build all examples and the lib, simply run:

    make

For individual examples go inside the folder and run make for it (lib must be built before this step):

    cd examples/music/
    make ode
