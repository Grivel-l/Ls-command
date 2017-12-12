/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:54:09 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/11 23:23:45 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct	s_file
{
	char		*path;
	char		*filename;
}				t_file;

typedef struct	s_arg
{
	t_file		*files;
	size_t		is_file;
	char		*arg_name;
	t_file		*file_info;
}				t_arg;

char			*get_options(int argc, char **argv);
int				get_all_files(int argc, char **argv,
			char *options, t_arg **files);

#endif
