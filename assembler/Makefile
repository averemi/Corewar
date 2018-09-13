	#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/27 12:46:46 by dtomchys          #+#    #+#              #
#    Updated: 2018/03/27 12:46:48 by dtomchys         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = asm
CC = gcc -Wall -Werror -Wextra -g3
RM = rm -f
HD = asm.h
MFLIB = ./includes/libft
SRC = main.c ft_get_info.c ./tools/ft_tools.c ./parser/parse_name_comment.c\
./parser/ft_get_command.c ./parser/parse_label.c ./parser/parse_command.c\
./tools/validate_param.c ./calculation/count_codage.c\
./calculation/count_param_size.c ./calculation/count_labels.c\
./translation/translate_name_comment.c ./translation/translate_exe.c\
./translation/translate_len.c ./translation/translation_tool.c ft_error.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

OBJ: $(SRC) $(HD)
	$(CC) $(SRC) $(HD) -c

$(NAME):  $(OBJ) $(HD)
	make -C $(MFLIB)
	$(CC) -o $(NAME) $(OBJ) -I.$(HD) includes/libft/libft.a

clean:
	make clean -C $(MFLIB)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) libft.a

re: fclean all

.PHONY: clean fclean
