/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:54:09 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 01:05:12 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct		s_file
{
	size_t			is_arg;
	size_t			is_file;
	char			*filename;
	struct stat		file_info;
	struct s_list	*file_list;
}					t_file;

typedef struct		s_flist
{
	t_file			*file;
	struct s_flist	*next;
}					t_flist;

char				*get_options(int argc, char **argv);
t_flist				*get_args_list(int argc, char **argv);

t_file				*new_file(char *filename, size_t is_arg);

t_flist				*new_flist(t_file *file);

void				free_args(t_flist *list);
#endif
