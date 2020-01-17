/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:01:23 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 17:18:41 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/stat.h>
# include <setjmp.h>
# include <fcntl.h>
# include <termios.h>
# include <stdbool.h>
# include <semaphore.h>
# include <time.h>
# include "../readline/readline.h"
# include "readline/history.h"
# include "../libft/libft.h"
# define RED		"\x1B[31m"
# define GRN		"\x1B[32m"
# define YEL		"\x1B[33m"
# define BLU		"\x1B[34m"
# define MAG		"\x1B[35m"
# define CYN		"\x1B[1;36m"
# define WHT		"\x1B[37m"
# define BRO		"\x1B[32;31m"
# define BCN		"\x1B[34;46m"
# define BOR		"\x1B[30;41m"
# define BOC		"\x1B[30;46m"
# define BGR		"\x1B[30;42m"
# define BBR		"\x1B[30;42;41m"
# define BLBR		"\x1B[34;43m"
# define RESET		"\x1B[0m"
# define LESS		"<"
# define DLESS		"<<"
# define TLESS		"<<<"
# define LESSAND 	"<&"
# define GREAT		">"
# define DGREAT		">>"
# define GREATAND	">&"
# define CLOBBER	">|"
# define LESSGREAT	"<>"
# define UPR0		"0      abtnvfr            e"
# define BIN_TEST_UN_OPTIONS "bcdefghLnprSstuwxz"
# define BIN_TEST_ERR_BIN ": binary operator expected: "
# define BIN_TEST_ERR_UN ": unary operator expected: "
# define BIN_TEST_ERR_TM ": too many argumanets"
# define BIN_TEST_ERR_INT ": integer expression expected: "
# define BIN_TEST_BLOCK (1)
# define BIN_TEST_CHAR (1 << 1)
# define BIN_TEST_DIR (1 << 2)
# define BIN_TEST_EXIST (1 << 3)
# define BIN_TEST_FILE (1 << 4)
# define BIN_TEST_GID (1 << 5)
# define BIN_TEST_SLNK_H (1 << 6)
# define BIN_TEST_SLNK_L (1 << 7)
# define BIN_TEST_STR_NZERO (1 << 8)
# define BIN_TEST_FIFO (1 << 9)
# define BIN_TEST_READ (1 << 10)
# define BIN_TEST_SOCKET (1 << 11)
# define BIN_TEST_SIZE_NZERO (1 << 12)
# define BIN_TEST_FD (1 << 13)
# define BIN_TEST_UID (1 << 14)
# define BIN_TEST_WRITE (1 << 15)
# define BIN_TEST_EXEC (1 << 16)
# define BIN_TEST_STR_ZERO (1 << 17)
# define BIN_TEST_STR_EQU (1 << 18)
# define BIN_TEST_STR_NEQU (1 << 19)
# define BIN_TEST_INT_EQU (1 << 20)
# define BIN_TEST_INT_NEQU (1 << 21)
# define BIN_TEST_INT_GT (1 << 22)
# define BIN_TEST_INT_GE (1 << 23)
# define BIN_TEST_INT_LT (1 << 24)
# define BIN_TEST_INT_LE (1 << 25)

typedef struct stat		t_stat;

typedef struct			s_proc
{
	struct s_proc		*next;
	char				**argv;
	pid_t				pid;
	pid_t				pgid;
	char				completed;
	char				stopped;
	int					status;
}						t_proc;

typedef struct			s_listf
{
	char				*path;
	char				*file;
	unsigned int		hash;
	struct s_listf		*next;
}						t_listf;

typedef struct			s_listh
{
	char				*path;
	char				*file;
	unsigned int		hash;
	int					hashcount;
	struct s_listh		*next;
}						t_listh;

typedef struct			s_env
{
	char				**env;
	t_listf				*first_list;
	t_listh				*hash_first;
}						t_env;

typedef struct			s_job
{
	char				*orig_cmd;
	char				*stat_job;
	int					num;
	int					ind;
	char				flag;
	pid_t				pgid;
	int					ready;
	struct termios		j_tmod;
	t_proc				*first_proc;
	int					in;
	int					out;
	int					err;
	struct s_job		*next;
}						t_job;

typedef struct			s_cmdlist
{
	int					nr;
	char				**avcmd;
	char				*find_path;
	int					built_in;
	int					fd_pipe_in[2];
	int					fd_pipe_out[2];
	sem_t				*sem_0;
	sem_t				*sem_1;
	int					fd0;
	int					fd1;
	int					fd2;
	pid_t				pid;
	pid_t				pid_z;
	char				*here;
	char				**locals;
	int					flag_not;
	int					andor;
	int					child_pid;
	char				*original;
	int					status;
	char				*sem_name;
	sem_t				*semafor;
	char				*bsem_name;
	sem_t				*bsemafor;
	struct s_cmdlist	*next;
}						t_cmdlist;
typedef struct			s_pipe
{
	t_cmdlist			*first_cmd;
	t_cmdlist			*last_cmd;
	t_cmdlist			*cur_cmd;
}						t_pipe;

t_env					*g_envi;
char					*g_app_name;
char					*g_app_full_name;
pid_t					g_pidchild;
int						g_level;
int						g_check;
int						g_color;
int						g_signal;
char					**g_shell;
int						g_and_or;
int						g_not;
int						g_skip;
int						g_rc;
int						g_built_rc;
int						g_subs_rc;
t_job					*g_job_first;
t_job					*g_job_last;
int						g_job;
char					*g_job_start;
int						g_job_end;
pid_t					g_parent_pid;
int						g_subshell;
int						g_and_or_line;
t_pipe					*g_pipe;
int						g_flpi;
pid_t					g_pgid;
struct termios			g_tmodes;
int						g_terminal;
int						g_is_interactive;
int						g_job_ind;
int						g_std_in;
int						g_std_out;
int						g_stderr;
int						g_redir_block;
char					*g_sub_str;
sem_t					*g_semafor;
char					*g_sem_name;
sem_t					*g_bsemafor;
char					*g_bsem_name;
int						g_subs_counter;
int						g_calc;
int						g_subst;
int						g_shell_num;
int						g_sem_fl;
int						g_bsem_fl;
int						g_pr_wait;
int						g_nopipe_start;

typedef struct dirent	t_dir;

typedef struct			s_cmd
{
	char				**cmd_list;
	jmp_buf				ebuf;
	int					jmp_code;
	jmp_buf				ebuf2;
	int					jmp_code2;
	int					stdin_copy;
	int					stdout_copy;
	int					stderr_copy;
}						t_cmd;
t_cmd					*g_cmd;

typedef struct			s_pipeflag
{
	int					flag;
	int					qflag;
	int					br_count;
	int					br_flag;
	int					start;
	int					count;
	int					i;
	int					flsub;
	int					b_sl;
}						t_pipeflag;
typedef struct			s_greatflag
{
	int					j;
	char				*ind;
	char				*file_redir;
	int					pref_fd;
	int					out_fd;
	int					flag_add;
	int					flag_all;
}						t_greatflag;

typedef struct			s_quoteflag
{
	int					i;
	int					qflag;
	int					br_count;
	int					br_flag;
	int					start;
	int					end;
	int					b_sl;
	int					n;
	int					rc;
	int					wcount;
	int					flsub;
	int					subs_start;
	int					subs_end;
	int					i_cmd;
}						t_quoteflag;

void					exit_shell();
int						ft_calc_matr_rows(char **in);
char					**ft_free_char_matr(char **matrix);
char					**ft_dup_char_matr(char **in);
int						ft_get_ind_env(char *s, char **shell);
t_listf					*ft_create_exe_list();
t_listf					*ft_add_exe_list(char *paths, int lpath,
						t_listf *first_list);
t_listf					*ft_add_file(t_listf *first_list, char *full);
void					ft_merge_sort(t_listf **headref);
char					*rl_gets(char *str);
char					*commands_generator(const char *text, int state);
char					**commands_completion(const char *text, int start,
						int end);
void					ft_parse_line(char *str);
int						ft_parse_cmd(char *str, int len);
void					ft_do_cmd_shell(char **av, int start, int flagpipe);
char					*ft_get_file_path(char *path, t_listf *first_list);
int						ft_built_in(char *path, char **av, char **locals);
void					ft_signal_handler(int signo);
void					ft_signal_handler_rl(int signo);
void					ft_main_signal_handler(int signo, char *line_read);
int						ft_built_cd(char **av, char **locals);
void					ft_cd(char *path, int flag, char **locals);
char					*ft_get_env(char *parm);
char					**ft_set_shell(char *parm, char *value);
int						ft_unset_env(char **parm);
void					ft_echo_parm(char *s, int flag, int len);
int						ft_echo(char **av);
int						ft_tst_home(char *s, int len);
int						ft_tst_env(char *s, int j);
char					*ft_get_home(char *s, int len);
char					*ft_get_my_home(void);
void					ft_get_cmd_matr(t_listf *lst);
void					ft_free_list(void);
void					ft_reset_cmd_list(void);
int						ft_check_file(char *find_path, int type);
int						ft_check_dir(char *find_path);
int						ft_is_dir(char *path);
int						ft_print_msg(char *s, char *name);
void					ft_del_quotes(char **args);
int						ft_len_list(t_listf	*lst);
char					*ft_set_dirpath(int lpath, char *paths);
char					*ft_set_full_exe(char *d_name, char *path, char *full);
char					*ft_alloc_char(int l);
char					*ft_tilda_path(char *path);
int						ft_print_env(void);
int						ft_tst_tilda(char *s, int j);
char					*ft_get_usr_tilda(char *path);
int						ft_tst_end_til(char *s, int j, int *flag);
void					ft_putstrf(char *s);
void					ft_final_free(void);
char					*ft_get_file(char *path);
char					**ft_split_pipes(char *cmd);
int						ft_get_count_in_pipe(char **av, int start);
char					**ft_get_pipe_av(char **av, int start);
int						ft_test_pipe(char **av, int start);
int						ft_test_built_in(char *path);
t_cmdlist				*ft_free_cmd_list(t_cmdlist *first);
void					ft_do_cmd_list(t_pipe *p_head, int flagpipe);
void					ft_do_cmd_shell(char **av, int start, int flagpipe);
t_cmdlist				*ft_redir_init(t_cmdlist *cmd);
t_cmdlist				*ft_redir_io_restore(t_cmdlist *cmd);
int						ft_do_redir(t_cmdlist *cmd);
char					**ft_press_matr(char **matr);
int						ft_redir_great(t_cmdlist *cmd, int i);
int						ft_redir_less(t_cmdlist *cmd, int i);
int						ft_redir_2less(t_cmdlist *cmd, int i);
int						ft_get_prev_num(char *s, int k);
int						ft_get_next_num(char *s);
char					*ft_calc_full_path(char *s);
char					*ft_get_heredoc(char *s);
int						ft_fd_dup_close(int in_fd, int i, int j,
						t_cmdlist *cmd);
void					ft_rest_in(t_cmdlist *cmd);
void					ft_rest_out(t_cmdlist *cmd);
void					ft_rest_err(t_cmdlist *cmd);
int						ft_set_flag_add(char *ind);
int						ft_test_fd(int fd);
int						ft_great_dup1(int pref_fd, int out_fd, t_cmdlist *cmd);
int						ft_great_dup2(int pref_fd, int out_fd, t_cmdlist *cmd);
void					ft_reset_cmd_great(int j, int i, t_cmdlist *cmd);
int						ft_set_pref_fd(t_cmdlist *cmd, int i, int j);
char					*ft_heredoc(char *eof);
void					ft_init_arr_fd(int code, int fd0[2], int fd1[2]);
void					ft_set_cmd_pipe(int code, t_cmdlist *cur_cmd,
						int fd0[2], int fd1[2]);
void					ft_set_cmd_pipe_out(int code, t_cmdlist *cur_cmd,
						int fd0[2], int fd1[2]);
void					ft_pipe_dup_ch_in(t_cmdlist *cur_cmd);
void					ft_pipe_dup_ch_out(t_cmdlist *cur_cmd);
void					ft_parent_close_pipe(int code, int fd0[2], int fd1[2]);
void					ft_parent_pipe_next(t_cmdlist *cur_cmd, int fd0[2],
						int fd1[2], int flpi);
void					ft_child_pipe_exec(t_cmdlist *cur_cmd, int flpi);
void					ft_pipe_wait_ch_fin(t_cmdlist *cur_cmd,
						t_cmdlist *first_cmd, t_cmdlist *last_cmd, int flpi);
t_pipe					*ft_init_p_head(t_cmdlist *first_cmd,
						t_cmdlist *last_cmd);
int						ft_set_fd_pipes(t_pipe	*p_head, int fd0[2],
						int fd1[2]);
int						ft_set_fd_pipes_2(t_pipe *p_head, int fd0[2],
						int fd1[2]);
int						fd_set_nopipe(t_pipe *p_head);
void					ft_parent_wait(t_pipe *p_head, int flpi);
int						ft_fork(t_pipe *p_head);
void					ft_init_curcmd(t_cmdlist *cur_cmd);
void					ft_set_cmd(t_pipe *p_head);
int						ft_test_cmd_pipe (char **av, int start, t_pipe *p);
t_pipeflag				*ft_pipe_split_ini(void);
void					ft_pipe_split_3(t_pipeflag *fl, char **ret,
						char const *str);
void					ft_pipe_split_4(t_pipeflag *fl, char **ret,
						char const *str);
void					ft_pipe_split_5(t_pipeflag *fl, char **ret,
						char const *str);
void					ft_pipe_split_6(t_pipeflag *fl, char const *str);
int						ft_get_word(char **ret, int count, int size,
						char const *s);
t_greatflag				*ft_ini_great_fl(void);
int						ft_tst_great_fd(t_greatflag *f, t_cmdlist *cmd, int i);
int						ft_great_testfile(t_greatflag *f);
int						ft_tst_great_getfile(t_greatflag *f, t_cmdlist *cmd,
						int i);
int						ft_great_test_out(t_greatflag *f, t_cmdlist *cmd,
						int i);
int						ft_get_heretext(t_cmdlist *cur);
int						ft_get_redir_hd(t_cmdlist *cmd);
char					*ft_get_heof(char *ind, t_cmdlist *cmd, int i, int j);
int						ft_redir_2lesshd(t_cmdlist *cmd, int i);
int						ft_get_tless(t_cmdlist *cmd, int i, int j, char *ind);
unsigned int			hashly(char *str);
char					*ft_clear_quotes(char *s);
char					*ft_replays(char *s);
char					*ft_repl_parm(char *s, int flag, int len);
char					*ft_repl_env(char *s, int *j);
char					*ft_repl_tilda(char *s, int j);
char					*ft_repl_end_til(char *s, int j, int *flag);
int						ft_repl_sym(char *s, int j);
char					*ft_set_var_ex_lst(int *j, int *l);
char					*ft_path_level_up(char *tmp);
char					*ft_tst_cdpath(char *str);
int						ft_test_cmd_file(t_cmdlist *cur_cmd);
char					*ft_get_app_name(char *s);
char					**ft_init_shell(void);
void					ft_init_glvar(char **av);
char					**ft_add_shell(char *str, char **shell);
int						ft_unset_shell(char *parm);
int						ft_export(char **av);
int						ft_check_exp_name(char *str, int j);
char					*ft_get_env2(char *parm, char **shell);
void					ft_unset_env_parm(char *str);
char					**ft_cmd_replays(char **str);
t_cmdlist				*ft_local_assig(t_cmdlist *cur_cmd);
char					**ft_put_locals(char **av);
void					ft_go_export(char *str, int flag);
int						ft_test_andor(void);
int						ft_exit(char **av);
char					**ft_isnot(char **in);
int						ft_shell_put_test(char *str);
int						ft_type(char **av);
int						ft_test_put_env(char *str);
int						ft_printenv(char **av);
char					*ft_repl_subs(char *s, int *k, int i);
int						ft_cmd_hash(char **av);
void					ft_print_one(char *av, int code);
int						ft_print_hash(void);
char					*ft_putfnbr(int nb, char *str);
void					ft_hash_all_del(char *str);
void					ft_hash_cmd_add(char *path, char *name, int num);
int						ft_hash_usage(char *av);
char					*ft_get_hash_path(char *path);
int						ft_test_sub(char *str, int i);
char					*ft_get_parm_simple(char *s);
int						ft_test_job(char *str, int start);
void					ft_exp_env(char *parm, char *value);
void					ft_locals_to_env(char **locals);
char					*ft_get_shell_str(char *in, int len);
void					ft_sig_set(void);
void					ft_sig_dfl(void);
int						ft_test_args(char *args);
int						ft_parse_pipe(char **ret);
int						ft_if_job(t_cmdlist *cur_cmd);
void					ft_print_start_job(t_job *cur_job);
t_job					*ft_del_job(t_job *del);
int						ft_set_job_str(char *start, int end);
void					ft_add_proc(t_cmdlist *cur_cmd, t_job *job);
char					*ft_print_job_pref(t_job *cur_job);
void					ft_update_job_status(t_job *cur);
void					ft_print_jobs(void);
void					ft_del_proc_list(t_proc *proc);
void					ft_print_job_list(int i, int start, int fl, char **av);
void					ft_print_job_line(t_job *job, int fl);
void					ft_print_if_job(char *str, int fl);
int						ft_cmd_jobs(char **av);
char					*ft_num_to_str(int i);
int						ft_ampers_test(char *str, int i, int start);
void					ft_set_job_plus(void);
int						ft_cmd_bg(char **av);
int						ft_cmd_fg(char **av);
int						ft_cmd_kill(char **av);
void					ft_test_cmd_list(pid_t pid, int status);
int						ft_test_sig_list(int signo);
int						ft_job_stopped (t_job *j);
int						ft_job_completed (t_job *j);
char					*ft_add_strnum(char *str, int i);
void					ft_test_job_status(pid_t pid, int status);
int						ft_put_job_status(t_job *job, t_proc *proc, int stat);
int						ft_cmd_bg(char **av);
int						ft_cmd_kill(char **av);
void					ft_test_tstp(pid_t pid, int status);
t_job					*ft_new_job(t_cmdlist *cur_cmd);
void					ft_insert_job(t_job *cur_job);
void					ft_set_job_cont(t_job *j);
void					ft_set_cmd_exit_status(int status);
char					**ft_globbing(char **table);
bool					glob_check(char *str, char *pat, char *b_str,
						char *b_pat);
void					ft_signal_child(int signo);

char					*ft_read_alias(void);
int						ft_arr_len(char **av);
void					ft_change_alias(char *new_alias);
char					*ft_find_alias(char *str, char *alias);
char					*ft_del_alias(char *alias_str, char *alias);
int						ft_alias(char **av);
void					ft_output_alias(char *all_alias, char *av,
										int flag_alias, int *ret);
void					print_all_alias(char *all_alias, int flag_alias);
int						ft_unalias(char **av);
char					*take_value_alias(char *all_alias, char *alias_name);
char					**ft_get_alias(char **av, int i);
void					ft_rec_log(char *str);
void					ft_new_semafor(t_cmdlist *cur_cmd);
void					ft_del_semafor(t_cmdlist *cur_cmd);
int						ft_wait_semafor(t_cmdlist *cur_cmd);
void					ft_add_semafor(t_pipe *p_head);
char					*param_rem(char *val, char *flag, char *pat);
int						ft_close_fd(char *str, int in);
int						ft_get_cmd_exit_status(int status);
char					**ft_cnt_subs(char **av);
char					**ft_tst_calc(char **str, int n, int start, int end);
char					**ft_all_calc_tst(char **str);
char					*ft_calc(char *str);
int						ft_check_ekran(char *str, int pos);
int						bin_test(char **tokens);
int						bin_test_unary(char *arg, int flag);
int						bin_test_binary(char *arg1, char *arg2, int flag);
int						bin_test_get_unary(char *arg, int *flag);
int						bin_test_get_binary(char *arg, int *flag);
int						bin_test_error(char *var, char *message);
int						bin_test_return(int code);
void					ft_print_sig(pid_t pid, int signo, int status);
void					ft_cmd_to_job(int status);
int						ft_set_job_status(t_job *job, int n, int status);
char					*glob_join(char *path, char *name);
void					ft_check_q(int i, int *qflag, char *str, int b_sl);
void					ft_check_b(int i, char *str, int *br_flag,
						int *br_count);
void					ft_check_init(int *i, int *qflag, int *br_c,
						int *br_f);
void					ft_do_cmd_list_ini(t_pipe *p_head, int flpi);
void					ft_set_pgid(t_cmdlist *cmd, int flpi);
int						ft_do_cmd_loop(t_pipe *p_head, int fd0[2], int fd1[2],
						int flpi);
void					ft_add_built_to_list(int j);
char					*ft_cre_parm_str(char *parm, char *value);
void					ft_cacl_test_b(t_quoteflag *f, char *str);
void					ft_calc_test_q(t_quoteflag *f, char *str);
t_quoteflag				*ft_get_quoteflag(void);
void					ft_ini_quoteflag(t_quoteflag	*f);
char					**ft_test_calc(t_quoteflag *f, char	**str);
void					ft_test_doll_calc(t_quoteflag *f, char **str);
void					ft_set_b_sl(t_quoteflag *f, char **str);
char					**ft_resize_matr(char **str);
int						ft_split_pipes_words(char *str);
char					**ft_resize_matr_n(char **str, int n, int add);
int						ft_test_parname(char *str);
char					*ft_print_badsub(char *s, int i, char *tmp);
int						ft_subst_lbr(char *s);
void					ft_subst_tst_ps(t_quoteflag *f, char **str, int n);
void					ft_subst_tst_pf(t_quoteflag *f, char **str, int n);
int						ft_subst_tst_exe(t_quoteflag *f, char **str, int n);
char					**ft_cnt_subs_exe(char **str, int n, int start,
						int end);
int						ft_repl_parm_sub(char **val);
char					*ft_do_parm_subs(char *tmp, int *n);
char					*ft_get_parm_ll(char *tmp);
char					*ft_get_parm_qq(char *tmp);
char					*ft_get_parm_rr(char *tmp);
char					*ft_get_parm_prc(char *tmp);
char					*ft_get_parm_start(char *s, int k, int *j);
char					*ft_get_val_prc(char *s, int j, char *tmp);
char					*ft_get_val_rr(char *s, int j, char *tmp);
int						ft_get_val_plus(char *s, int j, char *tmp, char **val);
int						ft_get_val_min(char *s, int j, char *tmp, char **val);
int						ft_repl_check(char *s, int len, char *q, int j);
void					ft_sig_do(int signo, int status, pid_t pid);
void					ft_ini_quoteflag_spl(t_quoteflag *f);
int						ft_all_pipe_words(char **ret, char const *str);
t_list					*ft_globbing_path_cycle(DIR *dir, char *path,
						char *pat);
bool					ft_globbing_split(char *line, char **path,
						char **pat);
void					ft_globbing_addline(char *line, t_list **alist);
void					ft_exe_subshell(void);
char					*ft_init_loop_read(void);
void					ft_init_shell_val(char **argv, char **environ);
char					*ft_get_name(void);
char					*param_remlarge(char *val, char *pat);
void					parm_remlarge_inloop(int i, int l, char *save,
						char *val);
t_quoteflag				*ft_init_parse_init(void);
int						ft_free_qf(t_quoteflag *f);
void					ft_redir_great_close(int out_fd, int direction);
int						ft_tst_great_fd_loop(t_cmdlist *cmd, int i,
						t_greatflag *f);
int						ft_set_nopipe_start(t_cmdlist *cur_cmd);
void					ft_child_pipe_varset(t_cmdlist *cur_cmd);
void					ft_close_g_semafors(void);
int						ft_child_check_subsh(t_cmdlist *cur_cmd);
void					ft_child_pipe_init(t_cmdlist *cur_cmd, int flpi);
char					**ft_get_myalias(char **args);
char					*ft_get_lpwd(char **locals);
int						ft_parse_if_4(char *str, t_quoteflag *f);
int						ft_parse_if_3(t_quoteflag *f, char *str);
int						ft_check_parm_unrec(char *s, int j);
int						ft_check_ekran_full(char *str, int pos);
char					*del_ekran(char *old_str);
void					ft_pipe_split_sp(t_pipeflag *fl, char **ret,
						char const *str);
int						ft_msg_c(char *s1, char *s2, int code);
int						ft_less_w0(int *in_fd, int i, int j, t_cmdlist *cmd);
int						ft_less_w1(int *in_fd, int i, t_cmdlist *cmd);
t_cmdlist				*ft_child_pipe_row32(t_cmdlist *cur_cmd);
int						ft_test_file_mame(char *fname);
char					*ft_repl_parm_n(char *s, int *flag, int *j);
char					*ft_repl_til_flag(int *flag, int j, char *s, int code);
int						ft_free_ret(char *s);
char					*ft_get_sufx_name(char	*s, int *j, int l);
char					*ft_calc_in_calc(char *s);
char					ft_get_nextp_world(char	*s);
int						ft_pr_msg_rc(char *s1, char *s2);
int						ft_get_words(void);
void					ft_pipe_split_sps(t_pipeflag *fl, char const *str);
void					ft_pipe_split_4s(t_pipeflag *fl, char const *str);
void					ft_pipe_split_3s(t_pipeflag *fl, char const *str);
int						ft_check_pipe_n(char *str, t_quoteflag *f);
void					ft_set_andor(int i, t_quoteflag *f);
void					ft_do_export(char *str, int flag, int j);
int						ft_get_fd_by_n(int i, t_cmdlist *cmd,
														char *ind, int *j);
int						ft_test_f_andor(t_quoteflag *f, char *str);
void					ft_tst_gf_norm(t_greatflag *f, t_cmdlist *cmd, int i,
						int l);

#endif
