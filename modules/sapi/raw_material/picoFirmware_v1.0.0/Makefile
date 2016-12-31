-include project.mk

# default project
PROJECT ?= examples/picoblinky
TARGET ?= lpc4337_m4
BOARD ?= picociaa

# application name
PROJECT_NAME := $(notdir $(PROJECT))

# source files folder
PROJECT_SRC_FOLDERS := $(PROJECT)/src

# header files folder
PROJECT_INC_FOLDERS := $(PROJECT)/inc

# source files
PROJECT_C_FILES := $(wildcard $(PROJECT)/src/*.c)
PROJECT_ASM_FILES := $(wildcard $(PROJECT)/src/*.S)

# Default cross-toolchain
CROSS_PREFIX ?= arm-none-eabi-

# OpenOCD configuration file
CFG_FILE := etc/openocd/lpc54102_cd.cfg

# Download command
DOWNLOAD_CMD := $(OOCD_PATH)openocd -f $(CFG_FILE) -c "init" -c "reset halt" -c "flash write_image erase unlock out/picofw.bin 0x00000000 bin" -c "reset run" -c "shutdown"

# Compile/Link flags
LFLAGS  := -nostdlib -fno-builtin -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 \
           -mfloat-abi=softfp -Xlinker -Map=out/picofw.map \
			  -Wl,--gc-sections -ggdb3

# Linker scripts
LD_FILE := -Tetc/ld/lpc54102_m4_lib.ld \
           -Tetc/ld/lpc54102_m4_mem.ld \
		       -Tetc/ld/lpc54102_m4.ld
# Libs
LIBS := lib/libbase.a lib/libpicoapi.a lib/libboard.a lib/libchip.a lib/libpower.a

# Includes
INCLUDES := -Iinc $(addprefix -I,$(PROJECT_INC_FOLDERS))

all:
	@echo "Making project $(PROJECT)..."
	@$(GCC_PATH)$(CROSS_PREFIX)gcc $(INCLUDES) $(LFLAGS) $(LD_FILE) -o out/picofw.axf $(PROJECT_C_FILES) $(OBJ_FILES) -Xlinker --start-group $(LIBS) -Xlinker --end-group -lc -lrdimon
	@$(GCC_PATH)$(CROSS_PREFIX)size out/picofw.axf
	@$(GCC_PATH)$(CROSS_PREFIX)objcopy -v -O binary out/picofw.axf out/picofw.bin

clean:
	rm -f out/picofw.*

download: all
	@$(DOWNLOAD_CMD)
