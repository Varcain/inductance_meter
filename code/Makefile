PROJ_NAME = main

# Set toolchain
TC = /home/limak/x-tools/arm-cortex_m3-eabi/bin/arm-cortex_m3-eabi

# Set STM32 Cube path
STM32CUBE_PATH = /home/limak/Downloads/STM32Cube_FW_F1_V1.2.0

# Output paths
OBJ_DIR		= obj
OUT_DIR		= out

# Set Tools
CC	= $(TC)-gcc
LD	= $(TC)-ld
AR	= $(TC)-ar
OBJCOPY	= $(TC)-objcopy
OBJDUMP	= $(TC)-objdump
SIZE	= $(TC)-size

# Set Dirs
HAL_DIR		= $(STM32CUBE_PATH)/Drivers/STM32F1xx_HAL_Driver/Src
USER_DIR	= src
ASM_DIR		= src

# Set Sources
HAL_SRCS	= $(wildcard $(HAL_DIR)/*.c)
USER_SRCS	= $(wildcard $(USER_DIR)/*.c)
ASM_SRCS	= $(wildcard $(ASM_DIR)/*.s)

# Set Objects
HAL_OBJS	= $(addprefix $(OBJ_DIR)/,$(notdir $(HAL_SRCS:.c=.o)))
USER_OBJS	= $(addprefix $(OBJ_DIR)/,$(notdir $(USER_SRCS:.c=.o)))
ASM_OBJS	= $(addprefix $(OBJ_DIR)/,$(notdir $(ASM_SRCS:.s=.o)))

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
			-Wl,-Map,$(OUT_DIR)/$(PROJ_NAME).map

# Default Target
all: mkdir $(OUT_DIR)/$(PROJ_NAME).hex $(OUT_DIR)/$(PROJ_NAME).lst info

# elf Target
$(OUT_DIR)/$(PROJ_NAME).elf: $(HAL_OBJS) $(USER_OBJS) $(ASM_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo $@

# bin Target
$(OUT_DIR)/$(PROJ_NAME).bin: $(OUT_DIR)/$(PROJ_NAME).elf
	$(OBJCOPY) -O binary $(OUT_DIR)/$(PROJ_NAME).elf $(OUT_DIR)/$(PROJ_NAME).bin
	@echo $@

$(OUT_DIR)/$(PROJ_NAME).hex: $(OUT_DIR)/$(PROJ_NAME).elf
	$(OBJCOPY) -O ihex $(OUT_DIR)/$(PROJ_NAME).elf $(OUT_DIR)/$(PROJ_NAME).hex
	@echo $@

$(OUT_DIR)/$(PROJ_NAME).lst: $(OUT_DIR)/$(PROJ_NAME).elf
	@$(OBJDUMP) -h -S $(OUT_DIR)/$(PROJ_NAME).elf > $(OUT_DIR)/$(PROJ_NAME).lst
	@echo $@

# Display Memory Usage Info
info: $(OUT_DIR)/$(PROJ_NAME).elf
	@$(SIZE) --format=berkeley $(OUT_DIR)/$(PROJ_NAME).elf

# Rule for HAL .c files
$(OBJ_DIR)/%.o: $(HAL_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo $@

# Rule for user .c files
$(OBJ_DIR)/%.o: $(USER_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo $@

# Rule for user .s files
$(OBJ_DIR)/%.o: $(ASM_DIR)/%.s
	$(CC) $(ASFLAGS) -c -o $@ $<
	@echo $@

# Prepare directories
mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OUT_DIR)

# Clean Target
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

