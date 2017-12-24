/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   files.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 23:51:52 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 01:22:00 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*new_file(char *filename, size_t is_arg)
{
	t_file	*file;

	if ((file = malloc(sizeof(t_file))) == NULL)
		return (NULL);
	file->is_arg = is_arg;
	file->file_list = NULL;
	if (filename == NULL)
	{
		file->filename = NULL;
		return (file);
	}
	if ((file->filename = ft_strdup(filename)) == NULL)
		return (NULL);
	return (file);
}
