### 1. Instalation
    $ sudo port install arm-elf-gcc
    $ sudo port install openocd
    
### 2. Symlink gcc binaries
    $ sudo ln -s /opt/local/bin/arm-elf-gcc-4.5.0 /opt/local/bin/arm-elf-gcc
    $ sudo ln -s /opt/local/bin/arm-elf-g++-4.3.2 /opt/local/bin/arm-elf-g++

### 3. Edit '/opt/local/share/openocd/scripts/target/stm32.cfg' (line 20)
Change
    set  _WORKAREASIZE 0x4000
to
    set  _WORKAREASIZE 0x4200

### 4. Compile
    make

### 5. Run openocd
    $ openocd -f interface/jtagkey.cfg -f target/stm32.cfg
        
### 6. Run telnet
    $ telnet localhost 4444
    
### 7. Write flash (inside telnet)
    > reset halt
    > stm32x mass_erase 0
    > flash probe 0
    > flash write_bank 0 /path/to/project/out/blink.bin 0
    > reset run
    
### 8. (Optional) debugger (using gdb)
    $ gdb
    (gdb) target remote localhost:3333
E.g. read GPIOB ODR register
    (gdb) x/x 0x40010c0c
    