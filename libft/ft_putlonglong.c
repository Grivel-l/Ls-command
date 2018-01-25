/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putlonglong.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 00:08:37 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 00:15:17 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlonglong(long long nb)
{
	if (nb >= 0 && nb <= 9)
		ft_putchar(nb + '0');
	else if (nb >= 10)
	{
		ft_putlonglong(nb / 10);
		ft_putlonglong(nb % 10);
	}
	else
	{
		ft_putchar('-');
		ft_putlonglong(nb * -1);
	}
}
