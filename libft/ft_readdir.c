/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_readdir.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 19:30:27 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/16 18:54:52 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_readdir(char *filename, size_t get_hidden)
{
	DIR				*dir;
	char			**all_dirs;
	struct dirent	*dir_content;

	if ((all_dirs = malloc(sizeof(char *) * 1)) == NULL)
		return (NULL);
	all_dirs[0] = NULL;
	if ((dir = opendir(filename)) == NULL)
		return (NULL);
	while ((dir_content = readdir(dir)) != NULL)
	{
		if ((get_hidden) || (!get_hidden && dir_content->d_name[0] != '.'))
			ft_pushstr(&all_dirs, dir_content->d_name);
	}
	if (closedir(dir) == -1)
		return (NULL);
	return (all_dirs);
}
