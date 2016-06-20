CC=g++
CFLAGS=-c -pthread -m64 -I/home/jake/Root/root_v5.34.32/include
LDFLAGS=-L/home/jake/Root/root_v5.34.32/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lSpectrum
SOURCES=main.cc HistoMaker.cc EnergyCal.cc PositionCal.cc
OBJECTS=$(SOURCES:.cc=.o)


caliope: $(SOURCES) $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o caliope $(LDFLAGS)  
	



	
	
