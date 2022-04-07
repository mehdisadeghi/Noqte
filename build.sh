#!/bin/bash

if [ "$#" -lt 2 ]; then
	echo 'Usage: build.sh <FILE> [ ... ]'
fi

PID=
while inotifywait -e CLOSE_WRITE $@; do
	test "$PID" && kill -9 "$PID" 
	cp -r $1 backup/$(date --iso-8601=seconds)_$1
	fontforge -quiet -lang ff -c "Open(\"$1\",1);Generate(\"noqte.ttf\")" 
	echo Starting...
	make noqte.ttf ttftest
	./ttftest &
	PID=$!
	echo PID=$PID
	sleep 3
done