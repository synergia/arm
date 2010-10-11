### 1. Instalation
    $ sudo port install arm-elf-gcc
    $ sudo port install openocd
    $ git clone git://libopenstm32.git.sourceforge.net/gitroot/libopenstm32/libopenstm32 
    
### 2. Symlink gcc binaries
    $ sudo ln -s /opt/local/bin/arm-elf-gcc-4.5.0 /opt/local/bin/arm-elf-gcc
    $ sudo ln -s /opt/local/bin/arm-elf-g++-4.3.2 /opt/local/bin/arm-elf-g++

### 3. Edit '/opt/local/share/openocd/scripts/target/stm32.cfg' (line 20)
Change
    set  _WORKAREASIZE 0x4000
to
    set  _WORKAREASIZE 0x4200

### 4. Edit Makefile
Change TOOLCHAIN_DIR and OPENOCD_BASE

### 5. Compile
    $ make

### 6. Run openocd
    $ make flash
    
### 7. (Optional) debugger (using gdb)
    $ gdb
    (gdb) target remote localhost:3333
E.g. read GPIOB ODR register
    (gdb) x/x 0x40010c0c
