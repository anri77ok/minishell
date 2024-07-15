#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

extern int	g_exit_status;

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipex->pipes)
		{
			close(pipex->pipes[i][0]);
			close(pipex->pipes[i][1]);
		}
		i++;
	}
}

void dupeing(t_pipex *pipex, t_cmd *cmd)
{
	if (cmd->input != 0)
	{
		if (dup2(cmd->input, 0) == -1)
			p_error(pipex, DUP_ERR, NULL, 1);
		close(cmd->input);
	}
	if (cmd->output != 1)
	{
		if (dup2(cmd->output, 1) == -1)
			p_error(pipex, DUP_ERR, NULL, 1);
		close(cmd->output);
	}
	close_pipes(pipex);
}

void   run_shell_cmd(t_pipex *pipex, t_cmd *cmd, int i, int *is_builtin)
{
	pid_t	pid;
	char	*arr;
	char	**matrix;
	char	**env;

	// (void)cmd;
	env = NULL;
	//printf("%d\n", *is_builtin);
		// printf("path -- %s\n", cmd->cmd_path);
		pid = fork();
		if (pid == -1)
			p_error(pipex, FORK_ERR, NULL, 1);
		if (pid == 0)
		{
			 
			// *is_builtin = 0;
			dupeing(pipex, cmd);
			which_built_in_will_be_runed(pipex, cmd, is_builtin, 1);//esi en depqna vor builtin-@ anum enq child procesum ev export,unset u cd built inner-@ chakertavor asvac chen arvum vortev et dranc shnorhiv katarvac popoxutyunner mnum en childum u henc prcav child-@ main-um et popoxutyunnery el chen linelu
			
			if (*is_builtin == 0)
			{
				
				env = env_list_to_array(pipex->envp);
				while (env[i])
				{
					if (ft_strstr(env[i], "PATH="))
						break ;
					i++;
				}
				
				arr = cmd->cmd_args[0];
				matrix = ft_split(env[i] + 5, ':');
				cmd->cmd_path = arr;
				if (access(cmd->cmd_path, X_OK) != -1)
					if (execve(cmd->cmd_path, cmd->cmd_args, env) == -1)
					{
						p_error(pipex, CMD_NOT_FOUND, NULL, 1);
					}
				i = 0;
				while (matrix[i])
				{
					// free(pipex->cmds->cmd_path);
					cmd->cmd_path = ft_strjoin(matrix[i++], arr, '/');
					// printf(":%s\n",cmd->cmd_path);
					if (access(cmd->cmd_path, X_OK) != -1)
						break ;
				}
				//printf(":%d\n",I);
				if (access(cmd->cmd_path, X_OK) != 0)//kam !matrix[i - 1]
					p_error(pipex, CMD_NOT_FOUND, cmd->cmd_args[0], 1);
				if (execve(cmd->cmd_path, cmd->cmd_args, env) == -1)
				{
					p_error(pipex, EXECVE_ERR, NULL, 1);
				}
			}
		}
		else
			pipex->pids[i] = pid;
		if (env != NULL)
			free(env);
		
}

void create_proceces(t_pipex *pipex)
{
	t_cmd *cmd;
	int i;
	int	is_builtin;

	i = 0;
	cmd = pipex->cmds;
	while (i < pipex->cmd_count)
	{
		is_builtin = 0;
		if (!cmd->cmd_path)
		{
			cmd = cmd->next;
			i++;
			continue ;
		}
		if (pipex->cmd_count == 1)
			which_built_in_will_be_runed(pipex, cmd, &is_builtin, 0);//ete mihat cmd-a pordzum enq ashxatacnel builinner@,bayc ete trbav hramany built in chi apa mtnum enq taki if-@ 
		if (is_builtin == 0)
			run_shell_cmd(pipex, cmd, i, &is_builtin);//stex nayum enq ete
		cmd = cmd->next;
		i++;
	}
}

int	check_is_built_in(t_cmd *cmd)
{
		if (ft_strcmp(cmd->cmd_path, "env") == 0 || ft_strcmp(cmd->cmd_path, "pwd") == 0 || ft_strcmp(cmd->cmd_path, "echo") == 0 || ft_strcmp(cmd->cmd_path, "export") == 0 || ft_strcmp(cmd->cmd_path, "unset") == 0 || ft_strcmp(cmd->cmd_path, "exit") == 0)
			return (1);
		return (-1);
}


void	which_built_in_will_be_runed(t_pipex *pipex, t_cmd *cmd, int *is_builtin, int is_in_fork)
{
	if (ft_strcmp(cmd->cmd_path, "env") == 0)
		g_exit_status = print_env(pipex->envp, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "pwd") == 0)
		g_exit_status = pwd(STDOUT_FILENO, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "cd") == 0)
		g_exit_status = cd(pipex->cmds->cmd_args[1], pipex, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "echo") == 0)
	{
		if (is_in_fork == 1)
			g_exit_status = echo(cmd->cmd_args, STDOUT_FILENO, is_builtin);
		else
			g_exit_status = echo(cmd->cmd_args, cmd->output, is_builtin);
	}
	else if (ft_strcmp(cmd->cmd_path, "export") == 0)
		g_exit_status = export(pipex, cmd, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "unset") == 0)
		g_exit_status = unset(pipex, cmd, is_builtin);
	else if (ft_strcmp(cmd->cmd_path, "exit") == 0)
		mini_exit(cmd, is_builtin, is_in_fork);
	if (*is_builtin == 1 && is_in_fork == 1)//sa nra hamara vor ete builtinner-@ arvel en childum exit linenq ,vor childy prccnenq eli
		exit(g_exit_status);
}


void	wait_processes(t_pipex *pipex)
{
	int		i;
	int		exit_status;
	pid_t	pid;

	i = 0;
	//esi areci sksec sxal ashxtel shat baner//arden che)))))
	if (pipex->cmd_count == 1 && check_is_built_in(pipex->cmds) == 1)
	{
		return ;//ete cmd-@ 1hata u built ina proces chenq bace dra hamare imast chka daje karelia asel sxala wait anel@(guce)
	}
	while (i < pipex->cmd_count)
	{
		pid = waitpid(pipex->pids[i], &exit_status, 0);
		// printf("%d\n", pid);
		if (WIFEXITED(exit_status))
			g_exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			g_exit_status = TERM_CODE_SHIFT + WTERMSIG(exit_status);// TERM_CODE_SHIFT fiqsvac 128a
		i++;
	}
}

void	run_cmds(t_shell *shell)
{
	t_pipex	pipex;

	pipex_init(&pipex, shell);
	
	// printf("tiv ---- %d\n", pipex.cmd_count);
	if (pipex.cmd_count > 1)
	{
		init_pipes(&pipex);
	}
	// printf("heysav\n");
	create_proceces(&pipex);
	close_pipes(&pipex);
	wait_processes(&pipex);
	if (pipex.pipes != NULL)
		free(pipex.pipes);
	pipex.pipes = NULL;
	free(pipex.pids);
	//return (EXIT_SUCCESS);
	// export(&pipex, shell->cmds);
	// unset(&pipex, shell->cmds);
	// cd(pipex.cmds->cmd_args[1], &pipex);
	// print_env(shell->envr);
	// create_proceces(&pipex);

	//printf("cmds count ----> %d\n", pipex.cmd_count);
	// export(&pipex, shell->cmds, int *is_builtin);
	// print_env(shell->envr, int *is_builtin);
}

void	pipex_init(t_pipex *pipex, t_shell *shell)
{
	pipex->pipes = NULL;
	pipex->cmd_count = count_shell_cmds(shell->cmds);
	pipex->cmds = shell->cmds;
	pipex->envp = shell->envr;
	pipex->pids = malloc(sizeof(pid_t) * (pipex->cmd_count + 1));
}

int	count_shell_cmds(t_cmd *shell_cmds)
{
	int	count_cmds;
	t_cmd	*cur;

	cur = shell_cmds;
	count_cmds = 0;
	while (cur)
	{
		count_cmds++;
		cur = cur->next;
	}
	return (count_cmds);
}
