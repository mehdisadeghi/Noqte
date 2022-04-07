.PHONY: clean all watch

all: noqte.ttf

noqte.ttf: noqte.sfd
	fontforge -quiet -lang ff -c "Open(\"noqte.sfd\",1);Generate(\"noqte.ttf\")" 

ttftest: *.c
	gcc *.c \
		-I/usr/include/SDL2 -lSDL2 -lSDL2_ttf \
		-I/usr/include/harfbuzz -I/usr/include/freetype2 \
		-I/usr/include/glib-2.0 \
		-I/usr/lib/glib-2.0/include \
		-o ttftest

watch:
	./build.sh noqte.sfd ttftest.c

clean:
	rm -f noqte.ttf ttftest
