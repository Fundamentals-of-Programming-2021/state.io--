#!/bin/sh

gcc -o poly-map poly-map.c `sdl2-config --cf\lags --libs` -lSDL2_image -lSDL2_gfx && ./poly-map
