# Build paths
PROJECT_NAME = $(notdir $(CURDIR))

RUNTIME_IDE_VERSION := 10607
BUILD_ARCH := RP2040

BUILD_CHIP = rp2040
VARIANT := rpipicow
FLASH_LAYOUT := 2097152_0# 2MB, no filesystem

ARDUINO_PICO_ROOT = $(realpath ../..)
CORE_PATH = $(ARDUINO_PICO_ROOT)/cores/$(BUILD_CHIP)
LIB_PATH = $(ARDUINO_PICO_ROOT)/lib/$(BUILD_CHIP)
BOOT2_PATH = $(ARDUINO_PICO_ROOT)/boot2/$(BUILD_CHIP)

# Arduino toolchain paths for macOS
ARDUINO_PATH = $(HOME)/Library/Arduino15
TOOLS_PATH = $(ARDUINO_PATH)/packages/$(BUILD_CHIP)/tools
GCC_PATH = $(wildcard $(TOOLS_PATH)/pqt-gcc/*/bin)

SRC_DIR = src
LIB_DIR = libraries
BUILD_DIR = build

BUILD_LIBPICO=libpico.a
BUILD_LIBPICOW=libipv4.a

# Board variant
VARIANTS_DIR = $(ARDUINO_PICO_ROOT)/variants/$(VARIANT)

# Get just the values, removing any -D prefix
BUILD_USBVID := $(shell grep "$(VARIANT).build.usbvid" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_USBPID := $(shell grep "$(VARIANT).build.usbpid" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_USBPWR := $(shell grep "$(VARIANT).build.usbpwr" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)

BUILD_USB_MANUFACTURER := $(shell grep "$(VARIANT).build.usb_manufacturer" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_USB_PRODUCT := $(shell grep "$(VARIANT).build.usb_product" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)

BUILD_BOARD := $(shell grep "$(VARIANT).build.board" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_F_CPU := $(shell grep "$(VARIANT).build.f_cpu" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_TOOLCHAINOPTS := $(shell grep "$(VARIANT).build.toolchainopts" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_EXTRA_FLAGS := $(shell grep "$(VARIANT).build.extra_flags" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_VARIANT := $(shell grep "$(VARIANT).build.variant" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_VARIANTDEFINES := $(shell grep "$(VARIANT).build.variantdefines" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_FLASH_TOTAL := $(shell grep "$(VARIANT).menu.flash.$(FLASH_LAYOUT).build.flash_total" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)

BUILD_BOOT2 := $(shell grep "$(VARIANT).build.boot2" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)

# Get memory map values
BUILD_FLASH_LENGTH := $(shell grep "$(VARIANT).menu.flash.$(FLASH_LAYOUT).build.flash_length" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_EEPROM_START := $(shell grep "$(VARIANT).menu.flash.$(FLASH_LAYOUT).build.eeprom_start" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_FS_START := $(shell grep "$(VARIANT).menu.flash.$(FLASH_LAYOUT).build.fs_start" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_FS_END := $(shell grep "$(VARIANT).menu.flash.$(FLASH_LAYOUT).build.fs_end" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
UPLOAD_METHOD = default
BUILD_RAM_LENGTH := $(shell grep "$(VARIANT).menu.uploadmethod.$(UPLOAD_METHOD).build.ram_length" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2- | sed 's/k/000/')
BUILD_PSRAM_LENGTH := 0

EXCEPTIONS = Disabled
BUILD_FLAGS_EXCEPTIONS := $(shell grep "$(VARIANT).menu.exceptions.$(EXCEPTIONS).build.flags.exceptions" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)
BUILD_FLAGS_LIBSTDCPP := $(shell grep "$(VARIANT).menu.exceptions.$(EXCEPTIONS).build.flags.libstdcpp" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f2-)

BUILD_LED_PIN := $(shell grep "$(VARIANT).build.led_defines" $(ARDUINO_PICO_ROOT)/boards.txt | cut -d= -f3-)


# Toolchain configuration
TOOLCHAIN_PREFIX := arm-none-eabi-
CC := $(GCC_PATH)/$(TOOLCHAIN_PREFIX)gcc
CXX := $(GCC_PATH)/$(TOOLCHAIN_PREFIX)g++
AR := $(GCC_PATH)/$(TOOLCHAIN_PREFIX)ar
OBJCOPY := $(GCC_PATH)/$(TOOLCHAIN_PREFIX)objcopy
SIZE := $(GCC_PATH)/$(TOOLCHAIN_PREFIX)size
READELF := $(GCC_PATH)/$(TOOLCHAIN_PREFIX)readelf
PYTHON3 := python3
PICOTOOL := $(wildcard $(TOOLS_PATH)/pqt-picotool/*/picotool)

# Common flags
WARNING_FLAGS := -Werror=return-type -Wno-psabi
WARNING_FLAGS_MORE := -Wall -Werror=return-type -Wno-ignored-qualifiers -Wno-psabi
WARNING_FLAGS_ALL := -Wall -Wextra -Werror=return-type -Wno-ignored-qualifiers -Wno-psabi -Wno-unused-parameter -Wno-missing-field-initializers

# Network and PSRAM defines
NET_DEFINES := $(BUILD_LIBPICOWDEFS) -DLWIP_IGMP=1 -DLWIP_CHECKSUM_CTRL_PER_NETIF=1
PSRAM_DEFINES := $(BUILD_PSRAM_CS) $(BUILD_PSRAM_FREQ)

DEFINES := $(BUILD_USBVID) \
          $(BUILD_USBPID) \
          $(BUILD_USBPWR) \
          -DUSB_MANUFACTURER='$(BUILD_USB_MANUFACTURER)' \
          -DUSB_PRODUCT='$(BUILD_USB_PRODUCT)' \
          -DLWIP_IGMP=1 \
          -DLWIP_CHECKSUM_CTRL_PER_NETIF=1 \
          $(BUILD_VARIANTDEFINES) \
          -DARDUINO_VARIANT="$(VARIANT)" \
          -DPICO_FLASH_SIZE_BYTES=$(BUILD_FLASH_TOTAL) \
          $(BUILD_EXTRA_FLAGS) \
          -DF_CPU=$(BUILD_F_CPU) \
          -DARDUINO=$(RUNTIME_IDE_VERSION) \
          -DARDUINO_$(BUILD_BOARD) \
          -DBOARD_NAME="$(BUILD_BOARD)" \
          -DARDUINO_ARCH_$(BUILD_ARCH) \
          $(BUILD_DEBUG_PORT) \
          $(BUILD_DEBUG_LEVEL) \
          -DWIFICC=CYW43_COUNTRY_WORLDWIDE \
          -DUSE_TINYUSB \
          -DENABLE_CLASSIC \
          @$(ARDUINO_PICO_ROOT)/lib/$(BUILD_CHIP)/platform_def.txt

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Base required libraries
LIB_SRCS := $(ARDUINO_PICO_ROOT)/libraries/SdFat/src \
            $(ARDUINO_PICO_ROOT)/libraries/SPI/src \
            $(ARDUINO_PICO_ROOT)/libraries/Wire/src \
            $(ARDUINO_PICO_ROOT)/libraries/rp2040/src \
            $(ARDUINO_PICO_ROOT)/libraries/EEPROM/src \
            $(LIB_DIR)

# Remove any non-existent paths
LIB_SRCS := $(wildcard $(LIB_SRCS))

# Generate include paths
LIB_INCLUDES := $(addprefix -I,$(LIB_SRCS))

# Special handling for TinyUSB
TINYUSB_PATH := $(ARDUINO_PICO_ROOT)/libraries/Adafruit_TinyUSB_Arduino
TINYUSB_C_FILES := $(call rwildcard,$(TINYUSB_PATH)/src,*.c)
TINYUSB_CPP_FILES := $(call rwildcard,$(TINYUSB_PATH)/src,*.cpp)

# Include paths
INCLUDES := -iprefix$(ARDUINO_PICO_ROOT)/ \
           @$(ARDUINO_PICO_ROOT)/lib/$(BUILD_CHIP)/platform_inc.txt \
           @$(ARDUINO_PICO_ROOT)/lib/core_inc.txt \
           -I$(ARDUINO_PICO_ROOT)/include/$(BUILD_CHIP) \
           -I$(CORE_PATH) -I$(VARIANTS_DIR) \
           -I$(CURDIR)/$(SRC_DIR) \
		   -I$(TINYUSB_PATH)/src \
           -I$(TINYUSB_PATH)/src/arduino \
           $(LIB_INCLUDES)

# Core files (excluding sdkoverride)
CORE_C_FILES = $(filter-out $(CORE_PATH)/sdkoverride/%,$(call rwildcard,$(CORE_PATH),*.c))
CORE_CPP_FILES = $(call rwildcard,$(CORE_PATH),*.cpp)

# Source directory files
SRC_C_FILES = $(call rwildcard,$(SRC_DIR),*.c)
SRC_CPP_FILES = $(call rwildcard,$(SRC_DIR),*.cpp)

# Library files
LIB_C_FILES := $(foreach dir,$(LIB_SRCS),$(wildcard $(dir)/*.c)) \
               $(foreach dir,$(LIB_SRCS),$(wildcard $(dir)/*/*.c))

LIB_CPP_FILES := $(foreach dir,$(LIB_SRCS),$(wildcard $(dir)/*.cpp)) \
                 $(foreach dir,$(LIB_SRCS),$(wildcard $(dir)/*/*.cpp))

# Combine all sources
C_SRCS = $(CORE_C_FILES) $(SRC_C_FILES) $(LIB_C_FILES) $(TINYUSB_C_FILES)
CPP_SRCS = $(CORE_CPP_FILES) $(SRC_CPP_FILES) $(LIB_CPP_FILES) $(TINYUSB_CPP_FILES)

# Generate object files
C_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS))
CPP_OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))

# Variant sources
VARIANT_CPP_SRCS = $(wildcard $(VARIANTS_DIR)/*.cpp)
VARIANT_CPP_OBJS = $(patsubst $(VARIANTS_DIR)/%.cpp,$(VARIANTS_DIR)/$(BUILD_DIR)/%.o,$(VARIANT_CPP_SRCS))

# Add variant objects to the list
OBJS = $(CPP_OBJS) $(C_OBJS) $(VARIANT_CPP_OBJS)

# Compiler flags
COMMON_FLAGS := $(BUILD_TOOLCHAINOPTS) -ffunction-sections -fdata-sections $(BUILD_FLAGS_EXCEPTIONS) \
               $(BUILD_FLAGS_STACKPROTECT) $(BUILD_PICODEBUGFLAGS)

# Wrap options from platform
WRAP_FLAGS := @$(LIB_PATH)/platform_wrap.txt \
             @$(ARDUINO_PICO_ROOT)/lib/core_wrap.txt

# C specific flags
CFLAGS := -c $(WARNING_FLAGS) $(DEFINES) $(COMMON_FLAGS) -MMD $(INCLUDES) -std=gnu17 -g -pipe

CXXFLAGS := -c $(WARNING_FLAGS) $(DEFINES) $(COMMON_FLAGS) -MMD $(INCLUDES) $(BUILD_FLAGS_RTTI) -std=gnu++17 -g -pipe

# Linker flags

LDFLAGS := $(WRAP_FLAGS) -Wl,--cref -Wl,--check-sections -Wl,--gc-sections \
          -Wl,--unresolved-symbols=report-all -Wl,--warn-common \
          -Wl,--undefined=runtime_init_install_ram_vector_table \
          -Wl,--undefined=__pre_init_runtime_init_clocks \
          -Wl,--undefined=__pre_init_runtime_init_bootrom_reset \
          -Wl,--undefined=__pre_init_runtime_init_early_resets \
          -Wl,--undefined=__pre_init_runtime_init_usb_power_down \
          -Wl,--undefined=__pre_init_runtime_init_post_clock_resets \
          -Wl,--undefined=__pre_init_runtime_init_spin_locks_reset \
          -Wl,--undefined=__pre_init_runtime_init_boot_locks_reset \
          -Wl,--undefined=__pre_init_runtime_init_bootrom_locking_enable \
          -Wl,--undefined=__pre_init_runtime_init_mutex \
          -Wl,--undefined=__pre_init_runtime_init_default_alarm_pool \
          -Wl,--undefined=__pre_init_runtime_init_per_core_bootrom_reset \
          -Wl,--undefined=__pre_init_runtime_init_per_core_h3_irq_registers \
          -Wl,--undefined=__pre_init_runtime_init_per_core_irq_priorities

# Libraries
LIBS := -lm -lc $(BUILD_FLAGS_LIBSTDCPP)
BEARSSL_LIB := $(LIB_PATH)/libbearssl.a
PICO_LIBS := $(LIB_PATH)/$(BUILD_LIBPICO) \
             $(LIB_PATH)/$(BUILD_LIBPICOW)

# Output formats
UF2_FAMILY ?= $(BUILD_UF2FAMILY)

# Build rules
.PHONY: all clean upload

all: $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT_NAME).uf2 $(BUILD_DIR)/$(PROJECT_NAME).bin.signed upload

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

# Link
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(OBJS) $(BUILD_DIR)/boot2.o $(BUILD_DIR)/memmap_default.ld
	$(CXX) -L$(BUILD_DIR) $(COMMON_FLAGS) $(LDFLAGS) \
	-Wl,--script=$(BUILD_DIR)/memmap_default.ld \
	-Wl,-Map,$(BUILD_DIR)/$(PROJECT_NAME).map \
	-o $@ -Wl,--no-warn-rwx-segments -Wl,--start-group \
	$(OBJS) $(BUILD_DIR)/boot2.o \
	$(LIB_PATH)/ota.o \
	$(PICO_LIBS) $(BEARSSL_LIB) $(LIBS) -Wl,--end-group

	#$(OBJS) $(BUILD_DIR)/core.a $(BUILD_DIR)/boot2.o \

$(BUILD_DIR)/core.a: $(OBJS)
	echo $(AR) rcs $@ $^
	$(AR) rcs $@ $^

upload: $(BUILD_DIR)/$(PROJECT_NAME).uf2
	echo "Uploading: $<"
	$(PICOTOOL) load -f -x $<
	$(PICOTOOL) reboot

# Create UF2
$(BUILD_DIR)/$(PROJECT_NAME).uf2: $(BUILD_DIR)/$(PROJECT_NAME).elf
	$(PICOTOOL) uf2 convert $< $@ $(UF2_FAMILY)

# Create signed binary
$(BUILD_DIR)/$(PROJECT_NAME).bin: $(BUILD_DIR)/$(PROJECT_NAME).elf
	$(OBJCOPY) -Obinary $< $@

$(BUILD_DIR)/$(PROJECT_NAME).bin.signed: $(BUILD_DIR)/$(PROJECT_NAME).bin
	$(PYTHON3) -I $(ARDUINO_PICO_ROOT)/tools/signing.py \
	--mode sign --privatekey $(BUILD_SOURCE_PATH)/private.key \
	--bin $< --out $@

# Compile boot2
$(BUILD_DIR)/boot2.o: $(BOOT2_PATH)/$(BUILD_BOOT2).S
	$(CC) $(COMMON_FLAGS) -c $< \
	-I$(ARDUINO_PICO_ROOT)/include/$(BUILD_CHIP)/hardware_regs \
	-I$(ARDUINO_PICO_ROOT)/include/$(BUILD_CHIP)/pico_binary_info -o $@

$(BUILD_DIR)/memmap_default.ld: $(LIB_PATH)/memmap_default.ld
	$(PYTHON3) -I $(ARDUINO_PICO_ROOT)/tools/simplesub.py \
	--input $< \
	--out $@ \
	--sub __FLASH_LENGTH__ $(BUILD_FLASH_LENGTH) \
	--sub __EEPROM_START__ $(BUILD_EEPROM_START) \
	--sub __FS_START__ $(BUILD_FS_START) \
	--sub __FS_END__ $(BUILD_FS_END) \
	--sub __RAM_LENGTH__ $(BUILD_RAM_LENGTH) \
	--sub __PSRAM_LENGTH__ $(BUILD_PSRAM_LENGTH)

# Debug helper
print-%:
	@echo $* = $($*)
print-flash-debug:
	@echo "Search string: $(VARIANT).menu.flash.$(FLASH_LAYOUT).build.flash_total"
	@echo "Searching in $(ARDUINO_PICO_ROOT)/boards.txt:"
	@grep "$(VARIANT).menu.flash.$(FLASH_LAYOUT)" $(ARDUINO_PICO_ROOT)/boards.txt
clean:
	rm -rf $(BUILD_DIR)
