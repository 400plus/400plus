PROJECT = AUTOEXEC
ADDRESS = 0x7F0000
VERSION = 99999999

CC     = arm-elf-gcc
CFLAGS = -nostdlib -march=armv5te -fno-builtin -DVERSION=$(VERSION) -Wall

AS      = arm-elf-as
ASFLAGS = 

LDFLAGS = -Wl,-Ttext,$(ADDRESS)
OBJCOPY = arm-elf-objcopy

S_OBJS = entry.o      \
         entry_subs.o \
         gui.o        \
         
C_OBJS = init.o           \
         main.o           \
         tasks.o          \
         utils.o          \
         menu.o           \
         menu_settings.o  \
         menu_developer.o \
         menu_shortcuts.o \
         info.o           \
         display.o        \
         settings.o       \
         scripts.o        \
         viewfinder.o     \
         af_patterns.o    \

all: $(PROJECT).BIN

release:
	make VERSION=`date +'%Y%m%d'`

$(PROJECT).BIN: $(PROJECT).arm.elf
	$(OBJCOPY) -O binary $(PROJECT).arm.elf $(PROJECT).BIN
	rm -f $(PROJECT).arm.elf

$(PROJECT).arm.elf: $(S_OBJS) $(C_OBJS) link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f $(PROJECT).arm.elf

