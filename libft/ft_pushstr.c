/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pushstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 18:01:59 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/11 19:12:31 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_pushstr(char ***tab, char *str)
{
	size_t	i;
	size_t	tab_len;
	char	**new_tab;

	tab_len = ft_tablen(*tab);
	if ((new_tab = malloc(sizeof(char *) * (tab_len + 2))) == NULL)
		return (-1);
	i = 0;
	while (i < tab_len)
	{
		if ((new_tab[i] = malloc(ft_strlen((*tab)[i]) + 1)) == NULL)
			return (-1);
		ft_strcpy(new_tab[i], (*tab)[i]);
		ft_strdel(&((*tab)[i]));
		i += 1;
	}
	free(*tab);
	if ((new_tab[i] = malloc(ft_strlen(str) + 1)) == NULL)
		return (-1);
	new_tab[i] = ft_strcpy(new_tab[i], str);
	new_tab[i + 1] = NULL;
	*tab = new_tab;
	return (0);
}
