

TARGET=exbed

ALL=${TARGET}

${TARGET}:
	cd src; make
	mv src/exbed .

.PHONY: clean
	-rm exbed
	cd src; make clean
