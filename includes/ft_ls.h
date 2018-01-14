/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:54:09 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/15 00:05:25 by legrivel    ###    #+. /#+    ###.fr     */
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
# include "../libft/libft.h"

typedef struct		s_file
{
	size_t			exist;
	size_t			is_arg;
	size_t			print_arg;
	size_t			permissions;
	char			*filename;
	char			*path;
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

t_opts				get_options(size_t argc, char **argv);
t_flist				*get_args_list(size_t argc, char **argv);

t_file				*new_file(char *filename, char *path, size_t print_arg, size_t is_arg);
t_flist				*new_flist(t_file *file);

t_flist				*set_flist_link(t_flist **list_start, t_list *files,
				char *path, t_opts options);
int					browse_reverse_flist(t_flist **list, t_opts options,
				int (fun)(t_flist **list, t_opts options));
int					browse_flist(t_flist **list, t_opts options,
				int (fun)(t_flist **list, t_opts options));
int					browse_flist_path(t_flist **list, t_opts options,
				char *path, int (fun)(t_flist **list, char *path, t_opts options));
void				browse_flist_suffix(t_flist **list, void (fun)(t_flist **list));

int					free_args(t_flist **list);
void				free_flist(t_flist **list_start);
void				free_files(t_list *files);

void				print_time(char *time);
void				print_arg(t_file *file);
void				print_file(t_file *file);
int					print_link(t_file *file);
void				print_filetype(mode_t st_mode);
void				print_permissions(size_t permissions);
void				print_void_arg(char *arg, t_opts options);
void    			print_flist(t_flist **list_start, t_opts options);

int					read_dir(t_flist **list, char *path, t_opts options);
int 				get_files(t_flist **list, char *path, t_opts options, size_t print_arg);

off_t				get_total(t_flist **list);
int					fill_infos(t_file *file, char *path, t_opts options);

void				invalid_option(char c);
void				check_errno(char *path);
void				enoent_error(char *filename);
#endif
