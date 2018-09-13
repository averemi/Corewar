/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtomchys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 16:53:16 by dtomchys          #+#    #+#             */
/*   Updated: 2018/07/03 16:53:17 by dtomchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <stdlib.h>
# include "includes/libft/libft.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define ST(x) ((s[x] == ' ' || s[x] == '\t'))

int						g_fd;
int						g_label;
int						g_file;

typedef enum			e_type
{
	NONE = 0, NAME, COMMENT, COMMAND
}						t_type;

typedef struct			s_label
{
	char				*name;
	struct s_label		*next;
}						t_label;

typedef struct			s_args
{
	int					type_arg;
	char				*val;
	int					value;
	size_t				arg_size;
	struct s_args		*next;
}						t_args;

typedef struct			s_parser
{
	char				*line;
	int					op;
	t_type				type;
	int					codage;
	int					par;

	t_label				*label;
	t_args				*args;
	struct s_parser		*next;
	size_t				size;
}						t_parser;

int						ft_get_info(t_parser *par, char **line);
t_parser				*ft_new_par();
int						ft_get_name_com(char *line, t_parser *par, int *i);
int						ft_find_end(int i, char *s);
int						ft_get_command(char *s, t_parser **par);
t_label					*ft_new_label(t_label **head, char *s, int len);
t_args					*ft_new_arg\
(t_args **head, char *val, int value, int type);
int						ft_parse_command(char *s, t_parser *par);

int						ft_check_label(char *s, t_parser *par);
int						ft_validate_label(char *s, int len, int j);

int						ft_parse_command(char *s, t_parser *par);
int						ft_validate_ind(int num, t_parser *par, char *s);
int						ft_validate_dir(int num, t_parser *par, char *s);
int						ft_validate_reg(int num, t_parser *par, char *s);

int						ft_count_labels(t_parser *head);
void					ft_count_codage(t_parser *par);
void					ft_get_param_size(t_parser *par);

void					ft_set_name_com(int fd, int op, t_parser *par);
void					ft_set_len(int fd, unsigned int len);
void					ft_set_exec(int fd, t_parser *par);
void					ft_translation(int fd, t_parser *par);
int						ft_len_exec(t_parser *par);
unsigned int			reverse_bits(int num, int bytes, int sign);

int						ft_error(int i);
int						ft_check_under(int num, int op);

#endif
