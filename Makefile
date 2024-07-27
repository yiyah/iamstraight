PROJECT := iamstraight
BUILD_DIR = build

# This must befoe include BSP/Makefile
# use to generate the output file(not use "all")
.PHONY: OUTPUT
OUTPUT: $(BUILD_DIR)/$(PROJECT).elf \
$(BUILD_DIR)/$(PROJECT).hex \
$(BUILD_DIR)/$(PROJECT).bin

include BSP/Makefile

######################################
# redefined the C_SOURCES, OBJECTS, C_INCLUDES, LDSCRIPT
# which defined in BSP/Makefile
######################################
# C sources
BSP_C_SOURCES = $(addprefix BSP/, $(C_SOURCES))
APP_C_SOURCES = \
APP/car.c \
APP/pid.c \
APP/set_params.c \

C_SOURCES := $(BSP_C_SOURCES) $(APP_C_SOURCES)
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))

# ASM sources
BSP_ASM_SOURCES = $(addprefix BSP/, $(ASM_SOURCES))
ASM_SOURCES := $(BSP_ASM_SOURCES)
vpath %.s $(sort $(dir $(ASM_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
OBJECTS := $(sort $(OBJECTS))
# C includes
BSP_C_INCLUDES = $(patsubst -I%,-IBSP/%,$(C_INCLUDES))
APP_C_INCLUDES = -IAPP/include
C_INCLUDES := $(BSP_C_INCLUDES) $(APP_C_INCLUDES)

LDSCRIPT = BSP/STM32F103C8Tx_FLASH.ld
############## redefined done ###############
#############################################

$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

dl: OUTPUT
# openocd -f interface/cmsis-dap.cfg -f target/stm32f1x.cfg -c "transport select swd" -c init -c "reset halt;wait_halt;flash write_image erase $(shell pwd)/build/${PROJECT}.elf" -c reset -c shutdown
	openocd -f interface/cmsis-dap.cfg -f target/stm32f1x.cfg -c "transport select swd" -c init -c "reset halt" -c "wait_halt" -c "flash write_image erase $(shell pwd)/build/${PROJECT}.elf" -c reset -c shutdown
