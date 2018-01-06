#include "ft_ls.h"

void	check_errno(char *path)
{
	ft_putstr_fd(BINARY, 2);
	ft_putstr_fd(": ", 2);
	if (errno == EACCES)
	{
		ft_putstr_fd("cannot open directory '", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': Permission denied\n", 2);
	}
}

void	enoent_error(void)
{
	ft_putstr_fd("The file doesn't exist\n", 2);
}
