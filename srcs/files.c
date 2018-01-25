/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   files.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 23:51:52 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/25 18:42:00 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*new_file(char *filename, char *path, size_t print_arg, size_t is_arg)
{
	t_file	*file;

	if ((file = malloc(sizeof(t_file))) == NULL)
		return (NULL);
	file->eacces = 0;
	file->is_arg = is_arg;
	file->print_arg = print_arg;
	file->permissions = 0;
	file->file_list = NULL;
	file->error = NULL;
	file->stats_filled = 0;
	if ((file->path = ft_strdup(path)) == NULL)
		return (NULL);
	if (filename == NULL)
	{
		file->filename = NULL;
		return (file);
	}
	if ((file->filename = ft_strdup(filename)) == NULL)
		return (NULL);
	return (file);
}
