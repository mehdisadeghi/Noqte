.PHONY: clean all watch

all: noqte.ttf noqte.woff noqte.woff2 glyphs.png
noqte.ttf: noqte.sfd
	fontforge -quiet -lang ff -c "Open(\"noqte.sfd\",1);Generate(\"noqte.ttf\")"

noqte.woff: noqte.sfd
	fontforge -quiet -lang ff -c "Open(\"noqte.sfd\",1);Generate(\"noqte.woff\")"

noqte.woff2: noqte.sfd
	fontforge -quiet -lang ff -c "Open(\"noqte.sfd\",1);Generate(\"noqte.woff2\")"

noqte.tar.gz: noqte.ttf noqte.woff noqte.woff2 noqte.png
	tar czf noqte.tar.gz noqte.ttf noqte.woff noqte.woff2 glyphs.png

glyphs.png: ttftest
	./ttftest -s

ttftest: *.c
	gcc *.c \
		-I/usr/include/SDL2 -lSDL2 -lSDL2_ttf -lSDL2_image \
		-I/usr/include/harfbuzz -I/usr/include/freetype2 \
		-I/usr/include/glib-2.0 \
		-I/usr/lib/glib-2.0/include \
		-o ttftest

watch:
	./build.sh noqte.sfd ttftest.c

clean:
	rm -f noqte.ttf noqte.woff noqte.woff2 ttftest noqte.tar.gz
