
CFLAGS  := -c -fPIC `pkg-config --cflags glfw3` `pkg-config --cflags gl` \
	-DGL_GLEXT_PROTOTYPES
LDFLAGS :=
LDLIBS  := `pkg-config --libs glfw3` `pkg-config --libs gl`

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

gltest: $(OBJS)
	gcc $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

src/%.o: src/%.c
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f gltest src/*.o

.PHONY: clean

