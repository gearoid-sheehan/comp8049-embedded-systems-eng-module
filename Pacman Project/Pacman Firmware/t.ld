/****************
qemu with -kernel file.bin ==> start to execute from 0x10000 ==>
file.bin must be loaded to 0x10000 ==> . = 0x10000
************/
ENTRY(reset)
SECTIONS
{
  . = 0x10000;
  .text : { ts.o  }
  .data : { *(.data) }
  .bss : { *(.bss) }
  .data : { panda.o }       /* panda file */
  .data : { pacman.o }     /* porkcar file */
  .data : {pacman_p_up.o}
  .data : {speedy.o}
  .data : {pokey.o}
  .data : {power.o}
  .data : {shadow.o}
  .data : {mur.o}
  .data : {point.o}
  . = ALIGN(8);
  . = . + 0x8000; /* 4kB of SVC stack space */
  svc_stack = .;
  . = . + 0x4000; /* 4kB of IRQ stack space */
  irq_stack = .;
}

