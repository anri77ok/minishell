#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int    echo(char **cmd_args, int fd, int *is_builtin)
{
    int i;
	int	flag;
	int	ind;
	int	j;

	flag = 1;
    i = 1;
	ind = 1;
	*is_builtin = 1;
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
    while (cmd_args[ind])
    {
        fd_put_string(cmd_args[ind++], fd);
		if (cmd_args[ind])
			write (fd, " ", 1);
    }
	if (flag == 1)
		write (fd, "\n", 1);
	return (0);
}

void    fd_put_string(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
        write(fd, &str[i++], 1);
}

//echo a >          syntax error pti ta bayc mery echo-n anuma
//echo a > $a   esi chishta
//echo a > "$a"  pti gri No such file or directory, byc mery anuma husam en chakertnery haneluc null-i texy vor datark tox dnes kdzvi