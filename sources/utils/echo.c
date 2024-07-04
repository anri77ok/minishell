#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void    echo(char **cmd_args, int fd)
{
    int i;
	int	flag;
	int	ind;
	int	j;

	flag = 1;
    i = 0;
	ind = 0;
	while (cmd_args[i])
	{
		if (cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
		{
			j = 2;
			while (cmd_args[i][j] && cmd_args[i][j] == 'n')
				j++;
			if (cmd_args[i][j] == '\0')
			{
				ind++;
				flag = 0;
			}
			else
				break ;
		}
		else
		{
			break ;
		}
		i++;
	}
	j = 0;
    while (cmd_args[ind])
    {
        fd_put_string(cmd_args[ind++], fd);
		write (fd, " ", 1);
    }
	if (flag == 1)
		write (fd, "\n", 1);
}

void    fd_put_string(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
        write(fd, &str[i++], 1);
}
