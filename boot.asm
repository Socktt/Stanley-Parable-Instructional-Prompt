[org 0x7c00]

BPB:
    jmp BPB_End
BPB_OEM:                    db "StanleyOS"
BPB_BytesPerSector:         dw 512
BPB_SectorsPerCluster:      db 1
BPB_ReservedSectors:        dw 1
BPB_NumberOfFAT:            db 2
BPB_DirectoryEntries:       dw 1
BPB_Sectors:                dw 1000
BPB_MediaDescriptorType:    db 0xF0
BPB_SectorsPerFAT:          dw 5
BPB_SectorsPerTrack:        dw 18
BPB_HeadsOnMedia:           dw 2
BPB_HiddenSectors:          dd 0
BPB_LargeSectorCount:       dd 0

EBPB:
EBPB_DriveNumber:           db 0x00
EBPB_NTFlags:               db 0
EBPB_Signature:             db 0x28
EBPB_VolumeID:              dd 0x69420
EBPB_VolumeLabelString:     db "StanleyOS  "
EBPB_SystemIDString:        db "FAT12   "

BPB_End:

KERNEL_LOCATION equ 0x1000

mov [BOOT_DISK], dl


retryLoad:
mov ah, 0
mov al, 0x3
int 0x10

mov ah, 0
mov al, [BOOT_DISK]
int 0x13

mov ah, 2
mov al, 40
mov ch, 0
mov cl, 2
mov dh, 0
mov dl, [BOOT_DISK]
mov bx, 0
mov es, bx
mov bx, KERNEL_LOCATION

int 0x13
jc diskReadErr

cli

in al, 0x92
or al, 2
out 0x92, al

lgdt [GDT_Descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:start_protected_mode

sti
mov ah, 0x0e
mov al, "3"
int 0x10
mov al, "2"
int 0x10
mov al, "E"
int 0x10

hlt

jmp $

%include "gdt.asm"

diskReadErr:
    mov ah, 0x0e
    mov al, "D"
    int 0x10
    mov al, "i"
    int 0x10
    mov al, "s"
    int 0x10
    mov al, "k"
    int 0x10
    jmp retryLoad

BOOT_DISK: db 0

[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    jmp KERNEL_LOCATION

times 510-($-$$) db 0
db 0x55, 0xaa