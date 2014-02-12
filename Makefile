SRCS_DIR		=	src/
OBJS_DIR		=	obj/
BIN_DIR			=	bin/


NAME_KERNEL		=	qrthurOS
SRCS_KERNEL		=	kernel/kernel.c		\
					lib/screen.c		\
					lib/memcpy.c		\
					kernel/gdt.c		\
					int/idt.c			\
					int/isr.c			\
					int/pic.c			\
					int/kbmap.c			\
					
OBJS_KERNEL		=	$(addprefix $(OBJS_DIR), $(SRCS_KERNEL:.c=.o))

SRCS_ASM		=	int/interrupts_routine.asm

OBJS_ASM		=	$(addprefix $(OBJS_DIR), $(SRCS_ASM:.asm=.o))


NAME_BOOT		=	bootsector
SRCS_BOOT		=	bootsector/bootsect.asm

FLOPPY			=	floppyA

LOGS			=	bochsout.log			\
					parport.out

CC				=	crossgcc
LD				=	crossld
CFLAGS			=	-Iinclude/

NASM			=	nasm -f bin

RM				=	rm -rf

ECHO			=	echo -e

all:				$(NAME_KERNEL)

$(NAME_KERNEL):		$(OBJS_ASM) $(OBJS_KERNEL)
					@mkdir -p $(BIN_DIR)
					$(LD) --oformat binary -Ttext 1000 $(OBJS_KERNEL) $(OBJS_ASM) -o $(BIN_DIR)$(NAME_KERNEL)
					@$(ECHO) '\033[0;90m> Kernel compiled\n\33[0m'

					$(NASM) $(SRCS_DIR)$(SRCS_BOOT) -o $(BIN_DIR)$(NAME_BOOT)
					@$(ECHO) '\033[0;90m> Boot sector compiled\n\33[0m'

					cat $(BIN_DIR)$(NAME_BOOT) $(BIN_DIR)$(NAME_KERNEL) /dev/zero | \
dd of=$(BIN_DIR)$(FLOPPY) bs=512 count=2880
					@$(ECHO) '\033[0;90m> OS written on $(FLOPPY)\33[0m'


clean:
					$(RM) $(OBJS_DIR)
					$(RM) $(LOGS)
					@$(ECHO) '\033[0;90m> Object files & logs cleaned\033[0m'

fclean:				clean
					$(RM) $(BIN_DIR)
					@$(ECHO) '\033[0;90m> Executables deleted\033[0m'

re:					fclean all


$(OBJS_DIR)%.o:		$(SRCS_DIR)%.asm
					@mkdir -p $(OBJS_DIR)kernel
					@mkdir -p $(OBJS_DIR)int
					@mkdir -p $(OBJS_DIR)lib
					nasm -f elf $^ -o $@

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c
					@mkdir -p $(OBJS_DIR)kernel
					@mkdir -p $(OBJS_DIR)int
					@mkdir -p $(OBJS_DIR)lib
					$(CC) $(CFLAGS) -c $^ -o $@

.PHONY:		all clean fclean re
