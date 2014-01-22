SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/
BIN_DIR			=	bin/


NAME_KERNEL		=	qrthurOS
SRCS_KERNEL		=	qrthurOS/kernel.c		\
					qrthurOS/screens_cc.c
OBJS_KERNEL		=	$(addprefix $(OBJS_DIR), $(SRCS_KERNEL:.c=.o))


NAME_BOOT		=	bootsector
SRCS_BOOT		=	bootsector/bootsect.asm

FLOPPY			=	floppyA

CC				=	gcc
CFLAGS			=	-Iincludes/

NASM			=	nasm -f bin

RM				=	rm -rf

all:				$(NAME_KERNEL)

$(NAME_KERNEL):		$(OBJS_KERNEL)
					ld --oformat binary -Ttext 1000 $(OBJS_KERNEL) -o $(BIN_DIR)$(NAME_KERNEL)
					$(NASM) $(SRCS_DIR)$(SRCS_BOOT) -o $(BIN_DIR)$(NAME_BOOT)
					cat $(BIN_DIR)$(NAME_BOOT) $(BIN_DIR)$(NAME_KERNEL) /dev/zero | \
dd of=$(BIN_DIR)$(FLOPPY) bs=512 count=2880


#cat bin/bootsect kernel /dev/zero | dd of=bin/floppyA bs=512 count=2880

clean:
					$(RM) $(OBJS_DIR)

fclean:				clean
					$(RM) $(BIN_DIR)

re:					fclean all

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c
					@mkdir -p $(OBJS_DIR)$(NAME_KERNEL)
					@mkdir -p $(BIN_DIR)
					$(CC) $(CFLAGS) -c $^ -o $@

.PHONY:		all clean fclean re
