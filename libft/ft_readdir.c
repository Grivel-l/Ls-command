/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_readdir.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 19:30:27 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/26 20:20:49 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_readdir(char *filename, size_t get_hidden)
{
	DIR				*dir;
	t_list			*list;
	t_list			*start;
	struct dirent	*dir_content;

	if ((dir = opendir(filename)) == NULL)
		return (NULL);
	start = NULL;
	while ((dir_content = readdir(dir)) != NULL)
	{
		if ((get_hidden) || (!get_hidden && dir_content->d_name[0] != '.'))
		{
			if (start == NULL)
			{
				list = ft_lstnew(dir_content->d_name, dir_content->d_namlen);
				start = list;
			}
			else
				ft_lstappend(&list,
					ft_lstnew(dir_content->d_name, dir_content->d_namlen));
		}
	}
	if (closedir(dir) == -1)
		return (NULL);
	return (start);
}
