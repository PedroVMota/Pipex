NAME = pipex
COMPILER = cc
CLAGS = -Wall -Wextra -Werror -g 
CINC = -I include/

CFILES = ./src/child.c ./src/data.c ./src/extra.c ./src/helper.c ./src/main.c ./src/parse.c ./src/utls.c
C_OBJS = $(CFILES:.c=.o)


all: $(NAME)

$(NAME): $(C_OBJS)
	@make -C libft/ --no-print
	$(COMPILER) $(CLAGS) $(CINC) $(C_OBJS) libft/libft.a -o $(NAME)

%.o: %.c
	$(COMPILER) $(CLAGS) $(CINC) -c $< -o $@

clean:
	@rm -f $(C_OBJS)
	@make clean -C ./libft --no-print

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft --no-print
re: fclean all


#[submodule "libft"]
#path = libft
#url = git@github.com:PedroVMota/libft.git