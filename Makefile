#CC = gcc
CC = arm-linux-gnueabi-gcc
TARGET_ROOTFS   := rootfs
INSTALLROOTFS := ${CPS_SDK_INSTALL_FULLDIR}/$(TARGET_ROOTFS)
INSTALLDIR := $(INSTALLROOTFS)/home/sample/eeprom

all:eeprom_dump

eeprom_dump: eeprom_dump.c
	${CC} -o eeprom_dump eeprom_dump.c

install: $(INSTALLDIR)
	install -c eeprom_dump $(INSTALLDIR)

$(INSTALLDIR):
	mkdir $(INSTALLDIR)

clean:
	rm -f eeprom_dump