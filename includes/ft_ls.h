/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:54:09 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 02:54:18 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define BINARY "ft_ls"

# include <dirent.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <grp.h>
# include <pwd.h>
# include <sys/syslimits.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct		s_file
{
	size_t			exist;
	size_t			is_arg;
	size_t			eacces;
	size_t			print_arg;
	size_t			permissions;
	size_t			stats_filled;
	char			*filename;
	char			*path;
	char			*error;
	struct stat		file_info;
	struct s_flist	*file_list;
}					t_file;

typedef struct		s_flist
{
	t_file			*file;
	struct s_flist	*left;
	struct s_flist	*right;
}					t_flist;

typedef struct		s_opts
{
	unsigned char	R;
	unsigned char	a;
	unsigned char	l;
	unsigned char	r;
	unsigned char	t;
	unsigned char	error;
}					t_opts;

typedef struct		s_arg
{
	size_t			nbr;
	char			*content;
}					t_arg;

t_opts				get_options(size_t argc, char **argv, size_t i);
t_flist				*get_args_list(size_t argc, char **argv, t_opts options);

t_flist				*new_flist(t_file *file);
t_file				*new_file(char *filename, char *path, size_t print_arg, size_t is_arg);

t_flist				*set_flist_link(t_flist **list_start, t_list *files,
				char *path, t_opts options);
int					browse_reverse_flist(t_flist **list, t_opts options,
				int (fun)(t_flist **list, t_opts options));
int					browse_flist(t_flist **list, t_opts options,
				int (fun)(t_flist **list, t_opts options));
int					browse_flist_path(t_flist **list, t_opts options,
				char *path, int (fun)(t_flist **list, char *path, t_opts options));
int					browse_reverse_flist_path(t_flist **list, t_opts options,
				char *path, int (fun)(t_flist **list, char *path, t_opts options));
void				browse_flist_suffix(t_flist **list, void (fun)(t_flist **list));

void				free_tlist(t_list **list);
void				free_files(t_list *files);
int					free_args(t_flist **list);
void				free_flist(t_flist **list_start);

void				print_arg(t_file *file);
int					print_link(t_file *file);
void				print_filetype(mode_t st_mode);
void				print_permissions(size_t permissions);
void				print_void_arg(char *arg, t_opts options);
void				print_time(time_t tv_sec, time_t timestamp);
void				print_total(blkcnt_t total, t_opts options);
int					print_as_list(t_file *file, time_t timestamp);
int	    			print_flist(t_flist **list_start, t_opts options);

int					read_dir(t_flist **list, char *path, t_opts options);
int 				get_files(t_flist **list, t_arg path_arg, t_opts options);
int					fill_file(t_list *files, t_flist **list, t_arg path, t_opts options);

blkcnt_t			get_total(t_flist **list);
int					fill_infos(t_file *file, char *path, t_opts options);

void				invalid_option(char c);
void				print_error(t_file *file);
void				enoent_error(char *filename);
void				eacces_error(char *filename);
#endif
