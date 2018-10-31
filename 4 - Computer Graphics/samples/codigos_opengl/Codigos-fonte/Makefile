
INCPATH = -I /usr/X11R6/include/ -I .
LIBS = -lglut -lGLU -lGL -lXi -lX11 -lm -lpthread -ljpeg -lGLEW
LIBPATH = -L/usr/lib -L/usr/X11R6/lib/
CXXFLAGS = -g -Wall

%:%.c
	gcc $(INCPATH) $(LIBPATH) $^ $(LIBS) $(CFLAGS) -o $@

%:%.cpp
	g++ $(INCPATH) $(LIBPATH) $^ $(LIBS) $(CXXFLAGS) -o $@

