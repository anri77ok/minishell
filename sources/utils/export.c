#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int	export(t_pipex *pipex, t_cmd *cmd, int *is_builtin)
{
	int error_exit;

	error_exit = 0;
	if (cmd)
	{
		if (!cmd->cmd_args[1])
		{
			print_export(pipex);
		}
		else
		{
			ay_nor_export(pipex, cmd, &error_exit);
		}
	}
	*is_builtin = 1;
	return (error_exit);
}

void	ay_nor_export(t_pipex *pipex, t_cmd *cmd, int *error_exit)
{
	t_env_elem	*new_node;
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (cmd->cmd_args[i])
	{
		if (cmd->cmd_args && cmd->cmd_args[i] && cmd->cmd_args[i][0] == '=')
		{
			// p_err(1, "minishell: export: `", var[i],
			// 	"': not a valid identifier\n");
		*error_exit = 1;
			i++;
			printf("vade\n");
			continue ;
		}
		key = get_word_before_equal(cmd->cmd_args[i]);
		if (is_valid_identifer(key) == -1)
		{
			*error_exit = 1;
			i++;
			printf("chexav axper\n");
			continue ;
		}
		value = get_word_after_equal(cmd->cmd_args[i]);
		if (check_this_key_in_env_list(pipex->envp, key, value) == -1)
		{
			i++;
			continue ;
		}
		new_node = ft_lstnew_dlya_env(key ,value);
		ft_lstadd_back_env(&pipex->envp, new_node);
		i++;
	}
	//printf("DDUM\n");
	// print_export(pipex);
}


int	check_this_key_in_env_list(t_env_elem *env_list, char *key, char *value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			if (value == NULL)
				return (-1);//esi arel enq vor export c  export c(erku hat node chsarqi nuyn c key-ov)
			if(env_list->value == NULL && (value[0] == '\0' || value[0]))
			{
				env_list->value = ft_strdup(value);
				return (-1);
			}//ete unenq export f heto anum enq export f= kam export f=aa popoxutyuny lini
			if (env_list->value && (value[0] == '\0' || value[0]))
			{
				char *temp = env_list->value;
				free(temp);
				env_list->value = ft_strdup(value);
				return (-1);
			}//ete lini export a=d heto export a=xx kam export export a=  poxi et node-i key-i value-n

		}
		env_list = env_list->next;
	}
	// if (value)
	//  	free(value);
	// free(key);//es frinery seg en talmmmmmmmm
	return (1);
}
//bann ayn e vor es env-i mej erb anem export a,drvelu e a-n ira \0-ov(aysinqn datark tox)
//isk env-n tpleuc ete a-n arjeq chuneav inqy pti chtpvi,isk es nenc emm are,vor da hashvi chem are
//lucel ayd xndiry

char	*get_word_after_equal(char	*value)
{
	int	i;
	// char	*res;
	int	flag;
	int	index_equal;

	flag = 0;
	i = 0;
	index_equal = 0;
	while (value[i])
	{
		if (value[i] == '=')
		{
			flag = 1;
			index_equal = i;
			//break ;
		}
		i++;
	}
	if (flag == 1)
	{
		if (value[index_equal + 1] == '\0')
			return (ft_strdup(""));
		if (i > index_equal - 1)
			return (ft_substr(value, index_equal + 1, ft_strlen(value), true));
	}
	return (NULL);
}

char	*get_word_before_equal(char	*key)
{
	int	i;
	char	*res;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			break ;
		i++;
	}
	res = ft_substr(key, 0, i, true);
	return (res);
}

void	print_export(t_pipex *pipex)
{
	t_env_elem	*temp;
	// t_cmd	*val;
	//int i = 1;
	// val = pipex->cmds;
	//printf("strrrr=%s\n", val->cmd_args[i]);
	//printf("len=%zu\n", ft_strlen(val->cmd_args[i]));
	temp = merge_sort(pipex->envp, ft_strcmp);
	if (ft_strcmp(pipex->cmds->cmd_args[0], "export") == 0 && !pipex->cmds->cmd_args[1])
	{
		while (temp)
		{
			if (temp->value == NULL)
			  	printf("declare -x %s\n", temp->key);
			else if (temp->value != NULL && temp->value[0] == '\0')
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else if (temp->value[0])
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			temp = temp->next;
		}
	}
	// free_list(temp);
	temp = NULL;
}

void	free_list(t_env_elem *temp)
{
	t_env_elem *del;

	while (temp)
	{
		del = temp;
		free(temp->key);
		free(temp->value);
		temp = temp->next;
		temp->prev = NULL;
		free(del);
	}
}
