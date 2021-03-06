/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 00:48:34 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 01:12:05 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int			browse_reverse_flist(t_flist **list, t_opts options,
				int (fun)(t_flist **list, t_opts options))
{
	if (*list == NULL)
		return (0);
	if ((*list)->left != NULL)
		if (browse_reverse_flist(&((*list)->left), options, fun) == -1)
			return (-1);
	if (fun(list, options) == -1)
		return (-1);
	if ((*list)->right != NULL)
		if (browse_reverse_flist(&((*list)->right), options, fun) == -1)
			return (-1);
	return (0);
}

int			browse_flist(t_flist **list, t_opts options,
				int (fun)(t_flist **list, t_opts options))
{
	if (*list == NULL)
		return (0);
	if ((*list)->right != NULL)
		if (browse_flist(&((*list)->right), options, fun) == -1)
			return (-1);
	if (fun(list, options) == -1)
		return (-1);
	if ((*list)->left != NULL)
		if (browse_flist(&((*list)->left), options, fun) == -1)
			return (-1);
	return (0);
}

void		browse_flist_suffix(t_flist **list, void (fun)(t_flist **list))
{
	if (*list != NULL)
	{
		if ((*list)->right != NULL)
			browse_flist_suffix(&((*list)->right), fun);
		if ((*list)->left != NULL)
			browse_flist_suffix(&((*list)->left), fun);
		fun(list);
	}
}

int			browse_reverse_flist_path(t_flist **list, t_opts options,
	char *path, int (fun)(t_flist **list, char *path, t_opts options))
{
	if (*list == NULL)
		return (0);
	if ((*list)->left != NULL)
		if (browse_reverse_flist_path(&((*list)->left),
				options, path, fun) == -1)
			return (-1);
	if (fun(list, path, options) == -1)
		return (-1);
	if ((*list)->right != NULL)
		if (browse_reverse_flist_path(&((*list)->right),
				options, path, fun) == -1)
			return (-1);
	return (0);
}

int			browse_flist_path(t_flist **list, t_opts options, char *path,
				int (fun)(t_flist **list, char *path, t_opts options))
{
	if (*list == NULL)
		return (0);
	if ((*list)->right != NULL)
		if (browse_flist_path(&((*list)->right), options, path, fun) == -1)
			return (-1);
	if (fun(list, path, options) == -1)
		return (-1);
	if ((*list)->left != NULL)
		if (browse_flist_path(&((*list)->left), options, path, fun) == -1)
			return (-1);
	return (0);
}
