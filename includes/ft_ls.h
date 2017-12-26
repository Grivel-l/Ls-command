/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:54:09 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/27 00:41:21 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct		s_file
{
	size_t			exist;
	size_t			is_arg;
	size_t			is_file;
	char			*filename;
	char			*path;
	struct stat		file_info;
	struct s_flist	*file_list;
}					t_file;

typedef struct		s_flist
{
	t_file			*file;
	struct s_flist	*next;
}					t_flist;

char				*get_options(int argc, char **argv);
t_flist				*get_args_list(int argc, char **argv);

t_file				*new_file(char *filename, char *path, size_t is_arg);

t_flist				*new_flist(t_file *file);

void				free_args(t_flist *list);

void				print_result(t_flist *list);
void    			sort_print(t_flist **list_start, char *options);

int					read_dir(t_flist **list, char *path, char *options);
int 				get_files(t_flist **list, char *path, char *options);
#endif
