# Object files
OBJS = kernel_entry.o kernel.o gdt.o idt.o isr.o isrc.o irq.o irqc.o tss.o timer.o kb.o port_io.o vga.o system.o prompt.o
# Files to remove during clean
REMOVABLE = kernel_entry.o kernel.o gdt.o idt.o isr.o isrc.o irq.o irqc.o tss.o timer.o kb.o port_io.o vga.o system.o prompt.o full_kernel.bin empty_end.bin instructionalPrompt.bin boot.bin
# Source Files
SRC_FILES = kernel.c gdt.c idt.c isr.c irq.c kb.c port_io.c vga.c system.c boot.asm empty_end.asm isr.asm irq.asm prompt.c tss.c
# Compiler options
COMPILER_OPTIONS = -ffreestanding -m32 -g -c -w
# Linker options
LINKER_OPTIONS = -Ttext 0x1000 --oformat binary

all: $(SRC_FILES)
	nasm -f bin boot.asm -o boot.bin
	nasm -f bin empty_end.asm -o empty_end.bin
	nasm -f elf kernel_entry.asm -o kernel_entry.o
	nasm -f elf isr.asm -o isr.o
	nasm -f elf irq.asm -o irq.o
	i686-elf-gcc $(COMPILER_OPTIONS) "kernel.c" -o "kernel.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "gdt.c" -o "gdt.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "idt.c" -o "idt.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "isr.c" -o "isrc.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "irq.c" -o "irqc.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "tss.c" -o "tss.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "timer.c" -o "timer.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "kb.c" -o "kb.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "port_io.c" -o "port_io.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "vga.c" -o "vga.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "system.c" -o "system.o"
	i686-elf-gcc $(COMPILER_OPTIONS) "prompt.c" -o "prompt.o"
	i686-elf-ld -o "full_kernel.bin" $(OBJS) $(LINKER_OPTIONS)
	cat "boot.bin" "full_kernel.bin" "empty_end.bin" > "instructionalPrompt.bin"
	qemu-system-x86_64 instructionalPrompt.bin
	# bochs -f bochs.cfg

clean: $(REMOVABLE)
	rm $(REMOVABLE)
