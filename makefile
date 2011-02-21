PROJECT = AUTOEXEC
ADDRESS = 0x7F0000

CC     = arm-elf-gcc
CFLAGS = -nostdlib -march=armv5te -fno-builtin

AS      = arm-elf-as
ASFLAGS = 

LDFLAGS = -Wl,-Ttext,$(ADDRESS)
OBJCOPY = arm-elf-objcopy

S_OBJS = entry.o      \
         entry_subs.o \
         gui.o
         
C_OBJS = init.o     \
         utils.o    \
         menu.o     \
         display.o  \
         settings.o \
         main.o


all: $(PROJECT).BIN

$(PROJECT).BIN: $(PROJECT).arm.elf
	$(OBJCOPY) -O binary $(PROJECT).arm.elf $(PROJECT).BIN

$(PROJECT).arm.elf: $(S_OBJS) $(C_OBJS) link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f *.o; 
	rm -f $(PROJECT).arm.elf
