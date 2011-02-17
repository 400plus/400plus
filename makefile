name=AUTOEXEC
entryadr=0x7F0000

CFLAGS=-nostdlib -march=armv5te -fno-builtin
LDFLAGS=-Wl,-Ttext,$(entryadr)
CC=arm-elf-gcc
AS=arm-elf-as
OBJCOPY=arm-elf-objcopy

all: $(name).BIN

$(name).BIN: $(name).arm.elf
	$(OBJCOPY) -O binary $(name).arm.elf $(name).BIN


$(name).arm.elf:entry.o entry_subs.o gui.o init.o menu.o settings.o main.o link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o$@ $^

entry_subs.o: entry_subs.S
entry.o:      entry.S
gui.o:        gui.S

init.o:     init.c
menu.o:     menu.c
settings.o: settings.c

main.o:main.c

clean:
	rm *.o; rm $(name).arm.elf
