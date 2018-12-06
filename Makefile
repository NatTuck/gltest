
CFLAGS  := -c -fPIC `pkg-config --cflags glfw3` `pkg-config --cflags glesv2` \
	-DGL_GLEXT_PROTOTYPES
LDFLAGS :=
LDLIBS  := `pkg-config --libs glfw3` `pkg-config --libs glesv2`

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

gltest: $(OBJS)
	gcc $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

src/%.o: src/%.c
	gcc $(CFLAGS) -o $@ $<

run: gltest
	MESA_GLSL_CACHE_DISABLE=true ./gltest

clean:
	rm -f gltest src/*.o

prereqs:
	sudo apt install libglfw3-dev

.PHONY: run clean prereqs

