#include "tokenization.h"
#include "utils.h"

void kp(char *begin, char *word, char *end, t_token **current)
{
	char *final;

	final = join(begin, word, 0, 0);
	// printf("begin -> %s, word-> %s,end -> %s\n", begin, word, end);
	free((*current)->value);
	(*current)->value = join(final, end, 0, 0);
	// printf("value -> %s\n", (*current)->value);
	free(final);
	free(word);
	if (begin != NULL)
	{
	free(begin);
	begin = NULL;
	}
	if (end != NULL)
	{
		free(end);
		end = NULL;
	}
}

char *open_dollar(char *dollar, char **env, bool flag, int *k)
{
	char *word;
	char *envp;
	int i;
	int j;

	word = NULL;
	i = 0;
	if (flag == true)
		return (ft_strdup("$"));
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		envp = ft_substr(env[i], 0, j, false);
		if (ft_strcmp(dollar, envp) == 0)
		{
			word = ft_substr(env[i], j + 1, ft_strlen(env[i]), true);
			//if (word !=)
			*k += 0;
			free(envp);
			return (word);
		}
		free(envp);
		i++;
	}
	return(word);
}

void dolarni2(t_token **token_list, char **env)
{
	t_token *current;
	int i;
	int j;
	char *dollar = NULL;
	char *begin = NULL;
	char *word = NULL;
	char *end = NULL;
	bool flag = false;
	bool qt = false;
	bool double_qt = false;
	current = *token_list;
	while(current)
	{
		if ((current->type == WORD || (current->type >= 12 && current->type <= 16)) && current->type != LIMITER)
		{
			i = 0;
			while(current->value && current->value[i])
			{
				if (current->value[i] == 34 && qt == false)
					double_qt = !double_qt;
				if (current->value[i] == 39 && double_qt == false)
					qt = !qt;
				if (current->value[i] == '$' && qt == false)
				{
					if (current->value[i + 1] && current->value[i + 1] == '?')
					{
						free(current->value);
						current->value = ft_itoa(g_exit_status);
						break ;
					}		
					j = i;
					while (current->value[j] && (ft_isspace(current->value[j]) != 1 &&
					current->value[j] != 34 && current->value[j] != 39))
					{
						j++;
						if (current->value[j] == '$' || current->value[j] == '/' || current->value[j] == '=')
							break ;
					}
					if (j == i + 1)
						flag = true;
					begin = ft_substr(current->value, 0, i, true);
					dollar = ft_substr(current->value, i + 1, j, true);
					end = ft_substr(current->value, j, ft_strlen(current->value) - j, false);
					word = open_dollar(dollar, env, flag, &i);
					kp(begin, word, end, &current);
					free(dollar);
					flag = false;
				}
				if (current->value[0] != '\0')
					i++;
				}
		}
		current = current->next;
	}
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}




//itoa
char	*foo(void)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * 2);
	ptr[0] = 48;
	ptr[1] = '\0';
	return (ptr);
}

int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;
	long	long_n;

	if (n == 0)
		return (foo());
	len = ft_len(n);
	arr = malloc(sizeof(char) *(len + 1));
	if (!arr)
		return (NULL);
	long_n = (long)n;
	arr[len] = '\0';
	len--;
	if (n < 0)
	{
		arr[0] = '-';
		long_n = -long_n;
	}
	while (long_n != 0)
	{
		arr[len--] = ((long_n % 10) + 48);
		long_n /= 10;
	}
	return (arr);
}