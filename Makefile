APP = pipex
CC = cc -g -Wall -Wextra -Werror -I include/ #-fsanitize=address

FILES = ./src/extra.c ./src/parse.c ./src/child_process.c ./src/setting_data.c ./src/main.c ./src/utils_2.c ./src/helper_functions.c
OBJECT = $(FILES:.c=.o)

FILES_FOR_BONUS = ./bonus/extra.c ./bonus/parse.c ./bonus/child_process.c ./bonus/setting_data.c ./bonus/main_bonus.c ./bonus/utils_2.c ./bonus/helper_functions.c
OBJECT_FOR_BONUS = $(FILES_FOR_BONUS:.c=.o)


# Regular text colors
BLK = \e[0;30m
RED = \e[0;31m
GRN = \e[0;32m
YEL = \e[0;33m
BLU = \e[0;34m
MAG = \e[0;35m
CYN = \e[0;36m
WHT = \e[0;37m

# Bold text colors
BBLK = \e[1;30m
BRED = \e[1;31m
BGRN = \e[1;32m
BYEL = \e[1;33m
BBLU = \e[1;34m
BMAG = \e[1;35m
BCYN = \e[1;36m
BWHT = \e[1;37m

# Underline text colors
UBLK = \e[4;30m
URED = \e[4;31m
UGRN = \e[4;32m
UYEL = \e[4;33m
UBLU = \e[4;34m
UMAG = \e[4;35m
UCYN = \e[4;36m
UWHT = \e[4;37m

# Regular background colors
BLKB = \e[40m
REDB = \e[41m
GRNB = \e[42m
YELB = \e[43m
BLUB = \e[44m
MAGB = \e[45m
CYNB = \e[46m
WHTB = \e[47m

# High intensity background colors
BLKHB = \e[0;100m
REDHB = \e[0;101m
GRNHB = \e[0;102m
YELHB = \e[0;103m
BLUHB = \e[0;104m
MAGHB = \e[0;105m
CYNHB = \e[0;106m
WHTHB = \e[0;107m

# High intensity text colors
HBLK = \e[0;90m
HRED = \e[0;91m
HGRN = \e[0;92m
HYEL = \e[0;93m
HBLU = \e[0;94m
HMAG = \e[0;95m
HCYN = \e[0;96m
HWHT = \e[0;97m

# Bold high intensity text colors
BHBLK = \e[1;90m
BHRED = \e[1;91m
BHGRN = \e[1;92m
BHYEL = \e[1;93m
BHBLU = \e[1;94m
BHMAG = \e[1;95m
BHCYN = \e[1;96m
BHWHT = \e[1;97m

# Reset color
RESET = \e[0m
CRESET = \e[0m
COLOR_RESET = \e[0m

all: $(APP)
	clear
	@printf "\n $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\n"
	@printf " $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\n"
	@printf " $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\tWindows Pro N\n"
	@printf " $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\n"
	@printf "\n"
	@printf " $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\n"
	@printf " $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\n"
	@printf " $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\n"
	@printf " $(BLUHB)         $(RESET)"
	@printf "  "
	@printf " $(BLUHB)         $(RESET)\n\n"



$(APP): $(OBJECT)
	make -C ./libft
	$(CC) $(CFLAGS)  $(OBJECT)  ./libft/libft.a -o $(APP)

bonus: $(OBJECT_FOR_BONUS)
	make -C ./libft
	$(CC) $(CFLAGS) ./libft/libft.a $(OBJECT_FOR_BONUS) -o $(APP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./libft
	rm -f $(OBJECT) $(OBJECT_FOR_BONUS)

fclean: clean
	make fclean -C ./libft
	rm -f $(APP)

re: fclean all