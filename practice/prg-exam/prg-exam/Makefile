# Compiler and linker settings
CFLAGS+= -std=c99 -pedantic -Wall -O2 -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS+= -lSDL2 -lSDL2_image -ljpeg  # Add missing libraries

# Target executable
TARGET=texam
OBJS=exam_utils.o save_jpeg.o texam.o xwin_sdl.o

# Build executable
bin: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

# Cleanup
clean:
	$(RM) $(OBJS) $(TARGET)
	$(RM) -rf *.ppm

