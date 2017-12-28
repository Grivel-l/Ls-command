/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_alloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:04:19 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 01:15:41 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int		free_args(t_flist **list, char *options)
{
	(void)options;
	ft_strdel(&((*list)->file->filename));
	free((*list)->file->file_list);
	free((*list)->file);
	free(*list);
	return (0);
}
