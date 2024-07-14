
#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	g_exit_status = 0;

void ft_clear_shell(t_shell **shell)
{
	t_cmd	*tmp;
	while ((*shell)->cmds)
	{
		tmp = (*shell)->cmds;
		//free((*shell)->cmds->cmd_path);
		// int i = 1;
		// while ((*shell)->cmds->cmd_args[i])
		// {
		// 	free((*shell)->cmds->cmd_args[i]);
		// 	i++;
		// }
		// free((*shell)->cmds->cmd_args);
		(*shell)->cmds = (*shell)->cmds->next;
		free(tmp);
	}
}

int	main(int argc, char **argv, char **env)
{
	// char args[6][10] = {"a", "-nnannn", "-nnnnn.n", "senc", "baner", NULL};
	//  char *strings[] = {
    //     "-n",
    //     "-n",
    //     "-nn",
    //     "-nnnnn.",
    //     "-nn",
    //     "sixth",
    //     NULL  // Завершающий NULL-указатель
    // };
	// echo(strings,1);
	// pwd(1);
	t_token	*token_list;
	char	*cmd_line;
	t_shell	*shell;
	argc = 0;
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
				// check_syntax(token_list);
				dolarni2(&token_list, env_list_to_array(shell->envr));
				//ete nodei mej exav datark tox hanum enq et node-@,bayc ete chakertneri meja et node-@ chenq hanum
				//u ha chakertnery haneluc heto inqy vorpes datark tox listi mej node-@ mnaluya
				get_bez_empty_nodes(&token_list);
				chakertni(&token_list);
				token_to_cmds(shell, token_list);
				run_cmds(shell);
				print_token_list(token_list);	
			}
		}

		ft_clear_shell(&shell);
		ft_token_list_clear(&token_list);
		free(cmd_line);
	}
}


int	check_syntax(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp)
	{
		if (temp->type == S_PIPE && (!temp->prev || !temp->next))
			return -1;//bash: syntax error near unexpected token `|'
		if (temp->type == OUT_REDIR || temp->type == IN_REDIR || temp->type == APPEND_REDIR || temp->type == HERE_DOC)
		{
			if (!temp->next)
				return -1;//bash: syntax error near unexpected token `newline'
			if (temp->next->type == FILEOUT || temp->next->type == FILEIN || temp->next->type == APPEND_FILEOUT || temp->next->type == LIMITER)
				return (0);
			// perror_exit(SYNTAX_ERR, NULL, t_l->value, 2);
			// return (2);
		}
		if (temp->type == S_PIPE && control_operators(temp->next) == 1)
			return -1;//bash: syntax error near unexpected token `|'
		if (permitted_operator(temp))
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
	temp = *token_list;
	while (temp)
	{
		printf("value=%s\n",temp->value);
		printf("flag==%d\n",temp->flag);
		temp= temp->next;
	}
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
