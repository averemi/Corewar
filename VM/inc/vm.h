/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfil <vfil@student.unit.ua>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:03:34 by vfil              #+#    #+#             */
/*   Updated: 2018/07/26 15:03:46 by vfil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "../libft/libft.h"
# include <ncurses.h>

# define FIELD_HEIGHT	10
# define FIELD_LENGTH	10
# define FIELD_START_Y	0
# define FIELD_START_X	0
# define T_REG_VALUE	1
# define T_REG_NUMBER	0

# define IDX(x)			((x) % (IDX_MOD))
# define MEM(x)			((x) % (MEM_SIZE))
# define REG(x)			((x) % (REG_NUMBER + 1))

typedef WINDOW		t_wind;

t_bot				parse_bot(char *bot_name);
t_bot				*get_bots(int argc, char **argv, unsigned int size);
unsigned int		swap_4bits(unsigned char *buf);
short				swap_2bits(unsigned char *buf);
void				ft_exit(char *str);
void				run(t_core core, t_vm_func *vm_func);
WINDOW				*init();
void				get_map(t_bot *bots, unsigned int amount, t_maps *maps);
void				init_proceses(t_bot *bots, unsigned int bots_count, \
								t_core *core);
void				print_map(t_core *core, unsigned int speed, \
								WINDOW	*wnd, unsigned int pause);
void				add_proc(t_proc **alst, t_proc *new);
int					cmd_id(unsigned char cmd);
void				vm_live(t_core *core, t_proc *proc);
void				vm_ld(t_core *core, t_proc *proc);
void				vm_st(t_core *core, t_proc *proc);
void				vm_add(t_core *core, t_proc *proc);
void				vm_sub(t_core *core, t_proc *proc);
void				vm_and(t_core *core, t_proc *proc);
void				vm_or(t_core *core, t_proc *proc);
void				vm_xor(t_core *core, t_proc *proc);
void				vm_zjmp(t_core *core, t_proc *proc);
void				vm_ldi(t_core *core, t_proc *proc);
void				vm_sti(t_core *core, t_proc *proc);
void				vm_fork(t_core *core, t_proc *proc);
void				vm_lld(t_core *core, t_proc *proc);
void				vm_lldi(t_core *core, t_proc *proc);
void				vm_lfork(t_core *core, t_proc *proc);
void				vm_aff(t_core *core, t_proc *proc);
void				vm_undef(t_core *core, t_proc *proc);

void				get_op_tab(t_op *op_tab2);
void				get_vm_func(t_vm_func *func2);
unsigned int		skip(int label, unsigned char cdg);
unsigned int		get_tdir(int label, t_core *core, int pc);
unsigned int		*get_args(t_core *core, t_proc *curr_proc, char t_reg);
void				put_on_map(t_core *core, int pc, \
								unsigned int value, unsigned int id);
void				move_proc(t_core *core, t_proc *curr_proc);
unsigned char		*get_codage(unsigned char value);
t_proc				*proc_copy(t_proc *curr_proc, unsigned char *map, \
								unsigned int position);
void				check_life(t_core *core);
unsigned int		count_proc(t_proc *proc);
void				reset_lives(t_core *core);
void				print_bots(t_core *core);
void				print_info(unsigned int speed, t_core *core, \
								unsigned int pause);
void				print_winner(t_core *core);
void				dump_winner(t_core *core);
char				check_codage(t_core *core, t_proc *curr_proc);
void				print_end(t_core *core, unsigned int speed, \
								WINDOW	*wnd, unsigned int pause);
unsigned int		mod(long long value);
void				del_proc(t_core *core);
int					find_winner(t_core *core);

#endif
