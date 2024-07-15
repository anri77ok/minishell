
#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	g_exit_status = 0;

int	global(int exit_status, int set)
{
	static int	status;

	if (set == 1)
		status = exit_status;
	return (status);
}

void	multy_putstr_fd(char *start, char *mid, char *end, int fd)
{
	int		i;

	i = 0;
	if (start != NULL)
	{
		while (start[i])
			write(fd, &start[i++], 1);
	}
	if (mid != NULL)
	{
		i = 0;
		while (mid[i])
			write(fd, &mid[i++], 1);
	}
	if (end != NULL)
	{
		i = 0;
		while (end[i])
			write(fd, &end[i++], 1);
	}
}

int	error_helper2(char *s1, char s2, char *s3, int exit_status)
{
	// global(exit_status, 1);
	g_exit_status = exit_status;
	if (s1 != NULL)
		fd_put_string(s1, 2);
	write(2, &s2, 1);
	if (s3 != NULL)
		fd_put_string(s3, 2);
	return (exit_status);
}

int	error_helper1(char *s1, char *s2, char *s3, int exit_status)
{
	//global(exit_status, 1);
	g_exit_status = exit_status;
	multy_putstr_fd(s1, s2, s3, 2);
	return (exit_status);
}

void p_error(t_pipex *pipex, int error_code, char *message, int status)
{
	if (pipex && pipex->pipes != NULL)
	{
		free(pipex->pipes);
		pipex->pipes = NULL;
	}
	if (error_code == ARGS_COUNT_ERR)
		exit(error_helper1("Invalid count of arguments\n", NULL, NULL, 1));
	else if (error_code == SYNTAX_ERR)
		error_helper1("minishell : syntax error near unexpected token `", message, "'\n", status);
	else if (error_code == QUOT_ERR)
		error_helper2("minishell : syntax error near unexpected token `", message[0], "'\n", status);
	else if (error_code == MALLOC_ERR)
		exit(error_helper1("minishell: ", NULL, ": malloc error\n", 1));
	else if (error_code == PIPE_ERR)
		perror("pipe failed");
	else if (error_code == FORK_ERR)
		perror("fork failed");
	else if (error_code == DUP_ERR)
		perror("dup failed");
	else if (error_code == CMD_NOT_FOUND)
		exit(error_helper1("minishell: ", message, ": command not found\n", status));
	else if (error_code == EXECVE_ERR)
		perror("execve failed");
}

void ft_clear_shell(t_shell **shell)
{
	t_cmd	*tmp;
	int i;

	while ((*shell)->cmds)
	{
		tmp = (*shell)->cmds;
		i = 0;
		// while (tmp->cmds->cmd_args[i])
		// {
		// 	free(tmp->cmds->cmd_args[i]);
		// 	i++;
		// }
		(*shell)->cmds = (*shell)->cmds->next;
		free(tmp);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;

	if (argc > 1)
		p_error(NULL, ARGS_COUNT_ERR, NULL, 1);
	argv = NULL;
	token_list = NULL;
	shell = malloc(sizeof(t_shell));
	shell->envr = init_env(shell->envr, env);
	shell->cmds = NULL;
	check_env(shell);
	cmd_line = "";
	while (cmd_line)
	{
		set_singals();
		cmd_line = readline("\033[0;036m MINIVIBERSEIJ: \033[0m");
		add_history(cmd_line);
		if (cmd_line && *cmd_line)
		{
			if (tokenization(cmd_line, &token_list) == 0)
			{
				if (check_syntax(token_list) != 2)
				{
					dolarni2(&token_list, env_list_to_array(shell->envr));
					//ete nodei mej exav datark tox hanum enq et node-@,bayc ete chakertneri meja et node-@ chenq hanum
					//u ha chakertnery haneluc heto inqy vorpes datark tox listi mej node-@ mnaluya
					get_bez_empty_nodes(&token_list);
					//chakertni(&token_list);
					//token_to_cmds(shell, token_list);
					//run_cmds(shell);
					//print_token_list(token_list);	
				}
			}
		}
		//ft_clear_shell(&shell);
		//ft_token_list_clear(&token_list);
		free(cmd_line);
	}

	t_env_elem *temp;

	while (shell->envr)
	{
		temp = shell->envr;
		shell->envr = shell->envr->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free(shell);
	printf("exit\n");
	system("leaks minishell");
}


int	check_syntax(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp)
	{
		if (temp->type == S_PIPE && (!temp->prev || !temp->next))
			return (p_error(NULL, SYNTAX_ERR, temp->value, 258), 2);
		if (temp->type == OUT_REDIR || temp->type == IN_REDIR || temp->type == APPEND_REDIR || temp->type == HERE_DOC)
		{
			if (!temp->next)
				return (p_error(NULL, SYNTAX_ERR, "newline", 258), 2);
				// return -1;//bash: syntax error near unexpected token `newline'
			if (temp->next->type == FILEOUT || temp->next->type == FILEIN || temp->next->type == APPEND_FILEOUT || temp->next->type == LIMITER)
				return (0);
			return (p_error(NULL, SYNTAX_ERR, temp->next->value,258), 2);
		}
		if (temp->type == S_PIPE && control_operators(temp->next) == 1)
			return (p_error(NULL, SYNTAX_ERR, temp->value, 258), 2);
			// return -1;//bash: syntax error near unexpected token `|'
		if (permitted_operator(temp))
			return (p_error(NULL, SYNTAX_ERR, temp->value, 258), 2);
			// return (perror_exit(SYNTAX_ERR, NULL, t_l->value, 2), 2);
		temp = temp->next;
	}
	return (0);//pti poxvi
}

int permitted_operator(t_token *token)
{
	if (token->type == D_PIPE || token->type == S_AND || token->type == D_AND)
			return (1);
		return (0);
}
int control_operators(t_token *token)
{
	// if (!token->value)
	// 	return (1);
	if (token->type == S_AND || token->type == D_AND || token->type == S_PIPE || token->type == D_PIPE)
		return (1);
	return (-1);
}

void	get_bez_empty_nodes(t_token **token_list)
{
	t_token *temp = *token_list;
	int	pos;

	pos = 0;
	while (temp)
	{
		if (temp->prev && ft_strcmp(temp->value,"\"\"") == 0 && (temp->prev->type == OUT_REDIR || temp->prev->type == IN_REDIR))
			temp->flag = 1;
		if (check_value_is_empty(temp->value) == 1)
		{
			delete_this_node(token_list, pos);
			temp = *token_list;
			pos = 0;
		}
		else
		{
			pos++;
			temp = temp->next;
		}
	}
	// temp = *token_list;
	// while (temp)
	// {
	// 	printf("value=%s\n",temp->value);
	// 	printf("flag==%d\n",temp->flag);
	// 	temp= temp->next;
	// }
}

void	delete_this_node(t_token	**token_list, int pos)
{
	int	count_nodes;
	t_token	*del_node;
	t_token	*temp;

	temp = *token_list;
	count_nodes = count_nodes_func(*token_list);
	if (count_nodes == 1) // If there's only one node
    {
        free(*token_list);
        *token_list = NULL;
        return ;
    }
	if (pos == 0)
	{
		del_node = *token_list;
		*token_list = (*token_list)->next;
		(*token_list)->prev = NULL;
		free(del_node);
		del_node = NULL;//ste seg ka//el chkaaaaaaaaaa
	}
	else if (pos == count_nodes - 1)
	{
		while (temp->next->next)
			temp = temp->next;
		del_node = temp->next;
		free(del_node);
		temp->next = NULL;
	}
	else
		middle_node(token_list, pos);
}

void	middle_node(t_token **token_list, int pos)
{
	t_token	*temp;
	t_token	*del_node;

	temp = *token_list;
	while (pos > 0)
	{
		temp = temp->next;
		pos--;
	}
	del_node = temp;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(del_node);
}


int	count_nodes_func(t_token	*token_list)
{
	t_token	*temp;
	int	count_nodes;

	count_nodes = 0;
	temp = token_list;
	while(temp)
	{
		count_nodes++;
		temp = temp->next;
	}
	return (count_nodes);
}

int	check_value_is_empty(char	*value)
{
	if (value[0] == '\0')
		return (1);
	return (-1);
}
