#!/bin/sh
g++ -pthread -m64 -I/home/jake/Root/root_v5.34.32/include imgHistos.cc -o imgHistos -L/home/jake/Root/root_v5.34.32/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic 
