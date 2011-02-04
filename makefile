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
	cp $(name).BIN G:\\$(name).BIN

$(name).arm.elf:entry.o entry_subs.o init.o main.o link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o$@ $^

entry.o:entry.S

main.o:main.c

init.o:init.c

entry_subs.o: entry_subs.S


clean:
	rm *.o; rm $(name).arm.elf
