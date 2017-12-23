/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 00:48:34 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 00:48:56 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_flist		*new_flist(t_file *file)
{
	t_flist	*list;

	if (file == NULL)
		return (NULL);
	if ((list = malloc(sizeof(t_flist))) == NULL)
		return (NULL);
	list->file = file;
	list->next = NULL;
	return (list);
}
