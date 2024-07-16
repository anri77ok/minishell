#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"

char	*find_key(char	*full_key_val)
{
	int		i;
	char	*new_key;

	i = 0;
	if (!full_key_val)
		return (NULL);
	while (full_key_val[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	new_key = malloc((i + 1) * sizeof(char));
	if (!new_key)
		return (NULL);
	i = 0;
	while (full_key_val[i] != '=')
	{
		new_key[i] = full_key_val[i];
		i++;
	}
	new_key[i] = '\0';
	return (new_key);
}

char	*find_value(char	*full_key_val)
{
	int		i;
	int		j;
	char	*new_val;

	i = 0;
	if (!full_key_val)
		return (NULL);
	while (full_key_val[i] != '=')
		i++;
	j = ++i;
	while (full_key_val[j] != '\0')
		j++;
	new_val = malloc((j - i + 1) * sizeof(char));
	if (!new_val)
		return (NULL);
	j = 0;
	while (full_key_val[i] != '\0')
	{
		new_val[j] = full_key_val[i];
		i++;
		j++;
	}
	new_val[j] = '\0';
	return (new_val);
}

t_env_elem	*init_env(t_env_elem *envr, char	**env)
{
	int			i;
	t_env_elem	*temp_env_elem;

	i = 0;
	envr = NULL;
	while (env[i] != NULL)
	{
		temp_env_elem = ft_lstnew_dlya_env(find_key(env[i]), find_value(env[i]), true);
		ft_lstadd_back_env(&envr, temp_env_elem);
		i++;
	}
	 return (envr);
}

char	**env_list_to_array(t_env_elem *temp)
{
	char		**env;
	int			len;
	int			i;

	len = ft_lstsize(temp);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env[i] = ft_strjoin(temp->key, temp->value, '=');
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	print_env(t_env_elem *env, int *is_builtin)
{
	t_env_elem *temp;

	temp = env;
	while (temp)
	{
		if (temp->value != NULL)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	*is_builtin = 1;
	return (0);
}

