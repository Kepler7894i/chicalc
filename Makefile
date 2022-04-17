# $@ = target(s), $< = sources
# Shell commands in makefile have to be on one line or have \ at end of lines

bin/chicalc: src/main.c
	if [ ! -d "bin" ]; then mkdir bin; fi

	gcc src/main.c -o bin/chicalc

run:
	bin/chicalc

clean:
	rm -rf bin