LINK_TARGET = testp

OBJS =  \
	main.o \

CFLAGS = -Iinclude/ -I/usr/include/ $(shell pkg-config --cflags opencv)
LIBS = -l I2CMaster -l AVRI2CBootloader -l IntelHexParser -l RGBColorSensorArray $(shell pkg-config --libs opencv)

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : $(LINK_TARGET)
	@echo "Build complete"

clean :
	rm -f $(REBUILDABLES)
	@echo "Clean complete"

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ $^ $(LIBS)

%.o : %.cpp
	g++ $(CFLAGS) -g -o $@ -c $< $(LIBS)

test:
	sudo ./testp 1 60
