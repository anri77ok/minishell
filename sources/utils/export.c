#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void	export(t_pipex *pipex, t_cmd *cmd)
{
	int	flag = 1;
	if (cmd)
	{
		if (!cmd->cmd_args[1])
		{
			flag = 1;
			print_export(pipex, flag);
		}
		else
		{
			flag = -1;
			ay_nor_export(pipex, cmd, flag);
		}
	}
}

void	ay_nor_export(t_pipex *pipex, t_cmd *cmd ,int flag)
{
	t_env_elem	*new_node;
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (cmd->cmd_args[i])
	{
		key = get_word_before_equal(cmd->cmd_args[i]);
		value = get_word_after_equal(cmd->cmd_args[i]);
		printf("anriiii=%s\n", value);
		if (check_this_key_in_env_list(pipex->envp, key, value) == -1)
		{
			i++;
			continue ;
		}
		new_node = ft_lstnew_dlya_env(key ,value);
		ft_lstadd_back_env(&pipex->envp, new_node);
		i++;
	}
	print_export(pipex, flag);
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
	if (value)
		free(value);
	free(key);
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

void	print_export(t_pipex *pipex, int flag)
{
	(void)flag;
	t_env_elem	*temp;
	t_cmd	*val;
	int i = 1;
	val = pipex->cmds;
	printf("strrrr=%s\n", val->cmd_args[i]);
	printf("len=%zu\n", ft_strlen(val->cmd_args[i]));
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

int	have_equal_sign(char *str)
{
	int	i;
	// int	flag;

	printf("str=%s\n",str);
	// flag = 0;
	i = 0;
	if (!str)
		return (-8);
	while (str[i])
	{
		if (str[i] == '=')
		{
			// flag = 1;
			break;
		}
		i++;
	}
	// if (flag == 1)
	// {
		if (str[i + 1] == '\0')
			return (1);
	// }
	return (-1);
}
