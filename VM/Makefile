# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchechai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 11:14:54 by vchechai          #+#    #+#              #
#    Updated: 2017/11/09 11:22:54 by vchechai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	corewar

MAKE	=	@make

FILES   =   create_bots.c data_manip.c ft_exit.c get_arg.c manage_life.c mod.c \
            parse_bot.c print_map.c vm_func_1.c vm_func_3.c create_proceses.c \
            end_game.c game.c get_window.c maps_manip.c op_tab.c print_info.c \
            swap_bites.c vm_func_2.c vm_func_4.c

SRC 	=	$(addprefix src/, $(FILES))

FLAGS	=	-Wall -Wextra -Werror

.PHONY: all clean fclean re
all: $(NAME)

$(NAME): $(SRC) main.c
		@make -C libft
		gcc $(FLAGS) main.c $(SRC) -lncurses -L libft -lftprintf -o $(NAME)

clean:
	$(MAKE) clean -C libft
	@rm -f *.o

fclean: clean
	$(MAKE) fclean -C libft
	@rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
