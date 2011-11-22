PROJECT = AUTOEXEC
ADDRESS = 0x7E0000

ifdef RELEASE
	VERSION = V-$(RELEASE)
	RELNAME = 400plus-$(RELEASE)
else
	VERSION = $(shell [[ -d .svn ]] && echo "R-`svn info | fgrep Revision | cut -d' ' -f2 `" || echo "B-`date +'%Y%m%d'`")
	RELNAME = 400plus-$(shell date +'%Y%m%d')-0
endif

COMMON_FLAGS =\
	-Wall                             \
	-Werror                           \
	-Wp,-MMD,$(dir $@).$(notdir $@).d \
	-Wp,-MT,$@                        \
	-nostdlib                         \
	-fno-builtin                      \
	-mcpu=arm946e-s                   \
	-DVERSION='"$(VERSION)"'          \

	#-Werror              \
	#-mlong-calls         \
	#-fomit-frame-pointer \
	#-fno-strict-aliasing \

# check if this fixes the problems with FPA
# i get those compiler misunderstanding sometimes, when i import new ASM code
	#-mthumb-interwork \
	#-msoft-float \

# alex had issues with struct alignment (gcc-4.6.0, -Os) in ML
# this fixes them, keep it here in case we need it
	#-mstructure-size-boundary=32 \


CC     = arm-elf-gcc
CFLAGS+= $(COMMON_FLAGS)               \
	-Os                                \
	-Wno-implicit-function-declaration \
	-Wno-char-subscripts               \

	#-fomit-frame-pointer  \
	#-fno-strict-aliasing  \
	#-Wno-unused-parameter \
	#-Wno-unused-function  \


AS      = arm-elf-as
ASFLAGS = $(COMMON_FLAGS)

LDFLAGS = -Wl,-Ttext,$(ADDRESS) -e _start

OBJCOPY = arm-elf-objcopy

S_OBJS = entry.o          \
         funclist.o       \

C_OBJS = init.o           \
         gui.o            \
         main.o           \
         mainctrl.o       \
         tasks.o          \
         ini.o            \
         languages.o      \
         utils.o          \
         memspy.o         \
         menu.o           \
         menupage.o       \
         menuitem.o       \
         menu_info.o      \
         menu_main.o      \
         menu_params.o    \
         menu_presets.o   \
         menu_rename.o    \
         menu_scripts.o   \
         menu_settings.o  \
         menu_developer.o \
         menu_shortcuts.o \
         display.o        \
         settings.o       \
         presets.o        \
         scripts.o        \
         viewfinder.o     \
         af_patterns.o    \
         debug.o          \

OBJS   = $(S_OBJS) $(C_OBJS)

all: $(PROJECT).BIN

release: clean
	@mkdir $(RELNAME)
	@svn export . $(RELNAME)/src
	@zip -9 -r $(RELNAME).src.zip $(RELNAME)

	@mkdir $(RELNAME)/bin
	@cd $(RELNAME)/src && make
	@cp $(RELNAME)/src/AUTOEXEC.BIN $(RELNAME)/src/languages.ini $(RELNAME)/bin/
	@zip -9 -r $(RELNAME).bin.zip $(RELNAME)/bin/

	@echo
	@rm -rf $(RELNAME)
	@ls -l $(RELNAME).src.zip $(RELNAME).bin.zip

$(PROJECT).BIN: $(PROJECT).arm.elf
	$(OBJCOPY) -O binary $(PROJECT).arm.elf $(PROJECT).BIN
	rm -f $(PROJECT).arm.elf
	@echo; echo; ls -l AUTOEXEC.BIN

$(PROJECT).arm.elf: $(OBJS) link.script
	$(CC) $(CFLAGS) -Wl,-T,link.script -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.S
	$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) .*.o.d
	rm -f $(PROJECT).arm.elf

-include .*.d

