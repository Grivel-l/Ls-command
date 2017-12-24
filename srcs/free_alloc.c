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

void	free_args(t_flist *list)
{
	t_flist	*next;

	if (list != NULL)
	{
		next = list->next;
		ft_strdel(&(list->file->filename));
		free(list->file->file_list);
		free(list->file);
		free(list);
		free_args(next);
	}
}
