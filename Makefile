.PHONY: clean all

all: noqte.ttf

noqte.ttf: noqte.sfd
	fontforge -quiet -lang ff -c "Open(\"noqte.sfd\",1);Generate(\"noqte.ttf\")" 

clean:
	rm noqte.ttf