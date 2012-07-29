PROJECT := AUTOEXEC
ADDRESS := 0x7E0000

ifdef RELEASE
	VERSION = V-$(RELEASE)
	RELNAME = 400plus-$(RELEASE)
	W_FLAGS = -Werror -Wno-implicit-function-declaration
else
	VERSION = $(shell [[ -d .svn ]] && echo "R-`svn info | fgrep Revision | cut -d' ' -f2 `" || echo "B-`date +'%Y%m%d'`")
	RELNAME = 400plus-$(shell date +'%Y%m%d')-0
	W_FLAGS =
endif

COMMON_FLAGS =\
	-Wall                             \
	-Wp,-MMD,$(dir $@).$(notdir $@).d \
	-Wp,-MT,$@                        \
	-mcpu=arm946e-s                   \
	-DVERSION='"$(VERSION)"'          \
	-mfloat-abi=soft                  \
	-msoft-float                      \
	-fno-builtin                      \
	-nostdinc                         \
	-nostdlib                         \
	-fomit-frame-pointer              \
	-fno-strict-aliasing              \
	-mfpu=fpa

	#-fno-builtin-puts                 \
	#-fno-builtin-sprintf              \
	#-fno-builtin-bzero                \
	#-fno-builtin-memset               \
	#-fno-builtin-printf               \

	# -mlong-calls or -fPIC will fix the rellocation problems with the linker on 64bit toolchain
	#-mlong-calls                      \

	#-Werror              \
	#-fomit-frame-pointer \
	#-fno-strict-aliasing \


# alex had issues with struct alignment (gcc-4.6.0, -Os) in ML
# this fixes them, keep it here in case we need it
	#-mstructure-size-boundary=32 \

CC     := arm-elf-gcc
CFLAGS += $(COMMON_FLAGS) $(W_FLAGS)   \
	-Os                                \
	-Wno-char-subscripts               \

	#-fomit-frame-pointer  \
	#-fno-strict-aliasing  \
	#-Wno-unused-parameter \
	#-Wno-unused-function  \

AS      := arm-elf-as
ASFLAGS := $(COMMON_FLAGS)

LD      := arm-elf-ld
LDFLAGS := -Wl,-Ttext,$(ADDRESS) -Wl,-T,link.script -e _start -lgcc

OBJCOPY := arm-elf-objcopy

S_OBJS := entry.o         \
         funclist.o       \

C_OBJS := init.o          \
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
         display.o        \
         settings.o       \
         presets.o        \
         scripts.o        \
         viewfinder.o     \
         af_patterns.o    \
         debug.o          \

OBJS  := $(S_OBJS) $(C_OBJS)

BOLD="\033[1m"
NORM="\033[0m"
ECHO="/bin/echo"

all: languages.ini $(PROJECT).BIN

release: clean
	@mkdir $(RELNAME)
	@svn export . $(RELNAME)/src
	@zip -9 -r $(RELNAME).src.zip $(RELNAME)

	@mkdir $(RELNAME)/bin
	@cd $(RELNAME)/src && CFLAGS="" make
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
	$(CC) $(CFLAGS) -Wl,-T,link.script -lgcc -o $@ $^

%.o: %.c
	@$(ECHO) -e $(BOLD)[C]:$(NORM) $<
	@$(CC) $(CFLAGS) -c $<

%.o: %.S
	@$(ECHO) -e $(BOLD)[ASM]:$(NORM) $<
	@$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) .*.o.d
	rm -f $(PROJECT).arm.elf

languages.ini: languages.h languages/*.ini
	@$(ECHO) -e $(BOLD)[GEN]$(NORM) languages.ini, new_lang.ini
	@./languages/lang_tool.pl -q -f languages -l languages.h -o languages.ini
	@./languages/lang_tool.pl -q -f languages -l languages.h -g `svn info languages.h | grep "Last Changed Rev" | cut -d ':' -f2`

-include .*.d

