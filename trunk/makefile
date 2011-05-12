PROJECT = AUTOEXEC
ADDRESS = 0x7F0000
VERSION = 99999999
RELEASE = 0

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
         languages.o      \
         viewfinder.o     \
         af_patterns.o    \

OBJS   = $(S_OBJS) $(C_OBJS)
DEPS   = $(C_OBJS:.o=.d)

BASE   = /tmp/400plus-$(VERSION)-$(RELEASE)

all: $(PROJECT).BIN

$(PROJECT).BIN: $(PROJECT).arm.elf
	$(OBJCOPY) -O binary $(PROJECT).arm.elf $(PROJECT).BIN
	rm -f $(PROJECT).arm.elf

$(PROJECT).arm.elf: $(OBJS) link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o $@ $^

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT $@ $*.c -o $*.d
	
%.o: %.c %.d
	$(CC) $(CFLAGS) -c $<
	
%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(DEPS)
	rm -f $(PROJECT).BIN $(PROJECT).arm.elf

-include $(DEPS)
