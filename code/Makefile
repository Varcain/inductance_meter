PROJ_NAME = main

# Set toolchain
TC = /home/limak/x-tools/arm-cortex_m3-eabi/bin/arm-cortex_m3-eabi

# Set STM32 Cube path
STM32CUBE_PATH = /home/limak/Downloads/STM32Cube_FW_F1_V1.2.0

# Output paths
OBJ_DIR		= obj
OUT_DIR		= out

PROJ_NAME := $(addprefix $(OUT_DIR)/, $(PROJ_NAME))

# Set Tools
CC		= $(TC)-gcc
LD		= $(TC)-ld
AR		= $(TC)-ar
OBJCOPY	= $(TC)-objcopy
OBJDUMP	= $(TC)-objdump
SIZE	= $(TC)-size

# Set Dirs
SRC_DIRS = \
$(STM32CUBE_PATH)/Drivers/STM32F1xx_HAL_Driver/Src \
src

# Set Include Paths
INCLUDES 	=	-I$(STM32CUBE_PATH)/Drivers/CMSIS/Include/ \
				-I$(STM32CUBE_PATH)/Drivers/CMSIS/Device/ST/STM32F1xx/Include/ \
				-I$(STM32CUBE_PATH)/Drivers/STM32F1xx_HAL_Driver/Inc \
				-Iinc/

# Set Board
DEFINES 	= -DSTM32F100xB

# Set Libraries
LIBS		= -lm

# Set Compilation and Linking Flags
CFLAGS 		= $(DEFINES) $(INCLUDES)
CFLAGS		+= -g -Wall -Wno-missing-braces -std=c99 
CFLAGS		+= -O2 -ffunction-sections -fdata-sections -ffast-math -fsingle-precision-constant
CFLAGS		+= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft

ASFLAGS 	= -g -Wa,--warn -x assembler-with-cpp -mcpu=cortex-m3 -mthumb

LDFLAGS 	= -g -Tstm32f100rb_flash.ld $(LIBS) \
			-Xlinker --gc-sections \
			-Wl,-Map,$(PROJ_NAME).map

# Set Sources
C_SRCS := $(foreach dir, $(SRC_DIRS),$(wildcard $(dir)/*c))
# Set Sources
S_SRCS := $(foreach dir, $(SRC_DIRS),$(wildcard $(dir)/*s))
# Set Objects
OBJS := $(foreach src, $(C_SRCS),$(addprefix $(OBJ_DIR)/,$(notdir $(C_SRCS:.c=.o))))
OBJS += $(foreach src, $(S_SRCS),$(addprefix $(OBJ_DIR)/,$(notdir $(S_SRCS:.s=.o))))

# Default Target
all: mkdir $(PROJ_NAME).hex $(PROJ_NAME).lst info

# elf Target
$(PROJ_NAME).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo $@

# bin Target
$(PROJ_NAME).bin: $(PROJ_NAME).elf
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	@echo $@

$(PROJ_NAME).hex: $(PROJ_NAME).elf
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	@echo $@

$(PROJ_NAME).lst: $(PROJ_NAME).elf
	@$(OBJDUMP) -h -S $(PROJ_NAME).elf > $(PROJ_NAME).lst
	@echo $@

# Display Memory Usage Info
info: $(PROJ_NAME).elf
	@$(SIZE) --format=berkeley $(PROJ_NAME).elf

vpath %.c $(SRC_DIRS)
vpath %.s $(SRC_DIRS)

# Rule for .c files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo $@

# Rule for .s files
$(OBJ_DIR)/%.o: %.s
	$(CC) $(ASFLAGS) -c -o $@ $<
	@echo $@

# Prepare directories
mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OUT_DIR)

print-%  : ; @echo $* = $($*)

# Clean Target
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

