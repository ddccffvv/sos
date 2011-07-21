#! /bin/bash
gcc -m32 -o kernel.o -c kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
ld -m elf_i386 -T linker.ld -o kernel.bin loader.o kernel.o
./run.sh 
