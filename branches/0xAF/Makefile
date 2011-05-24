PROJECT = AUTOEXEC
ADDRESS = 0x7F0000
VERSION = $(shell [[ -d .svn ]] && svn info | grep Revision | cut -d' ' -f2 || date +'%Y%m%d')
# make release RELEASE=X    - to change the release number
RELEASE = 0

CC     = arm-elf-gcc
CFLAGS+= -Os -nostdlib -march=armv5te -fno-builtin -DVERSION=$(VERSION)

AS      = arm-elf-as
ASFLAGS = 

LDFLAGS = -Wl,-Ttext,$(ADDRESS)
OBJCOPY = arm-elf-objcopy

S_OBJS = entry.o      \
         entry_subs.o \
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
DEPS   = $(C_OBJS:.o=.d)

all: $(PROJECT).BIN

CDATE := $(shell date +%Y%m%d)
RELVER := $(CDATE)-$(RELEASE)

release: clean
	@mkdir -p 400plus-$(RELVER)/bin
	@svn export . 400plus-$(RELVER)/src
	@sed -i "s/^VERSION\s*=.*/VERSION = $(CDATE)/" 400plus-$(RELVER)/src/Makefile
	@zip -9 -r 400plus-$(RELVER).src.zip 400plus-$(RELVER)
	@cd 400plus-$(RELVER)/src && make
	@cp 400plus-$(RELVER)/src/AUTOEXEC.BIN 400plus-$(RELVER)/bin
	@rm -rf 400plus-$(RELVER)/src
	@zip -9 -r 400plus-$(RELVER).bin.zip 400plus-$(RELVER)
	@echo
	@rm -rf 400plus-$(RELVER)
	@ls -l 400plus-$(RELVER).src.zip 400plus-$(RELVER).bin.zip

$(PROJECT).BIN: $(PROJECT).arm.elf
	$(OBJCOPY) -O binary $(PROJECT).arm.elf $(PROJECT).BIN
	rm -f $(PROJECT).arm.elf
	@echo;echo;ls -l AUTOEXEC.BIN

$(PROJECT).arm.elf: $(OBJS) link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o $@ $^

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT $@ $*.c -o $*.d
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(DEPS)
	rm -f $(PROJECT).arm.elf

-include $(DEPS)
