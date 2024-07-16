#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"
//exit aa 99 ,esi sxxala
//exit a a,sxala
//exit 99 aa(esi tochnia menak exit kody chem karum stugem vortev menq $? chunenq)
void	mini_exit(t_cmd *cmd, int *is_builtin, int is_in_fork)
{
	long long	exit_num;

	*is_builtin = 1;
	if (cmd->cmd_args[1])
	{
		if (cmd->cmd_args[2])
		{
			g_exit_status = 1;
			printf("exit\n");
			fd_put_string("minishell: exit: too many arguments\n", 2);
		}
		else if (is_only_digits_and_plus_minus(cmd->cmd_args[1]) == -1)
		{
			printf("exit\n");
			error_helper1("minishell: exit: ", cmd->cmd_args[1], ": numeric argument required\n", 2);
			g_exit_status = 255;
			exit(g_exit_status);
		}
		else
		{
			exit_num = ft_atoll(cmd->cmd_args[1]);
			if (exit_num > INT_MAX || exit_num < INT_MIN || ft_strlen(cmd->cmd_args[1]) > 11)
			{
				printf("exit\n");
				g_exit_status = 255;
				error_helper1("minishell: exit:", cmd->cmd_args[1], ": numeric argument required\n", 2);
				exit(g_exit_status);
			}
			if (exit_num > 0)
				g_exit_status = exit_num % 256;
			if (exit_num < 0)
				g_exit_status = (exit_num % 256) + 256;
			printf("exit\n");
			exit (g_exit_status);
		}
	}
	else
	{
		g_exit_status = 0;
		if (is_in_fork != 1)
			printf("exit\n");
		exit(g_exit_status);
	}
}

int is_only_digits_and_plus_minus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-')
			i++;
		else
			return (-1);
	}
	return (1);
}
