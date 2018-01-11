/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:54:09 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/11 11:28:00 by legrivel    ###    #+. /#+    ###.fr     */
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
# include "../libft/libft.h"

typedef struct		s_file
{
	size_t			exist;
	size_t			print_arg;
	size_t			is_file;
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

char				*get_options(size_t argc, char **argv);
t_flist				*get_args_list(size_t argc, char **argv);

t_file				*new_file(char *filename, char *path, size_t print_arg);
t_flist				*new_flist(t_file *file);

t_flist				*set_flist_link(t_flist **list_start, t_list *files,
				char *path, char *options);
int					browse_reverse_flist(t_flist **list, char *options,
				int (fun)(t_flist **list, char *options));
int					browse_flist(t_flist **list, char *options,
				int (fun)(t_flist **list, char *options));
int					browse_flist_path(t_flist **list, char *options,
				char *path, int (fun)(t_flist **list, char *path, char *options));
void				browse_flist_suffix(t_flist **list, void (fun)(t_flist **list));

int					free_args(t_flist **list);
void				free_flist(t_flist **list_start);
void				free_files(t_list *files);

void				print_arg(char *arg);
void				print_time(char *time);
void				print_filetype(mode_t st_mode);
void				print_permissions(size_t permissions);
void				print_void_arg(char *arg, char *options);
void    			print_flist(t_flist **list_start, char *options);

int					read_dir(t_flist **list, char *path, char *options);
int 				get_files(t_flist **list, char *path, char *options);

int					fill_infos(t_file *file, char *path, char *options);

void				check_errno(char *path);
void				enoent_error(void);
#endif
