##
## This file is part of the libopenstm32 project.
##
## Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

BINARY		= blink

# PREFIX		?= arm-none-eabi
PREFIX			?= arm-elf
CC				= $(PREFIX)-gcc
CXX				= $(PREFIX)-g++
LD				= $(PREFIX)-ld
OBJCOPY			= $(PREFIX)-objcopy
OBJDUMP			= $(PREFIX)-objdump
# Uncomment this line if you want to use the installed (not local) library.
# TOOLCHAIN_DIR	= `dirname \`which $(CC)\``/../$(PREFIX)
TOOLCHAIN_DIR	= ../../libopenstm32
CFLAGS			= -O0 -g -Wall -Wextra -I$(TOOLCHAIN_DIR)/include -fno-common \
		  			-mcpu=cortex-m3 -mthumb
LDSCRIPT		= $(BINARY).ld
LDFLAGS         = -L$(TOOLCHAIN_DIR)/lib -T$(LDSCRIPT) -nostartfiles
OBJS			= $(BINARY).o

OPENOCD_BASE	= /opt/local
OPENOCD			= $(OPENOCD_BASE)/bin/openocd
OPENOCD_SCRIPTS	= $(OPENOCD_BASE)/share/openocd/scripts
OPENOCD_FLASHER	= $(OPENOCD_SCRIPTS)/interface/jtagkey.cfg
OPENOCD_BOARD	= $(OPENOCD_SCRIPTS)/target/stm32.cfg

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q := @
NULL := 2>/dev/null
endif

all: images

images: $(BINARY)
	@printf "  OBJCOPY $(BINARY).bin\n"
	$(Q)$(OBJCOPY) -Obinary $(BINARY) $(BINARY).bin
	@printf "  OBJCOPY $(BINARY).hex\n"
	$(Q)$(OBJCOPY) -Oihex $(BINARY) $(BINARY).hex
	@printf "  OBJCOPY $(BINARY).srec\n"
	$(Q)$(OBJCOPY) -Osrec $(BINARY) $(BINARY).srec
	@printf "  OBJDUMP $(BINARY).list\n"
	$(Q)$(OBJDUMP) -S $(BINARY) > $(BINARY).list

$(BINARY): $(OBJS) $(LDSCRIPT)
	@printf "  LD      $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(LD) $(LDFLAGS) -o $(BINARY) $(OBJS) -lopenstm32

%.o: %.c Makefile
	@printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp Makefile
	@printf "  CXX     $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	@printf "  CLEAN   $(subst $(shell pwd)/,,$(OBJS))\n"
	$(Q)rm -f *.o
	@printf "  CLEAN   $(BINARY)\n"
	$(Q)rm -f $(BINARY)
	@printf "  CLEAN   $(BINARY).bin\n"
	$(Q)rm -f $(BINARY).bin
	@printf "  CLEAN   $(BINARY).hex\n"
	$(Q)rm -f $(BINARY).hex
	@printf "  CLEAN   $(BINARY).srec\n"
	$(Q)rm -f $(BINARY).srec
	@printf "  CLEAN   $(BINARY).list\n"
	$(Q)rm -f $(BINARY).list

flash: images
	@printf "  FLASH   $(BINARY).bin\n"
	@# IMPORTANT: Don't use "resume", only "reset" will work correctly!
	$(Q)$(OPENOCD) -s $(OPENOCD_SCRIPTS) \
		       -f $(OPENOCD_FLASHER) \
		       -f $(OPENOCD_BOARD) \
		       -c "init" -c "reset halt" \
		       -c "flash write_image erase $(BINARY).hex" \
		       -c "reset" \
		       -c "shutdown" $(NULL)

.PHONY: images clean

