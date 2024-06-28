#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"

int		ft_lstsize(t_env_elem *lst)
{
	int		count;
	t_env_elem	*temp;

	count = 0;
	temp = lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

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

t_env_elem	*init_env(char	**env)
{
	int			i;
	t_env_elem	*new_env;
	t_env_elem	*temp_env_elem;

	i = 0;
	// new_env = malloc(sizeof(t_env_elem));
	// temp_env_elem = new_env;
	while (env[i] != NULL)
	{
		new_env = malloc(sizeof(t_env_elem));
		if (!new_env)
			return (NULL);
		temp_env_elem = new_env;
		temp_env_elem->key = find_key(env[i]);
		temp_env_elem->value = find_value(env[i]);
		temp_env_elem->next = NULL;
		new_env = new_env->next;
		i++;
	}
	return (temp_env_elem);
}

void	check_env(t_shell	*shell)
{
	t_env_elem	*temp;

	temp = shell->envr;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PATH") == 0)
			return ;
		temp = temp->next;
	}
	temp = NULL;
	temp = malloc(sizeof(t_env_elem));
	if (!temp)
		return ;
	temp->key = "PATH";
	temp->value = "";
	temp->next = shell->envr;
	shell->envr = temp;
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

//im hamar

t_env_elem	*ft_lstnew_dlya_env(char *key, char *value)
{
	t_env_elem	*new;

	new = malloc(sizeof(t_env_elem));
	if (!new)
		return (NULL);
	new -> key = ft_strdup(key);
	new -> value = ft_strdup(value);
	new -> next = NULL;
	return (new);
}


t_env_elem	*ft_lstlast(t_env_elem *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env_elem **lst, t_env_elem *new)
{
	t_env_elem	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast(*lst);
	ptr -> next = new;
	// new->prev = ptr;
}