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


t_env_elem	*ft_lstnew_dlya_env(char *key, char *value, bool will_free)
{
	t_env_elem	*new;

	new = malloc(sizeof(t_env_elem));
	if (!new)
		return (NULL);
	new -> key = ft_strdup(key);
	new -> value = ft_strdup(value);
	if (will_free == true)
	{
		free(key);
		free(value);
	}
	new -> next = NULL;
	new->prev = NULL;
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

void	ft_lstadd_back_env(t_env_elem **lst, t_env_elem *new)
{
	t_env_elem	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast(*lst);
	ptr -> next = new;
	new->prev = ptr;
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
	// temp = NULL;
	// temp = malloc(sizeof(t_env_elem));
	// if (!temp)
	// 	return ;
	// temp->key = "PATH";
	// temp->value = "";
	// temp->next = shell->envr;
	// shell->envr = temp;
}
