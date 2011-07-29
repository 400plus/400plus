PROJECT = AUTOEXEC
ADDRESS = 0x7F0000
VERSION = 99999999
RELEASE = 0

CC     = arm-elf-gcc
CFLAGS = -nostdlib -march=armv5te -fno-builtin -DVERSION=$(VERSION) -Wall -Os

AS      = arm-elf-as
ASFLAGS = 

LDFLAGS = -Wl,-Ttext,$(ADDRESS)
OBJCOPY = arm-elf-objcopy

S_OBJS = entry.o      \
         funclist.o   \
         gui.o        \
         
C_OBJS = init.o           \
         main.o           \
	     mainctrl.o       \
         tasks.o          \
         languages.o      \
         utils.o          \
         menu.o           \
         menu_presets.o   \
         menu_rename.o    \
         menu_settings.o  \
         menu_developer.o \
         menu_shortcuts.o \
         info.o           \
         display.o        \
         settings.o       \
         presets.o        \
         scripts.o        \
         viewfinder.o     \
         af_patterns.o    \

OBJS   = $(S_OBJS) $(C_OBJS)

BASE   = ./400plus-$(VERSION)-$(RELEASE)

all: $(PROJECT).BIN

$(PROJECT).BIN: $(PROJECT).arm.elf
	$(OBJCOPY) -O binary $(PROJECT).arm.elf $(PROJECT).BIN
	rm -f $(PROJECT).arm.elf

$(PROJECT).arm.elf: $(OBJS) link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -Wp,-MMD,.$(notdir $@).d -Wp,-MT,$@ -c $<
	
%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) .*.d
	rm -f $(PROJECT).BIN $(PROJECT).arm.elf

release: clean all
	mkdir $(BASE)
	mkdir $(BASE)/bin
	cp $(PROJECT).BIN $(BASE)/bin/
	zip -r $(BASE).bin.zip $(BASE)/bin/
	mkdir $(BASE)/src
	cp *.h *.c *.S *.txt link.script $(BASE)/src/
	zip -r $(BASE).src.zip $(BASE)/src/
	rm -rf $(BASE)

-include .*.d
