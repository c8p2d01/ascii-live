#OUTPUT NAME
NAME := ascii_loop

# Folders:
BUILD	= ./build
SOURCE	= ./src

# Other Variables:
COMPILER:=	cc
COMPFLAGS:=	-g #-fsanitize=address #-Wall -Werror -Wextra -Wno-unused-variable 

# Source Files:
SRCFILES:=\
			main.c \
			


# ------------------------------------------
# Do not change anything beyond this point!
# ------------------------------------------

# Process Variables
CC:=		$(COMPILER)
CFLAGS:=	$(COMPFLAGS)
SRCS:=		$(addprefix $(SOURCE)/,$(SRCFILES))
OBJS:=		$(SRCS:$(SOURCE)/%.c=$(BUILD)/%.o)
NAME:=		./$(NAME)
OS:=		$(shell uname -s)

.PHONY: all clean fclean re e red clear green

LFT = ./ft_libft
LIBMLX = ./MLX42
LIBRARYS	:= $(LFT)/libft.a
RED = "\033[38;2;255;51;51m"
GRN = "\033[38;2;170;255;170m"
CLEAR = "\033[0m"

ifeq ($(SUBM_STATE),)
SUBM_FLAG	= submodule
else 
SUBM_FLAG	=
endif

all: $(SUBM_FLAG) lib
	make -j $(nproc) $(NAME)

submodule: 
	@git submodule init
	@git submodule update --remote --init --recursive

lib:
	make bonus -C $(LFT)

# Compile .cpp files to .o Files
$(OBJS): $(BUILD)%.o : $(SOURCE)%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# Main Build Rule
$(NAME): $(OBJS)
	@echo "--> Compiling Executable"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARYS)
	./$(NAME) knot

clean:
	@make -s red
	rm -rdf $(BUILD)
	make clean -C $(LFT)
	@make -s clear

fclean:
	@make -s red
	rm -rdf $(NAME)
	rm -rdf $(BUILD)
	make fclean -C $(LFT)
	@make -s clear

re: fclean all

ree: re
	./$(NAME) maps/smol/map.cub

e:
	make
	./$(NAME) maps/smol/map.cub

red:
	echo $(RED)
green:
	echo $(GRN)
clear:
	echo $(CLEAR)

.PHONY: all clean fclean re e red clear green
.SILENT: red clear green
