PROJECT := AUTOEXEC
ADDRESS := 0x7E0000

ifndef CROSS_COMPILE
	CROSS_COMPILE := arm-elf-
endif

ifdef RELEASE
	VERSION := VER-$(RELEASE)
	RELNAME := 400plus-$(RELEASE)
	D_FLAGS := -DRELEASE
else
	VERSION := REV-$(shell git rev-parse --short HEAD)
	D_FLAGS :=
endif

USE_FONTS := -DUSE_FONT_SMALL

COMMON_FLAGS := \
	$(USE_FONTS)                      \
	-DVERSION='"$(VERSION)"'          \
	-Wall                             \
	-Wp,-MMD,$(dir $@).$(notdir $@).d \
	-Wp,-MT,$@                        \
	-mcpu=arm946e-s                   \
	-march=armv5te                    \
	-fno-builtin                      \
	-nostdlib                         \
	-fomit-frame-pointer              \
	-fno-strict-aliasing              \
	-mfloat-abi=soft                  \
	-msoft-float                      \
	-mfpu=fpa                         \

	#-nostdinc                         \
	#-fno-builtin-puts                 \
	#-fno-builtin-sprintf              \
	#-fno-builtin-bzero                \
	#-fno-builtin-memset               \
	#-fno-builtin-printf               \

	#-mlong-calls or -fPIC will fix the rellocation problems with the linker on 64bit toolchain
	#-mlong-calls                      \

	#-fomit-frame-pointer \
	#-fno-strict-aliasing \

	# alex had issues with struct alignment (gcc-4.6.0, -Os) in ML
	# this fixes them, keep it here in case we need it
	#-mstructure-size-boundary=32 \

CC     := $(CROSS_COMPILE)gcc
CFLAGS += $(COMMON_FLAGS)              \
	$(D_FLAGS)                         \
	-Os                                \
	-nostdinc                          \
	-Ivxworks                          \
	-Werror                            \
	-Wstrict-prototypes                \
	-Wmissing-prototypes               \
	-Wno-char-subscripts               \
	-fdata-sections                    \
	-ffunction-sections                \

	#-fomit-frame-pointer  \
	#-fno-strict-aliasing  \
	#-Wno-unused-parameter \
	#-Wno-unused-function  \

AS      := $(CROSS_COMPILE)as
ASFLAGS := $(COMMON_FLAGS)

LD      := $(CROSS_COMPILE)ld
LDFLAGS := -Wl,-Ttext,$(ADDRESS) -Wl,-T,link.script -Wl,-Map,autoexec.map -Wl,--gc-sections -e _start -lm -lgcc -lc

OBJCOPY := $(CROSS_COMPILE)objcopy

S_SRCS := $(wildcard *.S) $(wildcard vxworks/*.S) $(wildcard firmware/*.S)
C_SRCS := $(wildcard *.c) $(wildcard vxworks/*.c) $(wildcard firmware/*.c)

S_OBJS := $(S_SRCS:.S=.o)
C_OBJS := $(C_SRCS:.c=.o)

OBJS  := $(S_OBJS) $(C_OBJS)

ECHO := "/bin/echo"

ifdef TERM
	BOLD := "\033[1m"
	NORM := "\033[0m"
endif

all: $(PROJECT).BIN languages.ini languages/new_lang.ini
	@$(ECHO) -e $(BOLD)[ALL]$(NORM)
	@ls -l AUTOEXEC.BIN

release: clean
	@$(ECHO) -e $(BOLD)[RELEASE]$(NORM)
	@git checkout-index -a --prefix $(RELNAME)/src/
	@zip -9 -r $(RELNAME).src.zip $(RELNAME)

	@mkdir $(RELNAME)/bin
	@cd $(RELNAME)/src && CFLAGS="" make
	@cp $(RELNAME)/src/AUTOEXEC.BIN $(RELNAME)/src/languages.ini $(RELNAME)/bin/
	@zip -9 -r $(RELNAME).bin.zip $(RELNAME)/bin/

	@$(ECHO) -e $(BOLD)[ZIP]$(NORM)
	@rm -rf $(RELNAME)
	@ls -l $(RELNAME).src.zip $(RELNAME).bin.zip

$(PROJECT).BIN: $(PROJECT).arm.elf
	@$(ECHO) -e $(BOLD)[OBJCOPY]:$(NORM) $@
	$(OBJCOPY) -O binary $(PROJECT).arm.elf $(PROJECT).BIN

$(PROJECT).arm.elf: $(OBJS) link.script
	@$(ECHO) -e $(BOLD)[LINK]:$(NORM) $@
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(ECHO) -e $(BOLD)[C]:$(NORM) $<
	@$(CC) $(CFLAGS) -c $<

%.o: %.S
	@$(ECHO) -e $(BOLD)[ASM]:$(NORM) $<
	@$(CC) $(ASFLAGS) -c -o $@ $<

clean:
	@$(ECHO) -e $(BOLD)[CLEAN]$(NORM)
	rm -f $(OBJS) .*.o.d
	rm -f $(PROJECT).arm.elf $(PROJECT).BIN

languages.ini: languages.h languages/*.ini
	@$(ECHO) -e $(BOLD)[I18N]:$(NORM) $@
	@./languages/lang_tool.pl -q -f languages -l languages.h -o languages.ini

languages/new_lang.ini: languages.h
	@$(ECHO) -e $(BOLD)[I18N]:$(NORM) $@
	@./languages/lang_tool.pl -q -f languages -l languages.h -g

-include .*.d

