/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define COLOR_GRAY				9
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

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_maps
{
	unsigned char	*v_map;
	unsigned char	*c_map;
	unsigned char	*c_cycle;
}					t_maps;

typedef struct		s_proc
{
	int				pc;
	unsigned int	carry;
	int				bot_id;
	unsigned int	reg[REG_NUMBER + 1];
	unsigned int	live;
	unsigned int	last_live;
	unsigned char	code;
	unsigned int	cycles;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_op
{
	unsigned char	code;
	int				nb_params;
	char			type[3];
	unsigned int	cycles;
	int				label;
}					t_op;

typedef struct		s_bot
{
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned int	size;
	unsigned char	code[CHAMP_MAX_SIZE + 1];
	unsigned int	id;
	unsigned int	last_life;
	unsigned int	live;
}					t_bot;

typedef struct		s_flag
{
	int				d;
	int				v;
}					t_flag;

typedef struct		s_core
{
	t_maps			maps;
	t_proc			*proc;
	t_bot			*bots;
	int				cycle;
	t_flag			flag;
	int				bots_count;
	int				cycle_to_die;
	int				new_reset;
	unsigned int	decycle;
	unsigned int	checks;
	int				info_row;
}					t_core;

typedef struct		s_var
{
	unsigned int	speed;
	char			pause;
	char			s;
	char			end;
}					t_var;

typedef void		(*t_vm_func)(t_core *core, t_proc *proc);

t_op				g_op_tab[17];

#endif
